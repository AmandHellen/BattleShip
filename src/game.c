#include "game.h"

/*
prompts the user for the attack i and j coordinates
Returns a COORD with said i and j
*/
COORD input_coord(){
	COORD c;
	printf("Enter the attack coordinate:\n");
	printf("Line >> ");
	scanf("%d", &c.i);
	printf("Column >> ");
	scanf("%d", &c.j);
	return c;
}

// checks if a move from (old_x, old_y) -> (new_x, new_y) is valid (between the boundaries)
bool valid_position(char *shape, int curr_rot, int old_x, int old_y, int new_x, int new_y, char *map_repr, MAP map){
   // int dim = get_dim(map);
    int old_pos;
	COORD old;
    CELL *c; 
    int pi;

    for (int i = 0; i < BMAP_SIZE; i++)
        for (int j = 0; j < BMAP_SIZE; j++)
        {
			old.i = old_y + i;
			old.j = old_x + j;
           /* delay(0.5);*/
            old_pos = (old_y + i)*dim + (old_x + j);
            
            if((c = get_cell(old,map)) == NULL){  
                goto jump;
            }

                
			if(c->ship == NULL && old_pos >= 0 && old_pos < dim*dim){
                map_repr[old_pos] = '.'; // erase the 'X's on the the old ship position
            }

jump:
            pi = rotate_point(i, j, curr_rot, BMAP_SIZE); // get the unidimensional index of this point when curr_rot is applied


            if (shape[pi] != '.'){
                if ((new_y +i < 0 || new_y + i >= dim) || (new_x + j < 0 || new_x + j >= dim)){
                    return false; // the new move make the piece go beyond the boundaries of the field.
                }
            }
        }
    return true;
}


void draw_ship(char *curr_bmap, MAP map, char *map_repr, int old_x, int old_y, int curr_x, int curr_y, int curr_rot){
    //int dim = get_dim(map);
	COORD old;
    CELL *c;
    for (int i = 0; i < BMAP_SIZE; i++)
        for (int j = 0; j < BMAP_SIZE; j++){
            if (curr_bmap[rotate_point(i, j, curr_rot, BMAP_SIZE)] != '.'){
                // draw the ship on this position
                map_repr[(curr_y + i)*dim + (curr_x + j)] = 'X';
				old.i = old_y + i;
				old.j = old_x + j;

                if((c = get_cell(old,map)) == NULL)
                    continue;

				if(c->ship != NULL)
                    map_repr[(old_y + i)*dim + (old_x + j)] = 'O';
            }
        }
}

//prints the map representation to the screen
void draw_field(char *map_repr){
    printf("  ");
        for (int i = 0; i < dim; i++)
            printf("%.2d ", i);

        printf("\n");
        for (int i = 0; i < dim; i++){
            printf("%.2d", i);
            for (int j = 0; j < dim; j++){
                printf(" %c ",map_repr[i*dim + j]);
            }
            printf("\n");
        }
}

char *gen_map_repr(){
    // just a representation of the map for UI purposes
    char *map_repr = (char*)malloc(sizeof(char)*dim*dim+1);
    if (map_repr == NULL)
        map_error("Failed to allocate memory for MAP_REPR");

    // empty map
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            map_repr[i*dim + j] = '.';
        }
    }
    map_repr[dim*dim] = '\0';
    return map_repr;
}



char get_keypress(char* map_repr){
    char key_press;
    system("clear");
    draw_field(map_repr);
    printf("Place your ships!\n");
    printf("To move the ship around press on the following keys + [ENTER]:\n");
    printf("w -> up | s -> down | a -> left | d -> right | r -> rotate\n");
    printf("To place the ship press [SPACE] + [ENTER]\n\n>> ");
    scanf("%c", &key_press);
    getchar();      // clear input buffer
    return key_press;
}

char get_rand_keypress(int rand_ind){
    if (rand_ind >= 0 && rand_ind < 20) return 'w';
    else if (rand_ind >= 20 && rand_ind < 40) return 'a';
    else if (rand_ind >= 40 && rand_ind < 60) return 'd';
    else if (rand_ind >= 60 && rand_ind < 80) return 's';
    else return 'r';
}

int update_position(char key_press, char **curr_bmap, int *curr_rot, int *curr_x, int *curr_y,
                     int old_x, int old_y, char *map_repr, MAP map, int *shape_ind, int *game_shapes, MODE mode){
    int shape;
    switch(tolower(key_press)){
        case 'w':
            (*curr_y) -= (valid_position(*curr_bmap, *curr_rot, *curr_x, *curr_y, *curr_x, *curr_y - 1, map_repr, map)) ? 1 : 0;
            break;
        case 's':
            (*curr_y) += (valid_position(*curr_bmap, *curr_rot, *curr_x, *curr_y, *curr_x, *curr_y + 1, map_repr, map)) ? 1 : 0;
            break;
        case 'd':
            (*curr_x) += (valid_position(*curr_bmap, *curr_rot, *curr_x, *curr_y, *curr_x + 1, *curr_y, map_repr, map)) ? 1 : 0;
            break;
        case 'a':
            (*curr_x) -= (valid_position(*curr_bmap, *curr_rot, *curr_x, *curr_y, *curr_x - 1, *curr_y, map_repr, map)) ? 1 : 0;
            break;
        case 'r':
            (*curr_rot) += (valid_position(*curr_bmap, *curr_rot + 1, *curr_x, *curr_y, *curr_x, *curr_y, map_repr, map)) ? 1 : 0;
            break;
        case 32: // try to place the ship on this position
            shape = game_shapes[*shape_ind];
            if(!place_ship(shape, *curr_bmap, map, map_repr, *curr_x, *curr_y, *curr_rot)){
                if (mode == MANUAL){
                    printf("You can't place the ship here!\n");
                    delay(1);
                }
                return -1;
            }
            (*shape_ind)++; // next ship
            (*curr_bmap) = shapes[game_shapes[*shape_ind]].bitmap;
            // back to starting position (all the ships start here)
            (*curr_rot) = 0;
            (*curr_x) = dim / 2;
            (*curr_y) = 0;
            fflush(stdin);
            draw_ship(*curr_bmap, map, map_repr, old_x, old_y, *curr_x, *curr_y, *curr_rot);
            return -1;
        default:
            if (mode == MANUAL){
                printf("Invalid key!\n");
                delay(1);
            }
    }
    return 0;
}

//FOR DEBUG ONLY
void print_map(MAP m){
    COORD c; 
    CELL *cell;
    printf("  ");
    for (int i = 0; i < dim; i++)
        printf("%.2d ", i);
    printf("\n");

    for(int i=0; i< dim; i++){
        printf("%.2d", i);
        for(int j=0; j< dim; j++){
            c.i = i; 
            c.j = j;

            if((cell = get_cell(c,m)) == NULL)
                continue;

            STATE s = cell->state;
            switch(s){
                case EMPTY:
                    printf(" . ");
                    break;
                case FILLED:
                    printf(" O ");
                    break;
            }
        }
        printf("\n");
    }
}

/*
ship placement loop
Updates the map matrix and returns that map
*/
MAP fill_map(MAP map, int n_ships, int *game_shapes, MODE mode){
    //int dim = get_dim(map);
    char key_press;
    int curr_rot = 0; // angle of the current rotation (0 -> 0 | 1 -> 90 | 2 -> 180 | 3 -> 270)
    int curr_x = dim / 2; // current x-axis coordinate of the ship
    int curr_y = 0; // current y-axis coordinate of the ship
    int old_x = curr_x;
    int old_y = curr_y;
    int n_rand_moves; // number of random moves to execute

    if (mode == RANDOM){ // populate random_moves with integers from 0 to dim*dim (each reprenting a move key)
        n_rand_moves = rand() % dim*dim;
        if(n_rand_moves == 0) n_rand_moves++; // always move atleast one position
    }

    int shape_ind = 0; // first shape
    char *curr_bmap = shapes[game_shapes[shape_ind]].bitmap; // the shape of the current ship to be placed

    char *map_repr = gen_map_repr();

    // the first ship starts here (before moving)
    draw_ship(curr_bmap, map, map_repr, old_x, old_y, curr_x, curr_y, curr_rot);

    int move_ind = 0;

    while (shape_ind < n_ships){
        if (mode == MANUAL){
            print_map(map);
            key_press = get_keypress(map_repr);
        }
        else if (mode == RANDOM){
            if (move_ind == n_rand_moves){ // executed all moves. place the ship.
                key_press = 32;
                // value resets
                move_ind = 0;
                n_rand_moves = rand() % dim*dim;
                if(n_rand_moves == 0) n_rand_moves++; // always move atleast one position
            }
            else{ // get the key represented by the number
                int rand_ind = rand() % 100;
                key_press = get_rand_keypress(rand_ind);
                move_ind++;
            }
        }

        // update the new position according to the key pressed

        int aux = update_position(key_press, &curr_bmap, &curr_rot, &curr_x, &curr_y,
                                  old_x, old_y, map_repr, map, &shape_ind, game_shapes, mode);
        if (aux == -1) continue;

        fflush(stdin);
        draw_ship(curr_bmap, map, map_repr, old_x, old_y, curr_x, curr_y, curr_rot);

        old_x = curr_x;
        old_y = curr_y;
    }
    free(map_repr);
    return map;
}

/*
checks the matrix for collisions and place the ship if there's none
Returns the result boolean result of said check
*/
bool place_ship(int shape_ind, char *shape, MAP map, char *map_repr, int curr_x, int curr_y, int curr_rot){
    CELL *c; 
    //int dim = get_dim(map);
    COORD bmap_begin, curr;
    bmap_begin.i = curr_y;
    bmap_begin.j = curr_x;
    SHIP *s = create_ship(shape, shape_ind, curr_rot, bmap_begin);
    CELL *cell;
    

    // collision checking
    for (int i = 0; i < BMAP_SIZE; i++){
        for (int j = 0; j < BMAP_SIZE; j++){
			curr.i = curr_y + i;
			curr.j = curr_x + j;

            if((c = get_cell(curr,map)) == NULL)
                continue;
                
			if (c->ship != NULL && (shape[rotate_point(i, j, curr_rot, BMAP_SIZE)] != '.')){
                // collision!
                free_ship(s);
                return false;
            }
        }
    }

    //place the ship on the map's matrix and update map_repr
    for (int i = 0; i < BMAP_SIZE; i++){
        for (int j = 0; j < BMAP_SIZE; j++){
            if (shape[rotate_point(i, j, curr_rot, BMAP_SIZE)] != '.'){
				curr.i = curr_y + i;
				curr.j = curr_x + j;

                if((cell = get_cell(curr, map)) == NULL)
                    continue;
                cell->ship = s;
                cell->state = FILLED;            
                map_repr[(curr_y + i)*dim + (curr_x + j)] = 'O';
            }
        }
    }

    return true;
}


/*
executes the attack by curr player on the adv player map and checks the game state
Returns 0 for misses, 1 for hits and -1 in case the coordinate was previously tried
*/
int attack(COORD c, PLAYER *curr, PLAYER *adv){
	SHIP *s;
    CELL *curr_cell, *adv_cell; 

	int pos = c.i*dim + c.j; // bidimensional index to unidimensional conversion
	if(pos < 0 || pos >= dim*dim ){ // out of bounds
		printf("Invalid coordinate. Try again!\n");
		return -1;
	}

    if((curr_cell = get_cell(c,curr->map)) == NULL){
        map_error("Cannot get cell ATTACK CURR");
    }
        
        
	if (curr_cell->atk_cell != UNKNOWN){
		printf("\nThis position was previously attacked. Try again!\n");
		delay(1);
		return -1;
	}

    if((adv_cell = get_cell(c,adv->map)) == NULL){
        map_error("Cannot get cell ATTACK ADV");
    }
        
	if((s = adv_cell->ship) != NULL){
        curr_cell->atk_cell = HIT;
		s->hits++;
		if(s -> size == s -> hits){
			printf("\nSUNK!\n");
			delay(1);
			adv->n_ships--;
			s -> sunk = true;
		}
		else{
			printf("\nHIT!\n");
			delay(1);
		}
		return 1;
	}else{
		printf("\nYou missed!\n");
		delay(1);
        curr_cell->atk_cell = MISS;
		return 0;
	}
	return 0;
}

// checks if the current player wins (the opponent has no remaining ships)
bool check_state(PLAYER *adv){
	return adv->n_ships == 0;
}

// main game loop
void play(PLAYER *p1, PLAYER *p2){
	bool finished = false;
	COORD c;
	PLAYER *curr_player = p1;
	PLAYER *other_player = p2;
	PLAYER *aux_player; // used for swapping

	while(!finished){
input_attack:
		system("cls || clear");
		print_dashboard(curr_player, other_player);
		//print_map(other_player->map);
		printf("\nNow playing: %s\n", curr_player->name);
		c = input_coord();
		int attack_result = attack(c, curr_player, other_player);
		if(attack_result == 1){ // HIT
			finished = check_state(other_player);
			if(finished) continue;
		}else if(attack_result == -1) // retry attack
			goto input_attack;

		// swap the players
		aux_player = curr_player;
		curr_player = other_player;
		other_player = aux_player;
	}
	printf("Congratulations, %s! You win!\n", curr_player->name);
	clean_game(p1, p2);
}

void clean_game(PLAYER *curr, PLAYER *adv){
	free_player(curr);
	free_player(adv);
}

PLAYER *player_input(int n_player, int n_ships, int *game_shapes, MODE mode){
	char name[NAME_LEN];
	printf("Player %d: type your name >> ", n_player);
	fgets(name, NAME_LEN, stdin);
	name[strcspn(name ,"\n")] = 0;
	if (mode == RANDOM) printf("Randomly filling %s's map...\n", name);
	MAP empty_map = create_map(dim);
    empty_map = fill_map(empty_map, n_ships, game_shapes, mode);
	PLAYER *p = create_player(name, empty_map, n_ships, game_shapes, mode);
	if (mode == RANDOM) printf("%s's map successfully generated.\n", name);
	return p;
}

// prompts the players for their names and fills their maps (RANDOM or MANUAL)
void input_players(PLAYER **p1, PLAYER **p2, int n_ships, int *game_shapes, MODE mode){
	*p1 = player_input(1, n_ships, game_shapes, mode);
	*p2 = player_input(2, n_ships, game_shapes, mode);
	delay(1);
}

int *gen_game_shapes(int n_ships){
	int *game_shapes = (int*)malloc(sizeof(int)*n_ships); // random ships
	if (game_shapes == NULL)
		game_error("Failed to allocate memory for GAME_SHAPES");
	for(int i=0; i<n_ships; i++){
		game_shapes[i] = rand() % NSHAPES;
	}
	return game_shapes;
}

// Call this in case of error
void game_error(char *msg){
	fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}

void *create_shm(size_t sz){
    return mmap(NULL,
                sz,
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, 
                -1, 0);
}

int create_player_socket(){
    int sock;
    struct sockaddr_in sock_name;
    struct hostent *hp;
    
    /* create socket on which to send */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("opening datagram socket");
        return -1;
    }

    /* destination is constructed from hostname
    and port oth given in the command line */
    if ((hp = gethostbyname("localhost")) == 0){
        fprintf(stderr, "unknown host localhost\n");
        return -1;
    }
    memcpy(&sock_name.sin_addr, hp->h_addr, hp->h_length);
    sock_name.sin_family = AF_INET;
    sock_name.sin_port = htons(PORT); // fixed port

    /* connect to given port */
    if (connect(sock, (struct sockaddr *)&sock_name, sizeof(sock_name)) < 0){
        perror("connecting to server socket");
        return -1;
    }
    
    return sock;
}

int create_server_socket(){
    int sock;
    struct sockaddr_in name;
    
    /* create socket from which to read */

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("opening datagram socket");
        return -1;
    }

    /* create name with wildcards*/
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = INADDR_ANY;
    name.sin_port = htons(PORT); // fixed port
    if (bind(sock, (struct sockaddr *)&name, sizeof(name))){
        perror("binding datagram socket");
        return -1;
    }
    return sock;
}

int send_int(int sock, int x){
    int len = snprintf(NULL, 0, "%d", x);
    char *out = malloc(len + 1);
    snprintf(out, len + 1, "%d", x);
    if (write(sock, out, len + 1) < 0)
        return -1;
    free(out);
    return 0;
}

int send_int_array(int sock, int *array){
    int out[n_ships];
    for(int i=0; i<n_ships; i++){
        out[i] = array[i];
    }
    if (write(sock, (char *)out, n_ships*sizeof(int)) < 0)
        return -1;
    
    return 0;
}

void mng_player_socket(int new_sock){
    int rbytes;
    char buf[BUF_SIZE];
    char name[BUF_SIZE];

    if((rbytes = read(new_sock, buf, sizeof(buf))) < 0){
        perror("ERROR on read");
        close(new_sock);
        exit(EXIT_FAILURE);
    }

    if((strcmp(curr_player_name, "") == 0)) {
        write(new_sock, "OK", 3);
        memcpy(curr_player_name, buf, sizeof(buf));
    }
        
    else if ((strcmp(curr_player_name, buf) == 0)){
        write(new_sock, "TAKEN", 6);                           
    }
    else if ((strcmp(adv_player_name, "") == 0)){
        write(new_sock, "OK", 3);
        memcpy(adv_player_name, buf, sizeof(buf));
    }
    
    memcpy(name, buf, sizeof(buf));

    printf("curr_player: %s\nadv_player: %s\n", curr_player_name, adv_player_name);
    while(1){
        if((rbytes = read(new_sock, buf, sizeof(buf))) < 0){
        perror("ERROR on read");
        close(new_sock);
        exit(EXIT_FAILURE);
        }

        if((strcmp(buf, "DIM") == 0)) {
            send_int(new_sock, dim);
        }
            
        else if ((strcmp(buf, "MODE") == 0)){
            send_int(new_sock, mode);
        }
        else if ((strcmp(buf, "SHAPES") == 0)){
            send_int_array(new_sock, game_shapes);
        }
        else if((strcmp(buf, "READY") == 0)){
            (*ready)++;
            printf("%d\n", *ready);
            break;

        }
       memset(buf, 0, BUF_SIZE);
    }
    
    printf("%s: Waiting for the other player to start the game...\n", name);

    while(*(ready) < 2){
        delay(1);
    }

    while(1){
        char *aux_name;

        if((strcmp(name, curr_player_name) == 0)) {
            write(new_sock, "PLAY", 5);

            int coord_in[2];
            read(new_sock, coord_in, 2 * sizeof(int));
            *attack_i = coord_in[0];
            *attack_j = coord_in[1];
            
            while(*attack_state == -1){
                delay(1);
            }

            switch(*attack_state){
                case 0:
                    write(new_sock, "MISS", 5);
                    break;
                case 1:
                    write(new_sock, "HIT", 4);
                    break;
                case 2:
                    write(new_sock, "SUNK", 5);
                    break;
            }

            *attack_state = -1;  

        }else{
            write(new_sock, "HOLD", 5);
           
            while(*attack_i == -1 && *attack_j == -1){
                delay(1);
            }

            int *coord_out = (int *)malloc(2 * sizeof(int));
            coord_out[0] = *attack_i;
            coord_out[1] = *attack_j;
            send_int_array(new_sock, coord_out);
            free(coord_out);
            read(new_sock, buf, sizeof(buf));
            *attack_state = atoi(buf);
        }
    
        aux_name = curr_player_name;
        curr_player_name = adv_player_name;
        adv_player_name = aux_name;

        *attack_i = -1;
        *attack_j = -1;
    }

    printf("%s: Client disconnected.\n", name);
    close(new_sock);
    exit(EXIT_SUCCESS);
}

int server_play(int sock){
    /* read from the socket */
    int pid, new_sock;
    socklen_t cli_len;
    struct sockaddr_in cli_addr;

    curr_player_name = create_shm(sizeof(*curr_player_name));
    adv_player_name = create_shm(sizeof(*adv_player_name));
    ready = create_shm(sizeof(*ready));
    attack_i = create_shm(sizeof(*attack_i));
    attack_j = create_shm(sizeof(*attack_j));
    attack_state = create_shm(sizeof(*attack_state));

    memcpy(curr_player_name, "", sizeof(""));
    memcpy(adv_player_name, "", sizeof(""));
    *ready = 0;
    *attack_i = -1;
    *attack_j = -1;
    *attack_state = -1;

    listen(sock, 10);
    printf("Listening...\n");
    cli_len = sizeof(cli_addr);
    for ( ; ; ){ // keep-alive
        new_sock = accept(sock, (struct sockaddr*)&cli_addr, &cli_len);
        if (new_sock < 0){
            perror("ERROR on accept");
            close(sock);
            return EXIT_FAILURE;
        }
        printf("New connection from client\n");

        if((pid = fork()) < 0){
            perror("ERROR on fork");
            close(sock);
            close(new_sock);
            return EXIT_FAILURE;
        }
        else if (pid == 0){
            /* client process */
            close(sock);
            mng_player_socket(new_sock);
        }
//=================================================================================================
        else{
            close(new_sock);                          
        } 
    }
    close(sock);
    munmap(curr_player_name, sizeof(*curr_player_name));
    munmap(adv_player_name, sizeof(*adv_player_name));
    munmap(ready,sizeof(*ready));
    munmap(attack_i, sizeof(*attack_i));
    munmap(attack_j, sizeof(*attack_j));
    munmap(attack_state, sizeof(*attack_state));
    return EXIT_SUCCESS;
}

int client_play(int player_type){
    int player_sock;
    char in[BUF_SIZE];
    char name[NAME_LEN];
    PLAYER *p;

    if((player_sock = create_player_socket()) == -1)
        return -1;
    
    printf("Connected to server.\n");

    printf("Type your name >> ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name ,"\n")] = 0;
    
    if (write(player_sock, name, sizeof(name)) < 0)
        perror("sending datagram message");
    
    if (read(player_sock, in, sizeof(in)) < 0)
        perror("receiving datagram packet");

    if ((strcmp(in, "TAKEN")) == 0){
        printf("That username is already in use. Try again.\n");
        close(player_sock);
        return -1;
    }

    if(player_type == 0){
        MAP empty_map = create_map(dim);
        empty_map = fill_map(empty_map, n_ships, game_shapes, mode);
        p = create_player(name, empty_map, n_ships, game_shapes, mode);
        print_map(empty_map);
    }else{
        if (write(player_sock, "DIM", 4) < 0)
        perror("sending datagram message");
    
        if (read(player_sock, in, sizeof(in)) < 0)
            perror("receiving datagram packet");
        
        dim = atoi(in);
        
        n_ships = (dim*dim) / (BMAP_SIZE*BMAP_SIZE);

        if (write(player_sock, "MODE", 5) < 0)
        perror("sending datagram message");
    
        if (read(player_sock, in, sizeof(in)) < 0)
            perror("receiving datagram packet");
        
        mode = atoi(in);

        if (write(player_sock, "SHAPES", 7) < 0)
        perror("sending datagram message");

        int shapes_in[n_ships];

        if (read(player_sock, shapes_in, n_ships*sizeof(int)) < 0)
            perror("receiving datagram packet");

        game_shapes = (int*)malloc(sizeof(int) * n_ships);
        for(int i=0; i<n_ships; i++){
            game_shapes[i] = shapes_in[i];
        }

        MAP empty_map = create_map(dim);
        empty_map = fill_map(empty_map, n_ships, game_shapes, mode);
        p = create_player(name, empty_map, n_ships, game_shapes, mode);
        print_map(empty_map);
    }

    if (write(player_sock, "READY", 6) < 0)
        perror("sending datagram message");   

    while(1){
        if (read(player_sock, in, sizeof(in)) < 0)
            perror("ATTACK");

        printf("%s: %s\n", name, in);

        if(strcmp(in, "PLAY") == 0){
            CELL *cell;
            COORD c;
input_coord:
            c = input_coord();

            int pos = c.i*dim + c.j; // bidimensional index to unidimensional conversion
            if(pos < 0 || pos >= dim*dim ){ // out of bounds
                printf("Invalid coordinate. Try again!\n");
                goto input_coord;
            }

            if((cell = get_cell(c,p->map)) == NULL){
                map_error("Cannot get cell ATTACK CURR");
            }
                              
            if (cell->atk_cell != UNKNOWN){
                printf("\nThis position was previously attacked. Try again!\n");
                delay(1);
                goto input_coord;
            }

            int *coord_out = (int *)malloc(2 * sizeof(int));
            coord_out[0] = c.i;
            coord_out[1] = c.j;
            send_int_array(player_sock, coord_out);
            free(coord_out);

            read(player_sock, in, sizeof(in)); 
            if(strcmp(in, "MISS") == 0){
                printf("%s: MISS\n", name);
                cell->atk_cell = MISS;
            }
            else if(strcmp(in, "HIT") == 0){
                printf("%s: HIT\n", name);
                cell->atk_cell = HIT;
            }
            else if(strcmp(in, "SUNK") == 0){
                printf("%s: SUNK\n", name);
                cell->atk_cell = HIT;
            }
        }
        else if(strcmp(in, "HOLD") == 0){
            printf("Not your turn!\n");
            CELL *cell;
            SHIP *s;
            COORD c;
            int coord_in[2];
            read(player_sock, coord_in, 2 * sizeof(int));          
            c.i = coord_in[0];
            c.j = coord_in[1];
            printf("%s: RECEIVED: %d %d\n", name, c.i, c.j);

            if((cell = get_cell(c,p->map)) == NULL){
                map_error("Cannot get cell ATTACK CURR");
            }

            if((s = cell->ship) != NULL){
                s -> hits++;
                if(s -> size == s -> hits){
                    p -> n_ships--;
                    s -> sunk = true;
                    send_int(player_sock, 2);
                }else{
                    send_int(player_sock, 1);
                }              
            }else{
                send_int(player_sock, 0);
            }
        }
        memset(in, 0, BUF_SIZE);
    }

    close(player_sock);
    return EXIT_SUCCESS;
}

int host_game(int player_type){
    int sock, pid;
    
    if((sock = create_server_socket()) == -1)
        return EXIT_FAILURE;

    if((pid = fork()) < 0){
        perror("ERROR on fork");
        close(sock);
        return EXIT_FAILURE;
    }
    if(pid == 0){ // player 1 
        sleep(2);
        return client_play(player_type);
    }else{ // server 
        return server_play(sock);
    }      
}

int input_game_config(){
start_game:
    printf("Select the map generation mode:\n0 -> RANDOM\n1 -> MANUAL\n>> ");
	scanf("%d",&mode);
    if(mode==0){ // RANDOM
		dim = rand() % (MAX_DIM - MIN_DIM + 1) + MIN_DIM;
		printf("Map dimension: %d x %d\n",dim,dim);
		getchar();
	}
	else if(mode==1){ // MANUAL
manual_mode:
		printf("Enter the map dimension (20-40) >> ");
		scanf("%d",&dim);
        getchar();
		if(dim < MIN_DIM || dim > MAX_DIM) {
			printf("Invalid map dimension! Input a number between 20 and 40.\n");
			goto manual_mode;
		}
    }
    else{ // INVALID
		printf("Invalid option. Try again.\n");
		goto start_game;
	}
    n_ships = (dim*dim) / (BMAP_SIZE*BMAP_SIZE);
	game_shapes = gen_game_shapes(n_ships);
    return mode;
}
// main menu and game initializer
int main(){
	PLAYER *p1, *p2;
    int game_mode; // 0 -> SAME TERMINAL / 1 -> SEPARATE TERMINALS / 2 -> PLAY OVER TCP/IP
    int player_type; // 0 -> host (player 1) / 1 -> client (player 2)
	srand (time(NULL));	// seed the random number generator
	system("cls || clear");
	printf("===============================\n#####=====BATTLESHIP======#####\n===============================\n\n");

game_mode_selection:
    printf("Choose the game mode:\n\n");
    printf("0 -> Both players share the same terminal\n");
    printf("1 -> Both players have their own terminal\n");
    printf("2 -> Play over TCP/IP\n");
    scanf("%d", &game_mode);
    getchar();

player_type_selection:
    if(game_mode == 1 || game_mode == 2){
        printf("Are you the host or the client?\n");
        printf("0 -> Host (player 1)\n1 -> Client (player 2)\n");
        scanf("%d", &player_type);
        getchar();

        if(player_type == 0){ // host 
            input_game_config();
            return host_game(player_type);
        }else if(player_type == 1){ // client
            return client_play(player_type);
        }else{
            printf("PLease select a valid option. Try again.\n");
            goto player_type_selection;
        }
    }
    else if (game_mode == 0){
        input_game_config();
        input_players(&p1, &p2, n_ships, game_shapes, mode);
        free(game_shapes);
        play(p1, p2);
    }else{
        printf("Please select a valid option. Try again.\n");
        goto game_mode_selection;
    }
	exit(EXIT_SUCCESS);
}