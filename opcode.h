# ifndef INC_OPCODE_H
# define INC_OPCODE_H

# include "chip8.h"

enum OPCODE
{
    OP_00E0,
    OP_00EE,
    OP_0NNN,
    OP_1NNN,
    OP_2NNN,
    OP_3XNN,
    OP_4XNN,
    OP_5XY0,
    OP_6XNN,
    OP_7XNN,
    OP_8XY0,
    OP_8XY1,
    OP_8XY2,
    OP_8XY3,
    OP_8XY4,
    OP_8XY5,
    OP_8XY6,
    OP_8XY7,
    OP_8XYE,
    OP_9XY0,
    OP_ANNN,
    OP_BNNN,
    OP_CXNN,
    OP_DXYN,
    OP_EX9E,
    OP_EXA1,
    OP_FX07,
    OP_FX0A,
    OP_FX15,
    OP_FX18,
    OP_FX1E,
    OP_FX29,
    OP_FX33,
    OP_FX55,
    OP_FX65,
};

enum ERROR
{
    DET_OPCODE_ERROR,
};

void det_opcode(CHIP8* chip8); /** Determine which opcode needs to be executed.*/

void instruction(CHIP8* chip8, int instruction); /** The function that executes all CPU instructions.*/

# endif