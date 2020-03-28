#ifndef TYPES_H
#define TYPES_H

typedef enum {FALSE, TRUE} BOOL;

typedef enum {RANDOM, MANUAL} MODE; // ship creation mode

typedef enum {EMPTY, FILLED, HIT} STATE; // status of each matrix cell

typedef enum {HORIZONTAL, VERTICAL} DIR; // ship orientation

typedef struct coord{
    int x, y;
}COORD;

#endif
