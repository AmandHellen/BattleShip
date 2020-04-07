#ifndef SHIP_H
#define SHIP_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define BMAP_SIZE 25 // a bitmap is always a 5x5 matrix
#define NSHAPES 9	 // number of different ship shapes

typedef struct shape{	// a struct containing a bitmap 
	char bitmap[BMAP_SIZE+1];
}SHAPE;

typedef struct ship{
    int size;
    int hits;   // how many attacks suffered
    bool sunk; // FALSE -> alive / TRUE -> dead
}SHIP;

//	all possible shapes 
SHAPE shapes[NSHAPES] = {{"XXXXX..X....X....X....X..\0"},
					     {"..X....X....X....X....X..\0"},
					     {"....X....XXXXXXX....X....\0"},
			   		     {"..X....X....XXX..X....X..\0"},
					     {".......X....X....X.......\0"},
					     {"X....X....X....X....XXXXX\0"},
					     {"X...XX...XX...XX...XXXXXX\0"},
					     {"X...XX...XXXXXXX...XX...X\0"},
					     {"XXXXX...X...X...X...XXXXX\0"}
						};

//--------------------------------------------------------------

SHIP *create_ship(char *);

int calculate_size(char *);

int rotate_point(int, int, int);

void free_ship(SHIP *);

void ship_error(char *);

//---------------------------------------------------------------

#endif
