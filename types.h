#ifndef TYPES_H
#define TYPES_H

typedef enum {FALSE, TRUE} BOOL;

typedef enum {RANDOM, MANUAL} MODE;

typedef enum {EMPTY, FILLED, HIT} TILE;

typedef enum {HORIZONTAL, VERTICAL} DIR;

typedef struct coord{
    int x, y;
}COORD;

#endif
