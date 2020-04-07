#include "player.h"

// returns a new instance of PLAYER
PLAYER *create_player(int dim, int n_ships, int *game_shapes, MODE mode, bool playing){
    PLAYER *p = (PLAYER*)malloc(sizeof(PLAYER));
    if(p == NULL){player_error("No memory");}
    MAP *empty_map = create_map(dim);
    p -> map = fill_map(empty_map, n_ships, mode, dim);
    p -> n_ships = n_ships;
    p -> playing = playing;
    return p;
}   

bool valid_position(char *shape, int curr_rot, int old_x, int old_y, int new_x, int new_y, char *map_repr, MAP *map, int dim)
{
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

/*
keep generating ships (or asking for them) and placing them on the 2D matrix
return a new instance of MAP with that matrix
*/
MAP *fill_map(MAP *map, int n_ships, MODE mode, int dim){
    // Game Logic
    char key_press;
    int old_x, old_y;
    int curr_rot = 0;
    int curr_x = dim / 2;
    int curr_y = 0;
    char nCurrentPiece[BMAP_SIZE*BMAP_SIZE+1] = {"..X....X....X....X....X..\0"};
    char map_repr[dim*dim+1]; // Create play field buffer

    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            map_repr[i*dim + j] = '.';
        }
    }
    map_repr[dim*dim] = '\0';

    // Place ship on the map
    for (int i = 0; i < BMAP_SIZE; i++){
        for (int j = 0; j < BMAP_SIZE; j++){
            if (nCurrentPiece[i * BMAP_SIZE + j] != '.')
                map_repr[(curr_y + i)*dim + (curr_x + j)] = 'X';
        }
    }

    old_x = curr_x;
    old_y = curr_y;

    while (1) // Main Loop
    {
        // Draw Field
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

        // Draw MAP
        printf("  ");
        for (int i = 0; i < dim; i++)
            printf("%.2d ", i);

        printf("\n");
        for (int i = 0; i < dim; i++){
            printf("%.2d", i);
            for (int j = 0; j < dim; j++){
                printf(" %d ", map->matrix[i*dim + j].state);
            }
            printf("\n");
        }

        // Input ========================
        scanf("%c", &key_press);
        getchar();

        switch(tolower(key_press)){
            case 'w':
                curr_y -= (valid_position(nCurrentPiece, curr_rot, curr_x, curr_y, curr_x, curr_y - 1, map_repr, map, dim)) ? 1 : 0;
                break;
            case 's':
                curr_y += (valid_position(nCurrentPiece, curr_rot, curr_x, curr_y, curr_x, curr_y + 1, map_repr, map, dim)) ? 1 : 0;
                break;
            case 'd':
                curr_x += (valid_position(nCurrentPiece, curr_rot, curr_x, curr_y, curr_x + 1, curr_y, map_repr, map, dim)) ? 1 : 0;
                break;
            case 'a':
                curr_x -= (valid_position(nCurrentPiece, curr_rot, curr_x, curr_y, curr_x - 1, curr_y, map_repr, map, dim)) ? 1 : 0;
                break;
           case 'r':
                curr_rot += (valid_position(nCurrentPiece, curr_rot + 1, curr_x, curr_y, curr_x, curr_y, map_repr, map, dim)) ? 1 : 0;
                break;
            case 32:
                if(!place_ship(nCurrentPiece, map, map_repr, curr_x, curr_y, curr_rot, dim)){
                    printf("You can't put the ship here!\n");
                }
                fflush(stdin);
                continue;
            default:
                printf("Invalid key!\n");
        }

        fflush(stdin);

        // Display ======================

        // Place ship on the map
        for (int i = 0; i < BMAP_SIZE; i++)
            for (int j = 0; j < BMAP_SIZE; j++)
                if (nCurrentPiece[rotate_point(i, j, curr_rot)] != '.'){
                    map_repr[(curr_y + i)*dim + (curr_x + j)] = 'X';
                    if(map->matrix[(old_y + i)*dim + (old_x + j)].state == FILLED)
                        map_repr[(old_y + i)*dim + (old_x + j)] = 'O';
                }


        old_x = curr_x;
        old_y = curr_y;
    }
    return map;
}

// checks the matrix for collisions and place the ship if there's none (POR ACABAR)
bool place_ship(char *shape, MAP *map, char *map_repr, int curr_x, int curr_y, int curr_rot, int dim){
    for (int i = 0; i < BMAP_SIZE; i++){
        for (int j = 0; j < BMAP_SIZE; j++){
            if ((map->matrix[(curr_y + i)*dim + (curr_x + j)].state == FILLED) && (shape[rotate_point(i, j, curr_rot)] != '.')){
                return false;
            }
        }
    }

    for (int i = 0; i < BMAP_SIZE; i++){
        for (int j = 0; j < BMAP_SIZE; j++){
            if (shape[rotate_point(i, j, curr_rot)] != '.'){
                map->matrix[(curr_y + i)*dim + (curr_x + j)].state = FILLED;
                map_repr[(curr_y + i)*dim + (curr_x + j)] = 'O';
            }
        }
    }

    return true;
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
