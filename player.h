#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "map.h"

typedef struct player{
    int n_ships; //remaining ships
    BOOL playing; //if it is this players turn or not
    MAP *map;
    //strategy ?
}PLAYER;

//-----------------------------------------------------
PLAYER *create_player(int, int, MODE);

//-----------------------------------------------------
PLAYER *create_player(int dim, int n_ships, MODE mode){

}

#endif
