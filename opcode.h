# ifndef INC_OPCODE_H
# define INC_OPCODE_H

# include "chip8.h"

void det_opcode(CHIP8 chip8); /** Determine which opcode needs to be executed.*/

void instruction(CHIP8 chip8, int instruction); /** The function that executes all CPU instructions.*/

# endif