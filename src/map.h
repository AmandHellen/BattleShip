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

//---------------------------------------------------
MAP create_map(int);

int get_dim(MAP);

//SHIP *get_ship(MAP, COORD);

int insert_ship(COORD, SHIP*, MAP);

//ATTACK get_atk_cell(COORD, MAP);

int get_cell(COORD, CELL *, MAP);

//ATTACK get_atk(CELL);
/*
void set_atk_cell(COORD, MAP, ATTACK);

void inc_hit_count(COORD, MAP);
*/

void print_strategy(MAP , MAP);

void print_map(MAP);

int rotate_point(int, int, int, int);

void remove_ship(MAP, int, int, int, int);

void free_map(MAP);

void map_error(char *);

//---------------------------------------------------

#endif
