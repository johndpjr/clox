#include "debug.h"
#include "value.h"

#include <stdio.h>

void disassemble_chunk(Chunk *chunk, const char *name) {
    printf("== %s ==\n", name);

    int rle_offset = 0;
    for (int offset = 0, n = 1; offset < chunk->count;) {
        offset = disassemble_instruction(chunk, offset, &rle_offset, &n);
    }
}

int constant_instruction(const char *name, Chunk *chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    print_value(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

int simple_instruction(const char *name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassemble_instruction(Chunk *chunk, int code_offset, int *rle_offset, int *n) {
    printf("%04d ", code_offset);
    LineRLE *encodings = chunk->line_rles.encodings;
    if (*n <= encodings[*rle_offset].n) {
        // Print newline
        printf("%4d ", encodings[*rle_offset].lineno);
        // Move on to next rle
        (*rle_offset)++;
        *n = 1;
    } else {
        printf("   | ");
        (*n)++;
    }

    uint8_t instruction = chunk->code[code_offset];
    switch (instruction) {
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", chunk, code_offset);
        case OP_RETURN:
            return simple_instruction("OP_RETURN", code_offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return code_offset + 1;
    }
}
