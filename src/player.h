#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
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

void print_dashboard(PLAYER *);

void free_player(PLAYER *);

void player_error(char *);

void gen_rand_moves(int *, int);

//-----------------------------------------------------

#endif
