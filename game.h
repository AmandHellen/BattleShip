#ifndef GAME_H
#define GAME_H 

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "player.h"
#include "ship.h"

//-----------------------------------------------------------
int random_bitmap(void);

COORD input_coord(void);

int attack(COORD , PLAYER *, PLAYER *);

bool check_state(PLAYER *);

void play(PLAYER *, PLAYER *);

void exit_game(PLAYER *, PLAYER *);

void clean_game(PLAYER *, PLAYER *);

//-----------------------------------------------------------

#endif 