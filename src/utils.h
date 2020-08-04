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

unsigned char *serialize_int(unsigned char *, int);

unsigned char *serialize_char(unsigned char *, char);

int deserialize_int(unsigned char *);

char deserialize_char(unsigned char*);

#endif
