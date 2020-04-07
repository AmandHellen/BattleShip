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
    for(int i=0; i< m -> dim; i++){
        for(int j=0; j< m -> dim; j++){
            printf("%d ",m -> matrix[i* m -> dim + j].state);
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
