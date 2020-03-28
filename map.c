#include "map.h"

//returns a new instance of MAP
MAP *create_map(int dim){
    MAP *m = (MAP*)malloc(sizeof(MAP));
    if(m == NULL){map_error("No memory");}
    TILE **matrix;
    //allocate memory for a 2D matrix
    matrix = (TILE**)malloc(sizeof(TILE*)*dim*dim);
    for(int i=0; i<dim; i++){
        matrix[i] = (TILE*)malloc(sizeof(TILE)*dim);
    }
    //initialize all the positions as EMPTY
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            matrix[i][j].state = EMPTY;
        }
    }
    m -> matrix = matrix;
    return m;
}

// Destroy the structure
void free_map(MAP *m){
    if(m != NULL){
        int i = 0;
        while(m->matrix[i] != NULL){
            free(m->matrix[i]);
            i++;
        }
        free(m -> matrix);
        free(m);
    }else{
        map_error("The map was badly generated.");
    }
}

// Call this when there is a memory related error
static void map_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}
