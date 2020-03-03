#ifndef SHIP_H
#define SHIP_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct ship{
    int xi, yi, xf, yf;
    int size;
    int hits;   // how many attacks suffered
    BOOL sunk; // FALSE -> alive / TRUE -> dead
}SHIP;

//-------------------------------------------------------
static void ship_error(char *msg);

static int calculate_size(int xi, int yi, int xf, int yf);

SHIP *create_ship(int xi, int yi, int xf, int yf);

void free_ship(SHIP *s);

void set_size(SHIP *s, int xi, int yi, int xf, int yf);

//---------------------------------------------------------------

static int calculate_size(int xi, int yi, int xf, int yf){
    if(xi == xf){ //Vertical
        return yf - yi;
    }
    else if(yi == yf){ //Horizontal
        return xf - xi;
    }
    return -1;
}

//Call this when there is a memory related error
static void ship_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}

SHIP *create_ship(int xi, int yi, int xf, int yf){ // VERIFICAR COORDENANDAS CORRECTAS
    SHIP *s = (SHIP *)malloc(sizeof(SHIP));
    if (s == NULL){ship_error("No memory");}
    set_size(s,xi,yi,xf,yf);
    s -> xi = xi;
    s -> yi = yi;
    s -> xf = xf;
    s -> yf = yf;
    s -> hits = 0;
    s -> sunk = FALSE;
    return s;
}

void set_size(SHIP *s, int xi, int yi, int xf, int yf){
    int size = calculate_size(xi,yi,xf,yf);
    if (size == -1){
        ship_error("Invalid ship coordinates");
        free_ship(s);
    }
    else{
        s -> size = size;
    }
}

//Destroys the structure
void free_ship(SHIP *s){
    if(s != NULL){
        free(s);
    }else{
        ship_error("The ship was badly generated");
    }
}

#endif
