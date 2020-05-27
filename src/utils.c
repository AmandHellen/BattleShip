#include "utils.h"

void delay(int secs){
    int ms = 1000 * 1000 * secs;
    clock_t start_time = clock();
    while (clock() < start_time + ms)
        ;
}
