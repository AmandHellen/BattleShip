#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "types.h"

#define MIN_DIM 10 
#define MAX_DIM 40

typedef struct tile{
    STATE state; // 0 -> EMPTY / 1 -> FILLED / 2 -> HIT / 3 -> MISS
    SHIP* ship;	// in case there's a ship in this tile
}TILE;

typedef struct map{
    TILE *matrix; 
    int dim;
}MAP;

//---------------------------------------------------
MAP *create_map(int);

void print_map(MAP*);

void free_map(MAP *);

void map_error(char *);

//---------------------------------------------------

#endif