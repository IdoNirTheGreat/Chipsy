# include <stdlib.h>
# include <string.h>
# include "opcode.h"
# include "randGen.h"
# define OP_00E0 1
# define OP_1NNN 2
# define OP_6XNN 3
# define OP_8XY0 4
# define OP_8XY1 5
# define OP_8XY2 6
# define OP_8XY3 7
# define OP_8XY4 8
# define OP_7XNN 9
# define OP_ANNN 10
# define OP_DXYN 11
# define OP_8XY5 12
# define OP_8XY7 13
# define OP_8XY6 14
# define OP_8XYE 15
# define OP_BNNN 16
# define OP_CXNN 17

void instruction(CHIP8 chip8, int instruction)
{
    switch (instruction)
    {
        case OP_00E0:
        {
            memset(chip8.monitor, 0, sizeof(chip8.monitor));
            break;
        }

        case OP_1NNN:
        {
            //This instruction should simply set PC to NNN, 
            // causing the program to jump to that memory location.
            // Do not increment the PC afterwards, it jumps directly there.
            unsigned short addr = chip8.opcode & 0x0FFFu;
            chip8.pc = addr;
            break;
        }
        
        case OP_6XNN:
        {
            // Simply set the register Vx to the value NN.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8.opcode & 0x00FFu;
            chip8.registers[Vx] = NN;
            break;
        }

        case OP_8XY0:
        {
            // Vx is set to the value of Vy.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vy];
            break;
        }

        case OP_8XY1:
        {
            // Vx is set to Vx OR Vy.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vx] | chip8.registers[Vy];
            break;
        }

        case OP_8XY2:
        {
            // Vx is set to Vx AND Vy.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vx] & chip8.registers[Vy];
            break;
        }

        case OP_8XY3:
        {
            // Vx is set to Vx XOR Vy.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vx] ^ chip8.registers[Vy];
            break;
        }

        case OP_8XY4:
        {
            // VX is set to the value of VX plus the value of VY.
            // VY is not affected.
            // Unlike 7XNN, this addition will affect the carry flag.
            // If the result is larger than 255 (and thus overflows 
            // the 8-bit register VX), the flag register VF is set to 1.
            // If it doesn’t overflow, VF is set to 0.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vx] + chip8.registers[Vy];
            if (chip8.registers[Vx] > 0x00FF) chip8.registers[0x000F] = 0x0001;
            else chip8.registers[0x000F] = 0x0000;
            break;
        }

        case OP_8XY5:
        {
            // sets VX to the result of VX - VY.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vx] - chip8.registers[Vy];
            break;
        }

        case OP_8XY7:
        {
            // 8XY7 sets VX to the result of VY - VX.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vy] - chip8.registers[Vx];
            break;
        }

        case OP_8XY6:
        {
            // Set VX to the value of VY, shift the value of VX
            // one bit to the right, set VF to 1 if the bit that
            // was shifted out was 1, or 0 if it was 0.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vy];
            unsigned short sh_bit = chip8.registers[Vx] & 0x000F;
            chip8.registers[Vx] >> 1u;
            if (sh_bit) chip8.registers[0x000F] = 0x0001;
            else chip8.registers[0x000F] = 0x0000;
            break;
        }

        case OP_8XYE:
        {
            // Set VX to the value of VY, shift the value of VX
            // one bit to the left, set VF to 1 if the bit that
            // was shifted out was 1, or 0 if it was 0.
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            chip8.registers[Vx] = chip8.registers[Vy];
            unsigned short sh_bit = chip8.registers[Vx] & 0xF000;
            chip8.registers[Vx] << 1u;
            if (sh_bit) chip8.registers[0x000F] = 0x0001;
            else chip8.registers[0x000F] = 0x0000;
            break;
        }

        case OP_7XNN:
        {
            // Add the value NN to Vx (no flag).
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short NN = (chip8.opcode & 0x00FFu);
            chip8.registers[Vx] = chip8.registers[Vx] + NN;
            break;
        }

        case OP_ANNN:
        {
            // Sets the index register to the value NNN.
            unsigned short NNN = (chip8.opcode & 0x0FFFu);
            chip8.index = NNN;
            break;
        }

        // case OP_BNNN: ;
            
        //     break;

        case OP_CXNN:
        {
            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8.opcode & 0x00FFu;
            unsigned char random = rand_byte() & NN;
            chip8.registers[Vx] = random;
            break;
        }

        case OP_DXYN:
        {
            // This is the most involved instruction. It will draw
            // an N pixels tall sprite from the memory location that
            // the I index register is holding to the screen, at the
            // horizontal X coordinate in VX and the Y coordinate in VY.
            // All the pixels that are “on” in the sprite will flip the
            // pixels on the screen that it is drawn to. If any pixels 
            // on the screen were turned “off” by this, the VF flag 
            // register is set to 1. Otherwise, it’s set to 0.

            unsigned short Vx = (chip8.opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8.opcode & 0x00F0u) >> 4u;
            unsigned char X = chip8.registers[Vx] & 0x003F;
            unsigned char Y = chip8.registers[Vx] & 0x001F;
            chip8.registers[0x000F] = 0x0000;
            unsigned char N = chip8.opcode & 0x000F;
            
            for (unsigned int i = 0; i < N; ++i)
            {
                unsigned char sprite_byte = chip8.memory[chip8.index + i];

                for (unsigned int j = 0; j < 8; ++j)
                {
                    unsigned char sprite_pixel = sprite_byte & (0x80 >> j);
                    unsigned long* actual_pixel = &chip8.monitor[(Y + i) * COLS + (X + j)];

                    if (sprite_pixel)
                    {
                        if (*actual_pixel == 0xFFFFFFFF)
                            chip8.registers[0x000F] = 1;
                        
                        *actual_pixel ^= 0xFFFFFFFF;
                    }
                }
            }


            break;
        }

        default:
            break;
    }
}
