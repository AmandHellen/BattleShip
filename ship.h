#ifndef SHIP_H
#define SHIP_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define BMAP_SIZE 25

typedef struct ship{
    int size;
    int hits;   // how many attacks suffered
    bool sunk; // FALSE -> alive / TRUE -> dead
}SHIP;

//--------------------------------------------------------------

SHIP *create_ship(char *);

int calculate_size(char *);

void free_ship(SHIP *);

void ship_error(char *);

//---------------------------------------------------------------

#endif
