#include "map.h"

int main(){
    int dim = 20;
    MAP *m = create_map(dim);
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            printf("%d ",m -> matrix[i*dim + j].state);
        }
        printf("\n");
    }
    return 0;
}
