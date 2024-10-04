#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

#include "chunk.h"

void disassemble_chunk(Chunk *chunk, const char *name);
static int constant_instruction(const char *name, Chunk *chunk, int offset);
static int simple_instruction(const char *name, int offset);
int disassemble_instruction(Chunk *chunk, int code_offset, int *rle_offset, int *n);

#endif //CLOX_DEBUG_H
