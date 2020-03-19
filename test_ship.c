#include "ship.h"

void print_ship_info(SHIP *s){
    printf("Beginning: (%d,%d)\nEnd: (%d,%d)\n",s -> begin.x, s -> begin.y, s -> end.x, s -> end.y);
    printf("Hits: %d\nSize: %d\nDirection: %d\n",s -> hits, s -> size, s -> dir);
    if(s -> sunk == FALSE){printf("Is sunk?: FALSE\n");}
    else{printf("Is sunk?: TRUE\n");}
}

int main(){
    COORD begin, end;
    begin.x = 5;
    begin.y = 5;
    end.x = 5;
    end.y = 3;
    SHIP *s = create_ship(begin, end);
    print_ship_info(s);
    free_ship(s);
    //print_ship_info(s);
    return 0;
}
