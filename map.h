#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "types.h"

#define MIN_DIM 10 
#define MAX_DIM 40

typedef struct tile{
    STATE state;
    SHIP* ship;
}TILE;

typedef struct map{
    TILE *matrix; // 0 -> EMPTY / 1 -> FILLED / 2 -> ALREADY HIT
    int dim;
}MAP;

//---------------------------------------------------
MAP *create_map(int);

void print_map(MAP*);

void free_map(MAP *);

void map_error(char *);

//---------------------------------------------------



#endif
