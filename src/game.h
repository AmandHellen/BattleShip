#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "player.h"
#include "map.h"
#include "ship.h"

//-----------------------------------------------------------

COORD input_coord(void);

bool valid_position(char *, int, int, int, int, int, char *, MAP );

void draw_ship(char *, MAP , char *, int, int, int, int, int);

void draw_field(char *);

char *gen_map_repr(void);

char get_keypress(char*);

void print_map(MAP);


char get_rand_keypress(int);

int update_position(char, char**, int*, int*, int*, int, int, char*, MAP, int*, int*, MODE);

MAP fill_map(MAP, int, int *, MODE);

bool place_ship(int, char *, MAP , char *, int, int, int);

int attack(COORD , PLAYER *, PLAYER *);

bool check_state(PLAYER *);

void play(PLAYER *, PLAYER *);

void clean_game(PLAYER *, PLAYER *);

void input_players(PLAYER **, PLAYER **, int, int *, MODE);

PLAYER *player_input(int , int, int *, MODE);

int *gen_game_shapes(int);

void game_error(char *);

//-----------------------------------------------------------

#endif
