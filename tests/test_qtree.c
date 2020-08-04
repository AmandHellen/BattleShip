#include "../src/map.h"
#include "../src/ship.h"
#include <stdio.h>

void print_map(MAP m){
    COORD c; 
    CELL *cell;
    printf("  ");
    for (int i = 0; i < dim; i++)
        printf("%.2d ", i);
    printf("\n");

    for(int i=0; i< dim; i++){
        printf("%.2d", i);
        for(int j=0; j< dim; j++){
            c.i = i; 
            c.j = j;
           /* if(get_cell(c, &cell, m) == -1) 
                game_error("Cannot get cell");*/
            if((cell = get_cell(c,m)) == NULL)
                continue;
                //map_error("Cannot get cell PRINT_MAP");
            STATE s = cell->state;
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

int main(){
    COORD c2;
    CELL *cell;
    //, c2, c3, c4;
    MAP map;
    dim = 32;

    /*c1.i = 7;
    c1.j = 0;

    
    c3.i = 7;
    c3.j = 2;map
;
    c4.i = 7;
    c4.j = 7;*/

    c2.i = 0;
    c2.j = 0;


    map = create_map(dim);
    SHIP *s = create_ship(shapes[2].bitmap, 2, 0, c2);


    printf("\n\n\n\n\n\n");

    //insert_cell(c2, s, map);
    //insert(c2, NULL, MAP);
    //insert(c3, NULL, MAP);
    //insert(c4, NULL, MAP);

  

    if((cell = get_cell(c2, map)) == NULL)
        exit(EXIT_FAILURE);
   // printf("(%d)\n", cell->atk_cell);

    cell->ship = s;
    cell->state = FILLED;

    print_map(map);

    //free_ship(s);
    free_map(map);

    return 0;
}
