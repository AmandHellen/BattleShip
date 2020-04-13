#include "player.h"

// returns a new instance of PLAYER
PLAYER *create_player(char *name, int dim, int n_ships, int *game_shapes, MODE mode){
    PLAYER *p = (PLAYER*)malloc(sizeof(PLAYER));
    if(p == NULL){player_error("No memory");}
    memcpy(p -> name,   name, NAME_LEN);
    MAP *empty_map = create_map(dim);
    p -> map = fill_map(empty_map, n_ships, game_shapes, mode);
    p -> n_ships = n_ships;
    return p;
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

bool valid_position(char *shape, int curr_rot, int old_x, int old_y, int new_x, int new_y, char *map_repr, MAP *map)
{
    int dim = map -> dim;
    int old_pos;
    for (int i = 0; i < BMAP_SIZE; i++)
        for (int j = 0; j < BMAP_SIZE; j++)
        {
            old_pos = (old_y + i)*dim + (old_x + j);
            if((map->matrix[old_pos].state != FILLED) && old_pos >= 0 && old_pos < dim*dim){
                map_repr[old_pos] = '.';
            }
                
            // Get index into piece
            int pi = rotate_point(i, j, curr_rot);

            if (shape[pi] != '.'){
                if ((new_y +i < 0 || new_y + i >= dim) || (new_x + j < 0 || new_x + j >= dim)){
                    return false;
                }
            }
        }
    return true;
}

void draw_ship(char *curr_bmap, MAP *map, char *map_repr, int old_x, int old_y, int curr_x, int curr_y, int curr_rot){
    int dim = map -> dim;
    for (int i = 0; i < BMAP_SIZE; i++)
        for (int j = 0; j < BMAP_SIZE; j++)
            if (curr_bmap[rotate_point(i, j, curr_rot)] != '.'){
                map_repr[(curr_y + i)*dim + (curr_x + j)] = 'X';
                if(map->matrix[(old_y + i)*dim + (old_x + j)].state == FILLED)
                    map_repr[(old_y + i)*dim + (old_x + j)] = 'O';
                }
}

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

/*
keep generating ships (or asking for them) and placing them on the 2D matrix
return a new instance of MAP with that matrix
*/
MAP *fill_map(MAP *map, int n_ships, int *game_shapes, MODE mode){
    // Game Logic
    int dim = map -> dim;
    char key_press;
    int old_x, old_y;
    int curr_rot = 0;
    int curr_x = dim / 2;
    int curr_y = 0;

    int shape_ind = 0;
    char *curr_bmap = shapes[game_shapes[shape_ind]].bitmap;

    char *map_repr = (char*)malloc(sizeof(char)*dim*dim+1);

    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            map_repr[i*dim + j] = '.';
        }
    }
    map_repr[dim*dim] = '\0';

    draw_ship(curr_bmap, map, map_repr, old_x, old_y, curr_x, curr_y, curr_rot);

    old_x = curr_x;
    old_y = curr_y;

    while (shape_ind < n_ships) // Main Loop
    {
        draw_field(map_repr, dim);
        scanf("%c", &key_press);
        getchar();      // clear input buffer 

        switch(tolower(key_press)){
            case 'w':
                curr_y -= (valid_position(curr_bmap, curr_rot, curr_x, curr_y, curr_x, curr_y - 1, map_repr, map)) ? 1 : 0;
                break;
            case 's':
                curr_y += (valid_position(curr_bmap, curr_rot, curr_x, curr_y, curr_x, curr_y + 1, map_repr, map)) ? 1 : 0;
                break;
            case 'd':
                curr_x += (valid_position(curr_bmap, curr_rot, curr_x, curr_y, curr_x + 1, curr_y, map_repr, map)) ? 1 : 0;
                break;
            case 'a':
                curr_x -= (valid_position(curr_bmap, curr_rot, curr_x, curr_y, curr_x - 1, curr_y, map_repr, map)) ? 1 : 0;
                break;
            case 'r':
                curr_rot += (valid_position(curr_bmap, curr_rot + 1, curr_x, curr_y, curr_x, curr_y, map_repr, map)) ? 1 : 0;
                break;
            case 32:
                if(!place_ship(curr_bmap, map, map_repr, curr_x, curr_y, curr_rot)){
                    printf("You can't put the ship here!\n");
                }                
                shape_ind++;
                curr_bmap = shapes[game_shapes[shape_ind]].bitmap;
                curr_rot = 0;
                curr_x = dim / 2;
                curr_y = 0;
                fflush(stdin);
                draw_ship(curr_bmap, map, map_repr, old_x, old_y, curr_x, curr_y, curr_rot);
                continue;
            default:
                printf("Invalid key!\n");
        }
        fflush(stdin);
        draw_ship(curr_bmap, map, map_repr, old_x, old_y, curr_x, curr_y, curr_rot);

        old_x = curr_x;
        old_y = curr_y;
    }
    free(map_repr);
    return map;
}

// checks the matrix for collisions and place the ship if there's none (POR ACABAR)
bool place_ship(char *shape, MAP *map, char *map_repr, int curr_x, int curr_y, int curr_rot){
    int dim = map -> dim;
    SHIP *s = create_ship(shape);

    for (int i = 0; i < BMAP_SIZE; i++){
        for (int j = 0; j < BMAP_SIZE; j++){
            if ((map->matrix[(curr_y + i)*dim + (curr_x + j)].state == FILLED) && (shape[rotate_point(i, j, curr_rot)] != '.')){
                free_ship(s);
                return false;
            }
        }
    }

    for (int i = 0; i < BMAP_SIZE; i++){
        for (int j = 0; j < BMAP_SIZE; j++){
            if (shape[rotate_point(i, j, curr_rot)] != '.'){
                map->matrix[(curr_y + i)*dim + (curr_x + j)].state = FILLED;
                map->matrix[(curr_y + i)*dim + (curr_x + j)].ship = s;
                map_repr[(curr_y + i)*dim + (curr_x + j)] = 'O';
            }
        }
    }

    return true;
}

void print_dashboard(PLAYER *p){
    print_map(p -> map);
    printf("Remaining Ships: %d\n",p -> n_ships);
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