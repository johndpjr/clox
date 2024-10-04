#include "rle.h"
#include "memory.h"

#include <stdio.h>

void init_rle_array(LineRLEArray *array) {
    array->count = 0;
    array->capacity = 0;
    array->encodings = NULL;
}

void write_rle_array(LineRLEArray *array, LineRLE line) {
    if (array->count + 1 > array->capacity) {
        int old_capacity = array->capacity;
        array->capacity = GROW_CAPACITY(old_capacity);
        array->encodings = GROW_ARRAY(LineRLE, array->encodings, old_capacity, array->capacity);
    }

    array->encodings[array->count] = line;
    array->count++;
}

void free_rle_array(LineRLEArray *array) {
    FREE_ARRAY(LineRLE, array->encodings, array->capacity);
    init_rle_array(array);
}

void update_rle_array(LineRLEArray *array, int lineno) {
    int rle_count = array->count;
    if (rle_count == 0 || array->encodings[rle_count - 1].lineno != lineno) {
        // First RLE or RLE chain broken: add a new RLE
        LineRLE new_rle = { .lineno = lineno, .n = 1 };
        write_rle_array(array, new_rle);
    } else {
        // Increment last RLE
        array->encodings[rle_count - 1].n++;
    }
}
