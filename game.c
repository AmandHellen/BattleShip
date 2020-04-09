#include "game.h"

int random_bitmap(){
	return rand() % NSHAPES;
}

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
			break;
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
		print_map(curr_player->map);
		c = input_coord();
		if(attack(c, p1, p2) == 1){
			finished = check_state(other_player);
			if(finished)
				continue;
		}else goto input_attack;

		aux_player = curr_player;
		curr_player = other_player;
		other_player = aux_player;
		
	}

	exit_game(curr_player, other_player);
}

void exit_game(PLAYER *curr, PLAYER *adv){
	printf("Congratulations, %s! You win!!!\n", curr->name);
	clean_game(curr, adv);
}

void clean_game(PLAYER *curr, PLAYER *adv){
	free_player(curr);
	free_player(adv);
	exit(EXIT_SUCCESS);
}

int main(){
	int dim;	// map dimension (dim * dim)
	int n_ships; // number of ships to be placed 	
	int mode;	// 0 -> RANDOM / 1 -> MANUAL
	char name[NAME_LEN];
	
	srand ( time(NULL) );	// seed the random number generator 

start_game:
	printf("Select the map generation mode:\n0 -> RANDOM\n1 -> MANUAL\n>> ");
	scanf("%d",&mode);

	if(mode==0){ // RANDOM
		printf("random\n");
	}
	else if(mode==1){ // MANUAL
		printf("Enter the map dimension >> ");
		scanf("%d",&dim);
		getchar();
		n_ships = (dim*dim) / (BMAP_SIZE*BMAP_SIZE);
		int game_shapes[n_ships];
		for(int i=0; i<n_ships; i++){
			game_shapes[i] = random_bitmap();
		}

		printf("Player 1: type your name >> ");
		fgets(name, NAME_LEN, stdin);
		printf("%s: place your ships!\n", name);
		PLAYER *p1 = create_player(name, dim, n_ships, game_shapes, MANUAL);
		printf("Player 2: type your name >> ");
		fgets(name, NAME_LEN, stdin);
		printf("%s: place your ships!\n", name);
		PLAYER *p2 = create_player(name, dim, n_ships, game_shapes, MANUAL);
		
		play(p1, p2);
	}
	else{ // INVALID
		printf("Invalid option. Try again.\n");
		goto start_game;
	}

	return 0;

}