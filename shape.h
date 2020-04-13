#ifndef SHAPE_H
#define SHAPE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5
#define NUM_SHAPES 2

typedef struct shape{
    char shape[MAX_SIZE][MAX_SIZE];
}SHAPE;

void print_shape(SHAPE);

#endif