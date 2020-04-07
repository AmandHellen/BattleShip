#ifndef SHIP_H
#define SHIP_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct ship{
    COORD begin, end;
    int size;
    int hits;   // how many attacks suffered
    bool sunk; // FALSE -> alive / TRUE -> dead
    DIR dir;    // 0 -> HORIZONTAL / 1 -> VERTICAL
}SHIP;

//--------------------------------------------------------------

SHIP *create_ship(COORD, COORD);

int set_size(SHIP *, COORD, COORD);

static int calculate_size(SHIP *, COORD, COORD);

void free_ship(SHIP *);

static void ship_error(char *);

//---------------------------------------------------------------

#endif
