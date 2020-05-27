#include "player.h"

// returns a new instance of PLAYER
PLAYER *create_player(char *name, MAP empty_map, int n_ships, int *game_shapes, MODE mode){
    PLAYER *p = (PLAYER*)malloc(sizeof(PLAYER));
    if(p == NULL){player_error("Failed to allocate memory for PLAYER");}
    memcpy(p -> name,   name, NAME_LEN);
    p -> map = empty_map;
    p -> n_ships = n_ships;
    return p;
}

//prints the current player's strategy (based on the adversary map) and the number of remaining ships
void print_dashboard(PLAYER *curr, PLAYER *adv){
    print_strategy(curr -> map, adv -> map);
    printf("X -> HIT\nM -> MISS\nS -> SUNK\n");
    //print_map(p -> map);
    printf("\n%s's remaining ships: %d\n", curr -> name, curr -> n_ships);
    printf("%s's remaining ships: %d\n", adv -> name, adv -> n_ships);
}

// Destroys the structure
void free_player(PLAYER *p){
    if (p != NULL){
        free_map(p -> map);
        free(p);
    }
    else{
        player_error("Cannot free PLAYER (NULL)");
    }
}

// Call this when there is a memory related error
void player_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}
