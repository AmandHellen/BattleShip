#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <ctype.h>

typedef enum {RANDOM, MANUAL} MODE; // ship creation mode

typedef enum {EMPTY, FILLED, HIT, MISS} STATE; // status of each matrix cell

typedef struct coord{
	int i, j;
}COORD;

#endif
