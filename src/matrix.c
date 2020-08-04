#include "map.h"

struct map{
    CELL *matrix;
    int dim;
};

//returns a new instance of MAP
MAP create_map(int dim){
    MAP m = (MAP)malloc(sizeof(struct map));
    if(m == NULL){map_error("Failed to allocate memory for MAP");}
    m -> dim = dim;
    CELL *matrix; // matrix to save the map state
    matrix = (CELL*)malloc(sizeof(struct cell)*dim*dim);
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

void print_strategy(MAP curr_map, MAP adv_map){
    CELL *curr_cell, *adv_cell;
    COORD c;

    printf("  ");
    for (int i = 0; i < dim; i++)
        printf("%.2d ", i);
    printf("\n");

    for(int i=0; i < dim; i++){
        printf("%.2d", i);
        for(int j=0; j< dim; j++){
            c.i = i; 
            c.j = j;

           if((curr_cell = get_cell(c,curr_map)) == NULL)
                map_error("Cannot get cell");

            
            ATTACK pos = curr_cell -> atk_cell;

            switch(pos){
                case UNKNOWN:
                    printf(" . ");
                    break;
                case HIT:
                    if((adv_cell = get_cell(c,adv_map)) == NULL)
                        map_error("Cannot get cell");

                    if(adv_cell->ship->sunk)
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

int get_dim(MAP m){
    return m -> dim;
}

CELL *get_cell(COORD c, MAP m){
    int dim = get_dim(m);
    int index = c.i*dim + c.j;

    return &m->matrix[index];
}

int insert_cell(COORD c, SHIP *s, MAP m){
    int dim = get_dim(m);
    m->matrix[c.i*dim + c.j].state = FILLED;
    m->matrix[c.i*dim + c.j].ship = s;
    return 0;
}


// set all the map cells pointing to this ship as EMPTY
void remove_ship(MAP m, int shape, int rot, int map_i, int map_j){
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
void free_map(MAP m){
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
