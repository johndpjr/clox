#ifndef CLOX_RLE_H
#define CLOX_RLE_H

#include "common.h"

typedef struct LineRLE {
    int lineno;
    short n;
} LineRLE;

typedef struct LineRLEArray {
    int count;
    int capacity;
    LineRLE *encodings;
} LineRLEArray;

void init_rle_array(LineRLEArray *array);
void write_rle_array(LineRLEArray *array, LineRLE line);
void free_rle_array(LineRLEArray *array);

void update_rle_array(LineRLEArray *array, int lineno);

#endif //CLOX_RLE_H
