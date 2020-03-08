#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "types.h"

typedef struct map{
    SHIP **ships;
    TILE **matrix; // 0 -> EMPTY / 1 -> FILLED / 2 -> ALREADY HIT
}MAP;

//---------------------------------------------------
MAP *create_map(SHIP **, TILE **);

TILE **create_empty_map(int);

void free_map(MAP *);

static void map_error(char *);

//---------------------------------------------------
TILE **create_empty_map(int dim){
    TILE **matrix;
    matrix = malloc(sizeof(TILE*)*dim);
    for(int i=0; i<dim; i++){
        matrix[i] = malloc(sizeof(TILE*)*dim);
    }
    //initialize all the positions as 0 (empty)
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            matrix[i][j] = EMPTY;
        }
    }
    return matrix;
}

MAP *create_map(SHIP **ships, TILE **matrix){
    MAP *m = (MAP*)malloc(sizeof(MAP));
    if(m == NULL){map_error("No memory");}
    m -> ships = ships;
    m -> matrix = matrix;
    return m;
}

void free_map(MAP *m){
    if(m != NULL){
        free(m -> ships);
        free(m -> matrix);
        free(m);
    }else{
        map_error("The map was badly generated.");
    }
}

static void map_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}

#endif
