#ifndef SHIP_H
#define SHIP_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct ship{
    COORD begin, end;
    int size;
    int hits;   // how many attacks suffered
    BOOL sunk; // FALSE -> alive / TRUE -> dead
    DIR dir;    // 0 -> HORIZONTAL / 1 -> VERTICAL
}SHIP;

//--------------------------------------------------------------

SHIP *create_ship(COORD, COORD);

void set_size(SHIP *, COORD, COORD);

static int calculate_size(SHIP *, COORD, COORD);

void free_ship(SHIP *);

static void ship_error(char *);

//---------------------------------------------------------------

SHIP *create_ship(COORD begin, COORD end){ // VERIFICAR COORDENANDAS CORRECTAS
    SHIP *s = (SHIP *)malloc(sizeof(SHIP));
    if (s == NULL){ship_error("No memory");}
    set_size(s, begin, end);
    s -> begin = begin;
    s -> end = end;
    s -> hits = 0;
    s -> sunk = FALSE;
    return s;
}

void set_size(SHIP *s, COORD begin, COORD end){
    int size = calculate_size(s, begin, end);
    if (size == -1){
        ship_error("Invalid ship coordinates");
        free_ship(s);
    }
    else{
        s -> size = size;
    }
}

static int calculate_size(SHIP *s, COORD begin, COORD end){
    if(begin.x == end.x){ //Vertical
        s -> dir = VERTICAL;
        return end.y - begin.y;
    }
    else if(begin.y == end.y){ //Horizontal
        s -> dir = HORIZONTAL;
        return end.x - begin.x;
    }
    return -1;
}

//Destroys the structure
void free_ship(SHIP *s){
    if(s != NULL){
        free(s);
    }else{
        ship_error("The ship was badly generated");
    }
}

//Call this when there is a memory related error
static void ship_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}

#endif
