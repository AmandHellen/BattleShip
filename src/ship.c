#include "ship.h"
/*
SHAPE shapes[NSHAPES] = {{"..X....X....X....X....X..\0"},
                         {".......X....X....X.......\0"},
                         {"............X............\0"},
                         {"XXXXX..X....X....X....X..\0"},
                         {"...X....X..XXX..X....X...\0"}};
*/

SHAPE shapes[NSHAPES] = {{".......X....X....X.......\0"}};

// returns a new instance of SHIP
SHIP *create_ship(char *bitmap, int shape_ind, int rot, COORD c){
    SHIP *s = (SHIP *)malloc(sizeof(SHIP));
    if (s == NULL){ship_error("Failed to allocate memory for SHIP");}
    s -> size = calculate_size(bitmap);
    s -> hits = 0;
    s -> sunk = false;
    s -> rot = rot % 4;
    s -> shape = shape_ind;
    s -> bmap_begin = c;
    return s;
}

//returns the size of the ship (filled cells on the bitmap)
int calculate_size(char *bitmap){
    int size = 0;
    for(int i=0; i < BMAP_SIZE*BMAP_SIZE; i++){
        if(bitmap[i] == 'X') size++;
    }
    return size;
}

//Destroys the structure
void free_ship(SHIP *s){
    if(s != NULL){
        free(s);
    }else{
        ship_error("Cannot free SHIP (NULL)");
    }
}

//Call this when there is a memory related error
void ship_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}
