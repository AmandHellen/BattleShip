#include "ship.h"

// returns a new instance of SHIP or NULL if the coordinates are illegal (diagonal)
SHIP *create_ship(char *bitmap){
    SHIP *s = (SHIP *)malloc(sizeof(SHIP));
    if (s == NULL){ship_error("No memory");}
    s -> size = calculate_size(bitmap);
    s -> hits = 0;
    s -> sunk = false;
    return s;
}

int calculate_size(char *bitmap){
    int size = 0;
    for(int i=0; i<BMAP_SIZE; i++){
        if(bitmap[i] == 'X') size++;
    }
    return size;
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
void ship_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}
