#include "map.h"

//returns a new instance of MAP
MAP *create_map(int dim){
    MAP *m = (MAP*)malloc(sizeof(MAP));
    if(m == NULL){map_error("No memory");}
    m -> dim = dim;
    TILE *matrix;
    //allocate memory for a 2D matrix
    matrix = (TILE*)malloc(sizeof(TILE)*dim*dim);
    //initialize all the positions as EMPTY
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            matrix[i*dim + j].state = EMPTY;
        }
    }
    m -> matrix = matrix;
    return m;
}

void print_map(MAP* m){
    printf("  ");
    for (int i = 0; i < m -> dim; i++)
        printf("%.2d ", i);
    printf("\n");
    for(int i=0; i< m -> dim; i++){
        printf("%.2d", i);
        for(int j=0; j< m -> dim; j++){
            STATE pos = m -> matrix[i * m->dim + j].state;
            switch(pos){
                case EMPTY:
                    printf(" . ");
                    break;
                case FILLED:
                    printf(" O ");
                    break;
                case HIT:
                    printf(" X ");
                    break;
            }
        }
        printf("\n");
    }
}

// Destroy the structure
void free_map(MAP *m){
    if(m != NULL){
        free(m -> matrix);
        free(m);
    }else{
        map_error("The map was badly generated.");
    }
}

// Call this when there is a memory related error
void map_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}
