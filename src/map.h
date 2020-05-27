#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "utils.h"

#define MIN_DIM 10
#define MAX_DIM 40

typedef struct map *MAP;

typedef struct cell{
    ATTACK atk_cell; //0 -> UNKNOWN / 1 -> HIT / 2 -> MISS
    STATE state; // 0 -> EMPTY / 1 -> FILLED
    SHIP* ship;	// in case there's a ship in this tile
}CELL;

int dim;

//---------------------------------------------------
MAP create_map(int);

int get_dim(MAP);

int insert_cell(COORD, SHIP*, MAP);

int rotate_point(int, int, int, int);

void print_strategy(MAP , MAP);

CELL *get_cell(COORD, MAP);

void remove_ship(MAP, int, int, int, int);

void free_map(MAP);

void map_error(char *);

//---------------------------------------------------

#endif
