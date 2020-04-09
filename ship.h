#ifndef SHIP_H
#define SHIP_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define BMAP_SIZE 5 // a bitmap is always a 5x5 matrix
#define NSHAPES 7	 // number of different ship shapes

typedef struct shape{	// a struct containing a bitmap 
	char bitmap[BMAP_SIZE*BMAP_SIZE+1];
}SHAPE;

typedef struct ship{
    int size;
    int hits;   // how many attacks suffered
    bool sunk; // FALSE -> alive / TRUE -> dead
}SHIP;

//	all possible shapes 
extern SHAPE shapes[NSHAPES];

//--------------------------------------------------------------

SHIP *create_ship(char *);

int calculate_size(char *);

void free_ship(SHIP *);

void ship_error(char *);

//---------------------------------------------------------------

#endif
