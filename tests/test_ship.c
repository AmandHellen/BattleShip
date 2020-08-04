#include "../src/ship.h"

void print_ship_info(SHIP *s){
    printf("Hits: %d\nSize: %d\n",s -> hits, s -> size);
}

int main(){
    char bitmap[BMAP_SIZE*BMAP_SIZE + 1] = {"XXXXX..X....X....X....X..\0"};
    SHIP *s = create_ship(bitmap);
    char *serialized = serialize_ship(s);
    SHIP *s2 = deserialize_ship(serialized);
    print_ship_info(s);
    print_ship_info(s2);
    free_ship(s);
    free_ship(s2);
    return 0;
}
