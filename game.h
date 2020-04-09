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

void play(PLAYER *, PLAYER *);

COORD input_coord(void);

//-----------------------------------------------------------

#endif 