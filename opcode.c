# include "chip8.h"
# define OP_00E0 1
# define OP_1NNN 2
# define OP_6XNN 3
# define OP_8XY0 4


void instruction(CHIP8 chip8, int instruction)
{
    switch (instruction)
    {
        case OP_00E0:
            memset(chip8.monitor, 0, sizeof(chip8.monitor));
            break;

        case OP_1NNN:
            //This instruction should simply set PC to NNN, 
            // causing the program to jump to that memory location.
            // Do not increment the PC afterwards, it jumps directly there.
            unsigned short addr = chip8.opcode & 0x0FFFu;
            chip8.pc = addr;
            break;
        
        case OP_6XNN:
            // Simply set the register Vx to the value NN.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short value = chip8.opcode & 0x00FFu;
            chip8.registers[Vx] = value;
            break;

        case OP_8XY0:
            // Vx is set to the value of Vy.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vy];
            break;

        default:
            break;
    }
}

// void op_00E0(CHIP8 chip8)
// {
//     memset(chip8.monitor, 0, sizeof(chip8.monitor));
// }

// void op_1NNN(CHIP8 chip8)
// {

// }

// void op_6XNN(CHIP8 chip8)
// {
//  // Simply set the register VX to the value NN.

// }

// void op_7XNN(CHIP8 chip8)
// {

// }

// void op_ANNN(CHIP8 chip8)
// {

// }

// void op_DXYN(CHIP8 chip8)
// {

// }

// void RET(CHIP8 chip8)
// {
//     --chip8.sp;
//     chip8.pc = chip8.stack[chip8.sp];
// }

// void JP_addr(CHIP8 chip8)
// {
//     unsigned short addr = chip8.opcode & 0x0FFFu;
//     chip8.pc = addr;
// }

// void CALL_addr(CHIP8 chip8)
// {
//     unsigned short addr = chip8.opcode & 0x0FFFu;
//     chip8.stack[chip8.sp] = chip8.pc;
//     ++chip8.sp;
//     chip8.pc = addr;
// }


