#include "map.h"

int main(){
    int dim = 10;
    TILE **matrix = create_empty_map(dim);
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
