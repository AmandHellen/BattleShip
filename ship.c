#include "ship.h"

// returns a new instance of SHIP or NULL if the coordinates are illegal (diagonal)
SHIP *create_ship(COORD begin, COORD end){
    SHIP *s = (SHIP *)malloc(sizeof(SHIP));
    if (s == NULL){ship_error("No memory");}
    int ok = set_size(s, begin, end);
    if (ok){
        s -> begin = begin;
        s -> end = end;
        s -> hits = 0;
        s -> sunk = FALSE;
    }
    return s;
}

// update the ship size and direction
int set_size(SHIP *s, COORD begin, COORD end){
    int size = calculate_size(s, begin, end);
    if (size == -1){ //if the direction is neither horizontal or vertical
        ship_error("Invalid ship coordinates");
        free_ship(s);
        return 0;
    }
    else{
        s -> size = size;
        return 1;
    }
}

// set the SHIP direction and calculate the size
static int calculate_size(SHIP *s, COORD begin, COORD end){
    if(begin.x == end.x){ //Vertical
        s -> dir = VERTICAL;
        return abs(end.y - begin.y);
    }
    else if(begin.y == end.y){ //Horizontal
        s -> dir = HORIZONTAL;
        return abs(end.x - begin.x);
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
