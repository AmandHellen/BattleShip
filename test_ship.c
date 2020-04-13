#include "ship.h"

void print_ship_info(SHIP *s){
    printf("Hits: %d\nSize: %d\n",s -> hits, s -> size);
    if(s -> sunk == false){printf("Is sunk?: FALSE\n");}
    else{printf("Is sunk?: TRUE\n");}
}

int main(){
    char bitmap[BMAP_SIZE + 1] = {"XXXXX..X....X....X....X..\0"};
    SHIP *s = create_ship(bitmap);
    print_ship_info(s);
    free_ship(s);
    return 0;
}
