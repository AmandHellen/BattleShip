#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "map.h"
#include "ship.h"

typedef struct player{
    int n_ships; //remaining ships
    BOOL playing; //if it is this players turn or not
    MAP *map;
    //strategy ?
}PLAYER;

//-----------------------------------------------------
PLAYER *create_player(int, int, MODE, BOOL);

//SHIP *get_ships(int, int **, MODE);initiliaze

MAP *fill_map(TILE **, int, MODE);

SHIP *get_ship(void);

BOOL place_ship(SHIP *, TILE **);

static void player_error(char *);

//-----------------------------------------------------
PLAYER *create_player(int dim, int n_ships, MODE mode, BOOL playing){
    /*PLAYER *p = (PLAYER*)malloc(sizeof(PLAYER));
    if(p == NULL){player_error("No memory");}
    TILE **empty_map = create_empty_map(dim);
    p -> map = fill_map(empty_map, n_ships, mode);
    p -> n_ships = n_ships;
    p -> playing = playing;
    return p;*/
}

MAP *fill_map(TILE **empty_map, int n_ships, MODE mode){
    SHIP *ships[n_ships];
    BOOL placed;
    SHIP *new_ship;
    
    for(int i=0; i<n_ships; i++){
        input_ship:
            new_ship = get_ship();
            placed = place_ship(new_ship, empty_map);
            if (placed == FALSE){goto input_ship;}
            ships[i] = new_ship;
    }
    MAP *map = create_map(ships, empty_map);
    return map;
}

SHIP *get_ship(void){
    COORD begin, end;
    int positions[4];
    char *prompts[4] = {"xi: ", "yi: " , "xf: ", "yf: "};

    for(int i = 0; i < 4; i++){
        printf("%s", prompts[i]);
        scanf("%d", &positions[i]);
        printf("\n");
    }

    begin.x = positions[0];
    begin.y = positions[1];
    end.x = positions[2];
    end.y = positions[3];
    SHIP *s = create_ship(begin, end);
    return s;
}

BOOL place_ship(SHIP *s, TILE **matrix){
    if (s -> dir == HORIZONTAL){
        for(int i=0; i<s -> size; i++){
            if (matrix[s -> begin.x][i] == 0){
                matrix[s -> begin.x][i] = FILLED;
            }
            else{
                return FALSE;
            }
        }
        return TRUE;
    }
    return TRUE;
}

static void player_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}

#endif
