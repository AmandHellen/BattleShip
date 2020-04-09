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

int attack(){

}

void play(PLAYER *p1, PLAYER *p2){
	bool finished = false;
	COORD c;
	PLAYER *curr_player = p1;
	PLAYER *other_player = p2;
	PLAYER *aux_player;

	while(!finished){
		c = input_coord();
		if(attack()){
			finished = update_player(other_player, c);
			aux_player = curr_player;
			curr_player = other_player;
			other_player = aux_player;

		}else{
			//deu ruim
			//pedir outra coordenada
		}
		
	}

	//exit game
}

int main(){
	int dim;	// map dimension (dim * dim)
	int n_ships; // number of ships to be placed 	
	int mode;	// 0 -> RANDOM / 1 -> MANUAL
	
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
		n_ships = (dim*dim) / (BMAP_SIZE*BMAP_SIZE);
		int game_shapes[n_ships];
		for(int i=0; i<n_ships; i++){
			game_shapes[i] = random_bitmap();
		}

		printf("Player 1: place your ships!\n");
		PLAYER *p1 = create_player(dim, n_ships, game_shapes, MANUAL);
		printf("Player 2: place your ships!\n");
		PLAYER *p2 = create_player(dim, n_ships, game_shapes, MANUAL);
		
		play(p1, p2);
	}
	else{ // INVALID
		printf("Invalid option. Try again.\n");
		goto start_game;
	}

	return 0;

}