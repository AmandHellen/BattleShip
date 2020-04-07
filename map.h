#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "types.h"

typedef struct tile{
    STATE state;
    SHIP* ship;
}TILE;

typedef struct map{
    TILE *matrix; // 0 -> EMPTY / 1 -> FILLED / 2 -> ALREADY HIT
}MAP;

//---------------------------------------------------
MAP *create_map(int);

void free_map(MAP *);

void map_error(char *);

//---------------------------------------------------



#endif
