#include "game.h"
#include "player.h"
#include "ship.h"

#define NSHAPES 9


typedef struct shape_ships{
	char bitmap[BMAP_SIZE+1];
}SHAPE_SHIPS;

SHAPE_SHIPS bitmaps[NSHAPES] = {{"XXXXX..X....X....X....X..\0"},
							    {"..X....X....X....X....X..\0"},
							    {"....X....XXXXXXX....X....\0"},
							    {"..X....X....XXX..X....X..\0"},
							    {".......X....X....X.......\0"},
							    {"X....X....X....X....XXXXX\0"},
							    {"X...XX...XX...XX...XXXXXX\0"},
							    {"X...XX...XXXXXXX...XX...X\0"},
							    {"XXXXX...X...X...X...XXXXX\0"}
							   };

int random_bitmap(){
	return rand() % NSHAPES;
}

void print_shape(char *bitmap){
	for(int i=0; i<BMAP_SIZE; i++){
		if(i % 5 == 0){
			printf("\n");
		}
		printf("%c",bitmap[i]);
	}
	printf("\n");
}

int main(){
	int dim;
	scanf("%d",&dim);
	int n_ships = dim*dim / BMAP_SIZE;


	int game_shapes[n_ships];
	for(int i=0; i<n_ships; i++){
		game_shapes[i] = random_bitmap();
	}

	for(int i=0; i<n_ships; i++){
		int shape = game_shapes[i];
		print_shape(bitmaps[shape].bitmap);
	}


	//PLAYER *p1 = create_player(dim,n_ships,MANUAL,true);
//	print_map(p1.map);
	return 0;

}