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

/*
executes the attack by curr player on the adv player map and checks the game state
Returns 0 for misses, 1 for hits and -1 in case the coordinate was previously tried
*/
int attack(COORD c, PLAYER *curr, PLAYER *adv){
	int dim = adv->map->dim;
	int pos = c.i*dim + c.j; // bidimensional index to unidimensional conversion

	if(pos < 0 || pos >= dim*dim ){ // out of bounds
		printf("Invalid coordinate. Try again!\n");
		return -1;
	}
	STATE state = adv->map->matrix[pos].state;
	switch(state){
		case EMPTY:
			printf("\nYou missed!\n");
			delay(1);
			adv->map->matrix[pos].state = MISS;
			return 0;
		case FILLED:
			printf("\nHIT!\n");
			delay(1);
			adv->map->matrix[pos].state = HIT; // update the opponent's map state
			adv->map->matrix[pos].ship->hits++; // update the opponent's ship hit count
			if(adv->map->matrix[pos].ship->size == adv->map->matrix[pos].ship->hits)
				adv->n_ships--; // decrement the opponent's ship count when a ship is sunk
			return 1;
		case HIT:
			printf("\nThis position was previously attacked. Try again!\n");
			delay(1);
			return -1;
		case MISS:
			printf("\nThis position was previously attacked. Try again!\n");
			delay(1);
			return -1;
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
		system("clear");
		print_dashboard(curr_player, other_player);
		//print_map(other_player->map);
		printf("\nNow playing: %s\n", curr_player->name);
		c = input_coord();
		int attack_result = attack(c, curr_player, other_player);
		if( attack_result == 1){ // HIT
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

// prompts the players for their names and fills their maps (RANDOM or MANUAL)
void input_players(PLAYER **p1, PLAYER **p2, int dim, int n_ships, int *game_shapes, MODE mode){
	char name[NAME_LEN];

	printf("Player 1: type your name >> ");
	fgets(name, NAME_LEN, stdin);
	name[strcspn(name ,"\n")] = 0;
	if (mode == RANDOM) printf("Randomly filling %s's map...\n", name);
	*p1 = create_player(name, dim, n_ships, game_shapes, mode);
	if (mode == RANDOM) printf("%s's map successfully generated.\n", name);

	printf("Player 2: type your name >> ");
	fgets(name, NAME_LEN, stdin);
	name[strcspn(name ,"\n")] = 0;
	if (mode == RANDOM) printf("Randomly filling %s's map...\n", name);
	*p2 = create_player(name, dim, n_ships, game_shapes, mode);
	if (mode == RANDOM) printf("%s's map successfully generated.\n", name);
	delay(1);
}

// Call this in case of error
void game_error(char *msg){
	fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}

// main menu and game initializer
int main(){
	int dim;	// map dimension (dim * dim)
	int n_ships; // number of ships to be placed
	int mode;	// 0 -> RANDOM / 1 -> MANUAL
	PLAYER *p1, *p2;
	srand ( time(NULL) );	// seed the random number generator
	system("clear");
	printf("===============================\n#####=====BATTLESHIP======#####\n===============================\n\n");

start_game:
	printf("Select the map generation mode:\n0 -> RANDOM\n1 -> MANUAL\n>> ");
	scanf("%d",&mode);

	if(mode==0){ // RANDOM
		dim = rand() % (MAX_DIM - MIN_DIM + 1) + MIN_DIM;
		printf("Map dimension: %d x %d\n",dim,dim);
		n_ships = (dim*dim) / (BMAP_SIZE*BMAP_SIZE);
		int *game_shapes = (int*)malloc(sizeof(int)*n_ships); // random ships
		if (game_shapes == NULL)
			game_error("Failed to allocate memory for GAME_SHAPES");
		for(int i=0; i<n_ships; i++){
			game_shapes[i] = rand() % NSHAPES;
		}
		getchar();
		input_players(&p1, &p2, dim, n_ships, game_shapes, RANDOM);
		free(game_shapes);

	}
	else if(mode==1){ // MANUAL
manual_mode:
		printf("Enter the map dimension (10-40) >> ");
		scanf("%d",&dim);
		if(dim < MIN_DIM || dim > MAX_DIM) {
			printf("Invalid map dimension! Input a number between 10 and 40.\n");
			goto manual_mode;
		}
		getchar();
		n_ships = (dim*dim) / (BMAP_SIZE*BMAP_SIZE);
		int *game_shapes = (int*)malloc(sizeof(int)*n_ships); // random ships
		if (game_shapes == NULL)
			game_error("Failed to allocate memory for GAME_SHAPES");
		for(int i=0; i<n_ships; i++){
			game_shapes[i] = rand() % NSHAPES;
		}
		input_players(&p1, &p2, dim, n_ships, game_shapes, MANUAL);
		free(game_shapes);
	}
	else{ // INVALID
		printf("Invalid option. Try again.\n");
		goto start_game;
	}

	play(p1, p2);

	exit(EXIT_SUCCESS);

}
