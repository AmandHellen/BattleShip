#include "map.h"

//returns a new instance of MAP
MAP *create_map(int dim){
    MAP *m = (MAP*)malloc(sizeof(MAP));
    if(m == NULL){map_error("Failed to allocate memory for MAP");}
    m -> dim = dim;
    TILE *matrix; // matrix to save the map state
    matrix = (TILE*)malloc(sizeof(TILE)*dim*dim);
    //initialize all the positions as EMPTY
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            matrix[i*dim + j].atk_cell = UNKNOWN;
            matrix[i*dim + j].state = EMPTY;
            matrix[i*dim + j].ship = NULL;
        }
    }
    m -> matrix = matrix;
    return m;
}

void print_strategy(MAP *curr_map, MAP *adv_map){
    int dim = curr_map -> dim;

    printf("  ");
    for (int i = 0; i < dim; i++)
        printf("%.2d ", i);
    printf("\n");

    for(int i=0; i < dim; i++){
        printf("%.2d", i);
        for(int j=0; j< dim; j++){
            ATTACK pos = curr_map -> matrix[i * dim + j].atk_cell;
            switch(pos){
                case UNKNOWN:
                    printf(" . ");
                    break;
                case HIT:
                    if(adv_map -> matrix[i * dim + j].ship->sunk)
                        printf(" S ");
                    else
                        printf(" X ");
                    break;
                case MISS:
                    printf(" M ");
                    break;
            }
        }
        printf("\n");
    }
}


//FOR DEBUG ONLY
void print_map(MAP* m){
    printf("  ");
    for (int i = 0; i < m -> dim; i++)
        printf("%.2d ", i);
    printf("\n");

    for(int i=0; i< m -> dim; i++){
        printf("%.2d", i);
        for(int j=0; j< m -> dim; j++){
            STATE s = m -> matrix[i * m->dim + j].state;
            switch(s){
                case EMPTY:
                    printf(" . ");
                    break;
                case FILLED:
                    printf(" O ");
                    break;
            }
        }
        printf("\n");
    }
}


// returns the index (unidimensional) when rotation r is applied to the point (i,j)
int rotate_point(int i, int j, int r, int dim){
    switch(r % 4){
        case 0: return i * dim + j;
        case 1: return (dim*dim - dim) + i - (j * dim);
        case 2: return (dim*dim - 1) - (i * dim) - j;
        case 3: return (dim - 1) - i + (j * dim);
    }
    return 0;
}

// checks if a move from (old_x, old_y) -> (new_x, new_y) is valid (between the boundaries)
bool valid_position(char *shape, int curr_rot, int old_x, int old_y, int new_x, int new_y, char *map_repr, MAP *map){
    int dim = map -> dim;
    int old_pos;
    for (int i = 0; i < BMAP_SIZE; i++)
        for (int j = 0; j < BMAP_SIZE; j++)
        {
            old_pos = (old_y + i)*dim + (old_x + j);
            if((map->matrix[old_pos].state != FILLED) && old_pos >= 0 && old_pos < dim*dim){
                map_repr[old_pos] = '.'; // erase the 'X's on the the old ship position
            }
            int pi = rotate_point(i, j, curr_rot, BMAP_SIZE); // get the unidimensional index of this point when curr_rot is applied
            if (shape[pi] != '.'){
                if ((new_y +i < 0 || new_y + i >= dim) || (new_x + j < 0 || new_x + j >= dim)){
                    return false; // the new move make the piece go beyond the boundaries of the field.
                }
            }
        }
    return true;
}


void draw_ship(char *curr_bmap, MAP *map, char *map_repr, int old_x, int old_y, int curr_x, int curr_y, int curr_rot){
    int dim = map -> dim;
    for (int i = 0; i < BMAP_SIZE; i++)
        for (int j = 0; j < BMAP_SIZE; j++){
            if (curr_bmap[rotate_point(i, j, curr_rot, BMAP_SIZE)] != '.'){
                // draw the ship on this position
                map_repr[(curr_y + i)*dim + (curr_x + j)] = 'X';
                if(map->matrix[(old_y + i)*dim + (old_x + j)].state == FILLED)
                    // if there was previously a ship on the old position, redraw it (erase the 'X')
                    map_repr[(old_y + i)*dim + (old_x + j)] = 'O';
            }
        }
}

//prints the map representation to the screen
void draw_field(char *map_repr, int dim){
    printf("  ");
        for (int i = 0; i < dim; i++)
            printf("%.2d ", i);

        printf("\n");
        for (int i = 0; i < dim; i++){
            printf("%.2d", i);
            for (int j = 0; j < dim; j++){
                printf(" %c ",map_repr[i*dim + j]);
            }
            printf("\n");
        }
}

char *gen_map_repr(int dim){
    // just a representation of the map for UI purposes
    char *map_repr = (char*)malloc(sizeof(char)*dim*dim+1);
    if (map_repr == NULL)
        map_error("Failed to allocate memory for MAP_REPR");

    // empty map
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            map_repr[i*dim + j] = '.';
        }
    }
    map_repr[dim*dim] = '\0';
    return map_repr;
}

char get_keypress(int dim, char* map_repr){
    char key_press;
    system("clear");
    draw_field(map_repr, dim);
    printf("Place your ships!\n");
    printf("To move the ship around press on the following keys + [ENTER]:\n");
    printf("w -> up | s -> down | a -> left | d -> right | r -> rotate\n");
    printf("To place the ship press [SPACE] + [ENTER]\n\n>> ");
    scanf("%c", &key_press);
    getchar();      // clear input buffer
    return key_press;
}

char get_rand_keypress(int rand_ind){
    if (rand_ind >= 0 && rand_ind < 20) return 'w';
    else if (rand_ind >= 20 && rand_ind < 40) return 'a';
    else if (rand_ind >= 40 && rand_ind < 60) return 'd';
    else if (rand_ind >= 60 && rand_ind < 80) return 's';
    else return 'r';
}

int update_position(char key_press, char **curr_bmap, int *curr_rot, int *curr_x, int *curr_y,
                     int old_x, int old_y, char *map_repr, MAP *map, int *shape_ind, int *game_shapes, MODE mode){
    int shape;
    switch(tolower(key_press)){
        case 'w':
            (*curr_y) -= (valid_position(*curr_bmap, *curr_rot, *curr_x, *curr_y, *curr_x, *curr_y - 1, map_repr, map)) ? 1 : 0;
            break;
        case 's':
            (*curr_y) += (valid_position(*curr_bmap, *curr_rot, *curr_x, *curr_y, *curr_x, *curr_y + 1, map_repr, map)) ? 1 : 0;
            break;
        case 'd':
            (*curr_x) += (valid_position(*curr_bmap, *curr_rot, *curr_x, *curr_y, *curr_x + 1, *curr_y, map_repr, map)) ? 1 : 0;
            break;
        case 'a':
            (*curr_x) -= (valid_position(*curr_bmap, *curr_rot, *curr_x, *curr_y, *curr_x - 1, *curr_y, map_repr, map)) ? 1 : 0;
            break;
        case 'r':
            (*curr_rot) += (valid_position(*curr_bmap, *curr_rot + 1, *curr_x, *curr_y, *curr_x, *curr_y, map_repr, map)) ? 1 : 0;
            break;
        case 32: // try to place the ship on this position
            shape = game_shapes[*shape_ind];
            if(!place_ship(shape, *curr_bmap, map, map_repr, *curr_x, *curr_y, *curr_rot)){
                if (mode == MANUAL){
                    printf("You can't place the ship here!\n");
                    delay(1);
                }
                return -1;
            }
            (*shape_ind)++; // next ship
            (*curr_bmap) = shapes[game_shapes[*shape_ind]].bitmap;
            // back to starting position (all the ships start here)
            (*curr_rot) = 0;
            (*curr_x) = map -> dim / 2;
            (*curr_y) = 0;
            fflush(stdin);
            draw_ship(*curr_bmap, map, map_repr, old_x, old_y, *curr_x, *curr_y, *curr_rot);
            return -1;
        default:
            if (mode == MANUAL){
                printf("Invalid key!\n");
                delay(1);
            }
    }
    return 0;
}

/*
ship placement loop
Updates the map matrix and returns that map
*/
MAP *fill_map(MAP *map, int n_ships, int *game_shapes, MODE mode){
    int dim = map -> dim;
    char key_press;
    int curr_rot = 0; // angle of the current rotation (0 -> 0 | 1 -> 90 | 2 -> 180 | 3 -> 270)
    int curr_x = dim / 2; // current x-axis coordinate of the ship
    int curr_y = 0; // current y-axis coordinate of the ship
    int old_x = curr_x;
    int old_y = curr_y;
    int n_rand_moves; // number of random moves to execute

    if (mode == RANDOM){ // populate random_moves with integers from 0 to dim*dim (each reprenting a move key)
        n_rand_moves = rand() % dim*dim;
        if(n_rand_moves == 0) n_rand_moves++; // always move atleast one position
    }

    int shape_ind = 0; // first shape
    char *curr_bmap = shapes[game_shapes[shape_ind]].bitmap; // the shape of the current ship to be placed

    char *map_repr = gen_map_repr(dim);

    // the first ship starts here (before moving)
    draw_ship(curr_bmap, map, map_repr, old_x, old_y, curr_x, curr_y, curr_rot);

    int move_ind = 0;

    while (shape_ind < n_ships){
        if (mode == MANUAL){
            key_press = get_keypress(dim, map_repr);
        }
        else if (mode == RANDOM){
            if (move_ind == n_rand_moves){ // executed all moves. place the ship.
                key_press = 32;
                // value resets
                move_ind = 0;
                n_rand_moves = rand() % dim*dim;
                if(n_rand_moves == 0) n_rand_moves++; // always move atleast one position
            }
            else{ // get the key represented by the number
                int rand_ind = rand() % 100;
                key_press = get_rand_keypress(rand_ind);
                move_ind++;
            }
        }

        // update the new position according to the key pressed

        int aux = update_position(key_press, &curr_bmap, &curr_rot, &curr_x, &curr_y,
                                  old_x, old_y, map_repr, map, &shape_ind, game_shapes, mode);
        if (aux == -1) continue;

        fflush(stdin);
        draw_ship(curr_bmap, map, map_repr, old_x, old_y, curr_x, curr_y, curr_rot);

        old_x = curr_x;
        old_y = curr_y;
    }
    free(map_repr);
    return map;
}

/*
checks the matrix for collisions and place the ship if there's none
Returns the result boolean result of said check
*/
bool place_ship(int shape_ind, char *shape, MAP *map, char *map_repr, int curr_x, int curr_y, int curr_rot){
    int dim = map -> dim;
    COORD bmap_begin;
    bmap_begin.i = curr_y;
    bmap_begin.j = curr_x;
    SHIP *s = create_ship(shape, shape_ind, curr_rot, bmap_begin);

    for (int i = 0; i < BMAP_SIZE; i++){
        for (int j = 0; j < BMAP_SIZE; j++){
            if ((map->matrix[(curr_y + i)*dim + (curr_x + j)].state == FILLED) && (shape[rotate_point(i, j, curr_rot, BMAP_SIZE)] != '.')){
                // collision!
                free_ship(s);
                return false;
            }
        }
    }

    //place the ship on the map's matrix and update map_repr
    for (int i = 0; i < BMAP_SIZE; i++){
        for (int j = 0; j < BMAP_SIZE; j++){
            if (shape[rotate_point(i, j, curr_rot, BMAP_SIZE)] != '.'){
                map->matrix[(curr_y + i)*dim + (curr_x + j)].state = FILLED;
                map->matrix[(curr_y + i)*dim + (curr_x + j)].ship = s;
                map_repr[(curr_y + i)*dim + (curr_x + j)] = 'O';
            }
        }
    }

    return true;
}

// set all the map cells pointing to this ship as EMPTY
void remove_ship(MAP *m, int shape, int rot, int map_i, int map_j){
    int dim = m -> dim;
    for(int i = 0; i < BMAP_SIZE; i++){
        for(int j = 0; j < BMAP_SIZE; j++){
            // only set to EMPTY if this bitmap pos is an 'X' given the ship rotation
            if(shapes[shape].bitmap[rotate_point(i, j, rot, BMAP_SIZE)] == 'X')
                m -> matrix[(map_i + i)*dim + (map_j + j)].state = EMPTY;
        }
    }

}

// Destroy the structure
void free_map(MAP *m){
	int dim = m -> dim;
    if(m != NULL){
        for(int i = 0; i < dim; i++){
            for(int j = 0; j < dim; j++){
                if (m -> matrix[i*dim + j].state == FILLED){
                    int shape = m -> matrix[i*dim + j].ship -> shape;
                    int rot = m -> matrix[i*dim + j].ship -> rot;
                    COORD bmap_begin = m -> matrix[i*dim +j].ship -> bmap_begin;
                    remove_ship(m, shape, rot, bmap_begin.i, bmap_begin.j);
                    free_ship(m -> matrix[i*dim + j].ship);
                }
            }
        }
        free(m -> matrix);
        free(m);
    }else{
        map_error("Cannot free MAP (NULL)");
    }
}

// Call this when there is a memory related error
void map_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}
