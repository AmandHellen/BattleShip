#include "../src/map.h"

int main(){
    int dim = 20;
    MAP *m = create_map(dim);
    print_map(m);
    free_map(m);
    return 0;
}
