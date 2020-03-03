#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "types.h"

typedef struct map{
    int dim;
    SHIP **ships;
}MAP;

static void map_exit_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}

void free_map(MAP *m){
    if(m != NULL){
        free(m -> ships);
        free(m);
    }else{
        map_exit_error("The map was badly generated.");
    }
}

#endif
