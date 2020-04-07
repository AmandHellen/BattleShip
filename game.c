#include "game.h"

int random_bitmap(){
	return rand() % NSHAPES;
}

/*
void print_shape(char *bitmap){
	for(int i=0; i<BMAP_SIZE; i++){
		if(i % 5 == 0){
			printf("\n");
		}
		printf("%c",bitmap[i]);
	}
	printf("\n");
}
*/

int main(){
	int dim;	// map dimension (dim * dim)
	int n_ships; // number of ships to be placed 	
	int mode;	// 0 -> RANDOM / 1 -> MANUAL
	bool finished = false;	

start_game:
	printf("Select the map generation mode:\n0 -> RANDOM\n1 -> MANUAL\n>> ");
	scanf("%d",&mode);

	if(mode==0){ // RANDOM
		printf("random\n");
	}
	else if(mode==1){ // MANUAL
		scanf("%d",&dim);
		n_ships = dim*dim / BMAP_SIZE;

		int game_shapes[n_ships];
		for(int i=0; i<n_ships; i++){
			game_shapes[i] = random_bitmap();
		}

		PLAYER *p1 = create_player(dim, n_ships, game_shapes, MANUAL, true);
		print_dashboard(p1);
	}
	else{ // INVALID
		printf("Invalid option. Try again.\n");
		goto start_game;
	}
	

/*
	for(int i=0; i<n_ships; i++){
		int shape = game_shapes[i];
		print_shape(bitmaps[shape].bitmap);
	}*/


	
//	print_map(p1.map);
	return 0;

}