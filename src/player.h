#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "types.h"
#include "map.h"
#include "ship.h"

#define NAME_LEN 16

typedef struct player{
    int n_ships; //remaining ships
    MAP *map;
    char name[NAME_LEN];
}PLAYER;

//-----------------------------------------------------
PLAYER *create_player(char *,int, int, int *, MODE);

bool valid_position(char *, int, int, int, int, int, char *, MAP *);

int rotate_point(int, int, int);

void draw_ship(char *, MAP *, char *, int, int, int, int, int);

void draw_field(char *, int);

MAP *fill_map(MAP *, int, int *, MODE);

MAP *fill_rand_map(MAP *, int, int *, MODE);

bool place_ship(char *, MAP *, char *, int, int, int);

void print_dashboard(PLAYER *);

void free_player(PLAYER *);

void player_error(char *);

void gen_rand_moves(int *, int);

//-----------------------------------------------------

#endif