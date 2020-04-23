#ifndef GAME_H
#define GAME_H 

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "player.h"
#include "ship.h"

//-----------------------------------------------------------

COORD input_coord(void);

int attack(COORD , PLAYER *, PLAYER *);

bool check_state(PLAYER *);

void play(PLAYER *, PLAYER *);

void clean_game(PLAYER *, PLAYER *);

void input_players(PLAYER **, PLAYER **, int, int, int *, MODE);

void game_error(char *);

//-----------------------------------------------------------

#endif 