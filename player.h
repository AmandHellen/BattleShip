#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "map.h"
#include "ship.h"

typedef struct player{
    int n_ships; //remaining ships
    bool playing; //if it is this players turn or not
    MAP *map;
    //strategy ?
}PLAYER;

//-----------------------------------------------------
PLAYER *create_player(int, int, MODE, bool);

MAP *fill_map(TILE **, int, MODE);

SHIP *get_ship(void);

bool place_ship(SHIP *, TILE **);

void free_player(PLAYER *);

static void player_error(char *);

//-----------------------------------------------------


#endif
