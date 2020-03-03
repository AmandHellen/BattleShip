#include "ship.h"

void print_ship_info(SHIP *s){
    printf("Beginning: (%d,%d)\nEnd: (%d,%d)\n",s -> xi, s -> yi, s -> xf, s -> yf);
    printf("Hits: %d\nSize: %d\n",s -> hits, s -> size);
    if(s -> sunk == FALSE){printf("Is sunk?: FALSE\n");}
    else{printf("Is sunk?: TRUE\n");}
}

int main(){
    SHIP *s = create_ship(3,3,3,10);
    print_ship_info(s);
    free_ship(s);
    //print_ship_info(s);
    return 0;
}
