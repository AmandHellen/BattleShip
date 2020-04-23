#include "game.h"

COORD input_coord(){
	COORD c;
	printf("Enter the attack coordinate:\n");
	printf("Line >> ");
	scanf("%d", &c.i);
	printf("Column >> ");
	scanf("%d", &c.j);
	return c;
}

int attack(COORD c, PLAYER *curr, PLAYER *adv){
	int dim = adv->map->dim;
	int pos = c.i*dim + c.j;

	if(pos < 0 || pos >= dim*dim ){
		printf("Invalid coordinate. Try again!\n");
		return -1;
	}
	STATE state = adv->map->matrix[pos].state;
	switch(state){
		case EMPTY:
			printf("You missed!\n");
			adv->map->matrix[pos].state = MISS;
			return 0;
		case FILLED:
			printf("HIT!\n");
			adv->map->matrix[pos].state = HIT;
			adv->map->matrix[pos].ship->hits++;
			if(adv->map->matrix[pos].ship->size == adv->map->matrix[pos].ship->hits)
				adv->n_ships--;
			return 1;
		case HIT:
			printf("This position was previously attacked. Try again!\n");
			return -1;
		case MISS:
			printf("This position was previously attacked. Try again!\n");
			return -1;
	}

	return 0;
}

bool check_state(PLAYER *adv){
	return adv->n_ships == 0;
}

void play(PLAYER *p1, PLAYER *p2){
	bool finished = false;
	COORD c;
	PLAYER *curr_player = p1;
	PLAYER *other_player = p2;
	PLAYER *aux_player;

	while(!finished){
input_attack: 
		system("clear");
		print_dashboard(curr_player);
		//print_map(other_player->map);
		printf("\nNow playing: %s\n", curr_player->name);
		c = input_coord();
		int attack_result = attack(c, curr_player, other_player); 
		if( attack_result == 1){
			finished = check_state(other_player);
			if(finished) continue;
		}else if(attack_result == -1)
			goto input_attack;

		aux_player = curr_player;
		curr_player = other_player;
		other_player = aux_player;		
	}

	exit_game(p1, p2);
}

void exit_game(PLAYER *curr, PLAYER *adv){
	printf("Congratulations, %s! You win!\n", curr->name);
	clean_game(curr, adv);
}

void clean_game(PLAYER *curr, PLAYER *adv){
	free_player(curr);
	free_player(adv);
	exit(EXIT_SUCCESS);
}

void input_players(PLAYER **p1, PLAYER **p2, int dim, int n_ships, int *game_shapes, MODE mode){
	char name[NAME_LEN];

	printf("Player 1: type your name >> ");
	fgets(name, NAME_LEN, stdin);
	name[strcspn(name ,"\n")] = 0;
	if (mode == RANDOM) printf("Randomly filling %s's map...\n", name);
	*p1 = create_player(name, dim, n_ships, game_shapes, mode);
	printf("Player 2: type your name >> ");
	fgets(name, NAME_LEN, stdin);
	name[strcspn(name ,"\n")] = 0;
	if (mode == RANDOM) printf("Randomly filling %s's map...\n", name);
	*p2 = create_player(name, dim, n_ships, game_shapes, mode);
}

int main(){
	int dim;	// map dimension (dim * dim)
	int n_ships; // number of ships to be placed 	
	int mode;	// 0 -> RANDOM / 1 -> MANUAL
	PLAYER *p1, *p2;
	srand ( time(NULL) );	// seed the random number generator 7
	system("clear");
	printf("===============================\n#####=====BATTLESHIP======#####\n===============================\n\n");

start_game:
	printf("Select the map generation mode:\n0 -> RANDOM\n1 -> MANUAL\n>> ");
	scanf("%d",&mode);

	if(mode==0){ // RANDOM
		dim = rand() % (MAX_DIM - MIN_DIM + 1) + MIN_DIM;
		printf("Map dimension: %d x %d\n",dim,dim);
		n_ships = (dim*dim) / (BMAP_SIZE*BMAP_SIZE);
		int *game_shapes = (int*)malloc(sizeof(int)*n_ships);
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
		int *game_shapes = (int*)malloc(sizeof(int)*n_ships);
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

	return 0;

}