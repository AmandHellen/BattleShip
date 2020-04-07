#include "player.h"

// returns a new instance of PLAYER
PLAYER *create_player(int dim, int n_ships, MODE mode, bool playing){
    /*PLAYER *p = (PLAYER*)malloc(sizeof(PLAYER));
    if(p == NULL){player_error("No memory");}
    TILE **empty_map = create_empty_map(dim);
    p -> map = fill_map(empty_map, n_ships, mode);
    p -> n_ships = n_ships;
    p -> playing = playing;
    return p;*/
}   

/*
keep generating ships (or asking for them) and placing them on the 2D matrix
return a new instance of MAP with that matrix
*/
MAP *fill_map(TILE **empty_map, int n_ships, MODE mode){
    SHIP *ships[n_ships];
    bool placed;    // if the ship is successfully placed
    SHIP *new_ship;
    for(int i=0; i<n_ships; i++){
        input_ship:
            /*if (mode == RANDOM){
                new_ship = generate_ship();
            }
            else{
                new_ship = get_ship();
            }*/
            new_ship = get_ship();
            if (new_ship == NULL){
                printf("ERROR: The ship direction must be either HORIZONTAL or VERTICAL. Try again.\n");
                goto input_ship; // try again
            }
            placed = place_ship(new_ship, empty_map);
            if (placed == FALSE){
                printf("ERROR: The ship is colliding with another ship in the map. Try again.\n");
                goto input_ship; // try again
            }
            ships[i] = new_ship;
    }
    MAP *map = create_map(ships, empty_map);
    return map;
}

// prompts the player for the new ship coordinates and returns the ship
SHIP *get_ship(void){
    COORD begin, end;
    int positions[4]; // [xi, yi, xf, yf]
    char *prompts[4] = {"xi: ", "yi: " , "xf: ", "yf: "}; // sequence of prompts

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

// checks the matrix for collisions and place the ship if there's none (POR ACABAR)
bool place_ship(SHIP *s, TILE **matrix){
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

// Destroys the structure
void free_player(PLAYER *p){
    if (p != NULL){
        free_map(p -> map);
        free(p);
    }
    else{
        player_error("The player was badly generated");
    }
}

// Call this when there is a memory related error
void player_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}
