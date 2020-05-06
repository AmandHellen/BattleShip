#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "utils.h"

#define MIN_DIM 20
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

void print_strategy(MAP *);

void print_map(MAP*);

bool valid_position(char *, int, int, int, int, int, char *, MAP *);

int rotate_point(int, int, int, int);

void draw_ship(char *, MAP *, char *, int, int, int, int, int);

void draw_field(char *, int);

void gen_rand_moves(int, int*, int);

char *gen_map_repr(int);

char get_keypress(int, char*);

char get_rand_keypress(int);

MAP *fill_map(MAP *, int, int *, MODE);

bool place_ship(int, char *, MAP *, char *, int, int, int);

void remove_ship(MAP *, int, int, int, int);

void free_map(MAP *);

void map_error(char *);

//---------------------------------------------------

#endif
