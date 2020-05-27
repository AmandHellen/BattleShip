#include "game.h"

//int dim;

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
           /* printf("(%d/%d)\n", old.i, old.j);
            delay(0.5);*/
            old_pos = (old_y + i)*dim + (old_x + j);
            /*if(get_cell(old, &c, map) == -1) 
                game_error("Cannot get cell");*/
            if((c = get_cell(old,map)) == NULL){  
               // printf("(%d/%d)\n", old.i, old.j);      
              //  continue;     
                //map_error("Cannot get cell VALID POSITION");
                goto coisa;
            }

            //c = get_cell(old,map);
                
			if(c->ship == NULL && old_pos >= 0 && old_pos < dim*dim){
                map_repr[old_pos] = '.'; // erase the 'X's on the the old ship position
            }

coisa:
            pi = rotate_point(i, j, curr_rot, BMAP_SIZE); // get the unidimensional index of this point when curr_rot is applied

           // printf("dim: %d | new_y + i: %d | new_x + j: %d\n", dim, new_y + i, new_x + j);


            if (shape[pi] != '.'){
               // printf("QUASE FORA DO MAPA!\n");
                if ((new_y +i < 0 || new_y + i >= dim) || (new_x + j < 0 || new_x + j >= dim)){
                   // printf("FORA DO MAPA!\n");
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
               /* if(get_cell(old, &c, map) == -1) 
                    game_error("Cannot get cell");*/
                if((c = get_cell(old,map)) == NULL)
                    continue;
                    //map_error("Cannot get cell DRAW_SHIP");
                
                  printf("%d/%d\n", old.i, old.j);

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
   // system("clear");
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
           /* if(get_cell(c, &cell, m) == -1) 
                game_error("Cannot get cell");*/
            if((cell = get_cell(c,m)) == NULL)
                continue;
                //map_error("Cannot get cell PRINT_MAP");
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
            /*if(get_cell(curr, &c, map) == -1) 
                game_error("Cannot get cell");*/
            if((c = get_cell(curr,map)) == NULL)
                continue;
                //map_error("Cannot get cell PLACE_SHIP");
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
				/*if(insert_cell(curr, s, map) < 0)
					game_error("Cannot insert ship");*/
                if((cell = get_cell(curr, map)) == NULL)
                  //  map_error("");
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

	//int dim = get_dim(adv->map);
	int pos = c.i*dim + c.j; // bidimensional index to unidimensional conversion
	if(pos < 0 || pos >= dim*dim ){ // out of bounds
		printf("Invalid coordinate. Try again!\n");
		return -1;
	}
  /*  if(get_cell(c, &curr_cell, curr->map) == -1){
        game_error("Cannot get cell");
    } */

    if((curr_cell = get_cell(c,curr->map)) == NULL){
        map_error("Cannot get cell ATTACK CURR");
    }
        
        
	if (curr_cell->atk_cell != UNKNOWN){
		printf("\nThis position was previously attacked. Try again!\n");
		delay(1);
		return -1;
	}
    /*if(get_cell(c, &adv_cell, adv->map) == -1){
        game_error("Cannot get cell");
    } */

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
		//set_atk_cell(c, curr->map, MISS);
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
	//	system("cls || clear");
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

// main menu and game initializer
int main(){
	//int dim;	// map dimension (dim * dim)
	int n_ships; // number of ships to be placed
	int mode;	// 0 -> RANDOM / 1 -> MANUAL
	PLAYER *p1, *p2;
	int *game_shapes;
	srand ( time(NULL) );	// seed the random number generator
	//system("cls || clear");
	printf("===============================\n#####=====BATTLESHIP======#####\n===============================\n\n");

start_game:
	printf("Select the map generation mode:\n0 -> RANDOM\n1 -> MANUAL\n>> ");
	scanf("%d",&mode);

	if(mode==0){ // RANDOM
		dim = rand() % (MAX_DIM - MIN_DIM + 1) + MIN_DIM;
		printf("Map dimension: %d x %d\n",dim,dim);
		n_ships = (dim*dim) / (BMAP_SIZE*BMAP_SIZE);
		game_shapes = gen_game_shapes(n_ships);
		getchar();
		input_players(&p1, &p2, n_ships, game_shapes, RANDOM);
		free(game_shapes);

	}
	else if(mode==1){ // MANUAL
manual_mode:
		printf("Enter the map dimension (20-40) >> ");
		scanf("%d",&dim);
		if(dim < MIN_DIM || dim > MAX_DIM) {
			printf("Invalid map dimension! Input a number between 20 and 40.\n");
			goto manual_mode;
		}
		getchar();
		n_ships = (dim*dim) / (BMAP_SIZE*BMAP_SIZE);
		game_shapes = gen_game_shapes(n_ships);
		input_players(&p1, &p2, n_ships, game_shapes, MANUAL);
		free(game_shapes);
	}
	else{ // INVALID
		printf("Invalid option. Try again.\n");
		goto start_game;
	}

	play(p1, p2);

	exit(EXIT_SUCCESS);

}
