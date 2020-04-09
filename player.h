#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "map.h"
#include "ship.h"

typedef struct player{
    int n_ships; //remaining ships
    MAP *map;
}PLAYER;

//-----------------------------------------------------
PLAYER *create_player(int, int, int *, MODE);

bool valid_position(char *, int, int, int, int, int, char *, MAP *);

int rotate_point(int, int, int);

void draw_ship(char *, MAP *, char *, int, int, int, int, int);

void draw_field(char *, int);

MAP *fill_map(MAP *, int, int *, MODE);

bool place_ship(char *, MAP *, char *, int, int, int);

void print_dashboard(PLAYER *);

void free_player(PLAYER *);

void player_error(char *);

//-----------------------------------------------------


#endif
