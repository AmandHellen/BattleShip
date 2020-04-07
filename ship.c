#include "ship.h"

SHAPE shapes[NSHAPES] = {{"XXXXX..X....X....X....X..\0"},
                         {"..X....X....X....X....X..\0"},
                         {"....X....XXXXXXX....X....\0"},
                         {"..X....X....XXX..X....X..\0"},
                         {".......X....X....X.......\0"},
                         {"X....X....X....X....XXXXX\0"},
                         {"X...XX...XX...XX...XXXXXX\0"},
                         {"X...XX...XXXXXXX...XX...X\0"},
                         {"XXXXX...X...X...X...XXXXX\0"}
                        };

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
    for(int i=0; i < BMAP_SIZE; i++){
        if(bitmap[i] == 'X') size++;
    }
    return size;
}

int rotate_point(int i, int j, int r){
    switch(r % 4){
        case 0: return i * BMAP_SIZE + j;
        case 1: return 20 + i - (j * BMAP_SIZE);
        case 2: return 24 - (i * BMAP_SIZE) - j;
        case 3: return 4 - i + (j * BMAP_SIZE);
    }
    return 0;
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
