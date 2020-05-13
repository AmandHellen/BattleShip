#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <ctype.h>
#include <time.h>

typedef enum {RANDOM, MANUAL} MODE; // ship creation mode

typedef enum {EMPTY, FILLED} STATE; // status of each matrix cell

typedef enum {UNKNOWN, HIT, MISS} ATTACK; // strategy 

typedef struct coord{
	int i, j;
}COORD;

void delay(int);

#endif
