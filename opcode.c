# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "opcode.h"
# include "randGen.h"
# define COLS 64
# define ROWS 32

void det_opcode(CHIP8* chip8)
{
    printf_s("Opcode in determination function: %x\n", chip8->opcode);
    unsigned char frst_bt = (chip8->opcode & 0xF000u) >> 12;
    switch (frst_bt)
    {
        case 0x0:
        {
            switch (chip8->opcode)
            {
                case 0x00e0u:
                {
                    instruction(chip8, OP_00E0);
                    break;
                }

                case 0x00EEu:
                {
                    instruction(chip8, OP_00EE);
                    break;
                }

                default:
                {
                    instruction(chip8, OP_0NNN);
                    break;
                }
            }
            
            break;
        }

        case 0x1:
        {
            instruction(chip8, OP_1NNN);
            break;
        }

        case 0x2:
        {
            instruction(chip8, OP_2NNN);
            break;
        }

        case 0x3:
        {
            instruction(chip8, OP_3XNN);
            break;
        }

        case 0x4:
        {
            instruction(chip8, OP_4XNN);
            break;
        }

        case 0x5:
        {
            instruction(chip8, OP_5XY0);
            break;
        }

        case 0x6:
        {
            instruction(chip8, OP_6XNN);
            break;
        }

        case 0x7:
        {
            instruction(chip8, OP_7XNN);
            break;
        }

        case 0x8:
        {
            unsigned char frth_bt = chip8->opcode & 0x000Fu;
            switch (frth_bt)
            {
                case 0x0:
                {
                    instruction(chip8, OP_8XY0);
                    break;

                }

                case 0x1:
                {
                    instruction(chip8, OP_8XY1);
                    break;
                }

                case 0x2:
                {
                    instruction(chip8, OP_8XY2);
                    break;
                }

                case 0x3:
                {
                    instruction(chip8, OP_8XY3);
                    break;
                }

                case 0x4:
                {
                    instruction(chip8, OP_8XY4);
                    break;
                }

                case 0x5:
                {
                    instruction(chip8, OP_8XY5);
                    break;
                }

                case 0x6:
                {
                    instruction(chip8, OP_8XY6);
                    break;
                }

                case 0x7:
                {
                    instruction(chip8, OP_8XY7);
                    break;
                }

                case 0xE:
                {
                    instruction(chip8, OP_8XYE);
                    break;
                }

                default:
                {
                    printf_s("Opcode determination function has failed!\n");
                    exit(DET_OPCODE_ERROR);
                    break;
                }
            }

            break;
        }

        case 0x9:
        {
            instruction(chip8, OP_9XY0);
            break;
        }

        case 0xA:
        {
            instruction(chip8, OP_ANNN);
            break;
        }

        case 0xB:
        {
            instruction(chip8, OP_BNNN);
            break;
        }

        case 0xC:
        {
            instruction(chip8, OP_CXNN);
            break;
        }

        case 0xD:
        {
            instruction(chip8, OP_DXYN);
            break;
        }

        case 0xE:
        {
            unsigned char thrd_bt = (chip8->opcode & 0x000Fu) >> 4;
            switch (thrd_bt)
            {
                case 0x9:
                {
                    instruction(chip8, OP_EX9E);
                    break;
                }

                case 0xA:
                {
                    instruction(chip8, OP_EXA1);
                    break;
                }

                default:
                {
                    printf_s("There seems to be an error with determining the opcode.\n");
                    exit(DET_OPCODE_ERROR);
                    break;
                }
            }

            break;
        }

        case 0xF:
        {
            unsigned char thrd_bt = (chip8->opcode & 0x00F0u) >> 4;
            switch (thrd_bt)
            {
                case 0x0:
                {
                    unsigned char frth_bt = chip8->opcode & 0x000Fu;
                    switch (frth_bt)
                    {
                        case 0x7:
                        {
                            instruction(chip8, OP_FX07);
                            break;
                        }

                        case 0xA:
                        {
                            instruction(chip8, OP_FX0A);
                            break;
                        }

                        default:
                        {
                            printf_s("There seems to be an error with determining the opcode.\n");
                            exit(DET_OPCODE_ERROR);
                            break;
                        }
                    }

                    break;
                }

                case 0x1:
                {
                    unsigned char frth_bt = chip8->opcode & 0x000Fu;
                    switch (frth_bt)
                    {
                        case 0x5:
                        {
                            instruction(chip8, OP_FX15);
                            break;
                        }

                        case 0x8:
                        {
                            instruction(chip8, OP_FX18);
                            break;
                        }

                        case 0xE:
                        {
                            instruction(chip8, OP_FX1E);
                            break;
                        }

                        default:
                        {
                            printf_s("There seems to be an error with determining the opcode.\n");
                            exit(DET_OPCODE_ERROR);
                            break;
                        }

                    }

                    break;
                }

                case 0x2:
                {
                    instruction(chip8, OP_FX29);
                    break;
                }

                case 0x3:
                {
                    instruction(chip8, OP_FX33);
                    break;
                }

                case 0x5:
                {
                    instruction(chip8, OP_FX55);
                    break;
                }

                case 0x6:
                {
                    instruction(chip8, OP_FX65);
                    break;
                }

                default:
                {
                    printf_s("There seems to be an error with determining the opcode.\n");
                    exit(DET_OPCODE_ERROR);
                    break;
                }
            }
        }

        default:
        {
            printf_s("There seems to be an error with determining the opcode.\n");
            exit(DET_OPCODE_ERROR);
            break;
        }
    }
}

void instruction(CHIP8* chip8, int instruction)
{
    switch (instruction)
    {
        case OP_00E0:
        {
            printf_s("Initiating OP_00E0\n");
            printf_s("Clearing screen...\n");
            memset(chip8->monitor, 0, sizeof(chip8->monitor[0]));
            chip8->pc += 2;
            printf_s("PC at 0x%x\n", chip8->pc);
            printf_s("opcode: 0x%x\n", chip8->opcode);
            break;
        }

        case OP_00EE:
        {
            printf_s("Initiating OP_00EE\n");
            break;
        }

        case OP_0NNN:
        {
            printf_s("Initiating OP_0NNN\n");
            break;
        }

        case OP_1NNN:
        {
            // This instruction should simply set PC to NNN,
            // causing the program to jump to that memory location.
            // Do not increment the PC afterwards, it jumps directly there.
            printf_s("Initiating OP_1NNN\n");
            unsigned short NNN = chip8->opcode & 0x0FFFu;
            chip8->pc = NNN;
            break;
        }

        case OP_2NNN:
        {
            printf_s("Initiating OP_2NNN\n");
            break;
        }

        case OP_3XNN:
        {
            printf_s("Initiating OP_3XNN\n");
            break;
        }

        case OP_4XNN:
        {
            printf_s("Initiating OP_4XNN\n");
            break;
        }

        case OP_5XY0:
        {
            printf_s("Initiating OP_5XY0\n");
            break;
        }

        case OP_6XNN:
        {
            // Simply set the register Vx to the value NN.
            printf_s("Initiating OP_6XNN\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8->opcode & 0x00FFu;
            chip8->registers[Vx] = NN;
            printf_s("The value of the register V%x should be 0x%x and is: 0x%x\n", Vx, NN, chip8->registers[Vx]);
            chip8->pc += 2;
            break;
        }

        case OP_7XNN:
        {
            // Add the value NN to Vx (no flag).
            printf_s("Initiating OP_7XNN\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short NN = (chip8->opcode & 0x00FFu);
            printf_s("Should add to V%x (value=0x%x) the number %x;", Vx, chip8->registers[Vx], NN);
            chip8->registers[Vx] += NN;
            printf_s(" new value is: 0x%x\n", chip8->registers[Vx]);
            chip8->pc += 2;
            break;
        }

        case OP_8XY0:
        {
            // Vx is set to the value of Vy.
            printf_s("Initiating OP_8XY0\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy];
            break;
        }

        case OP_8XY1:
        {
            // Vx is set to Vx OR Vy.
            printf_s("Initiating OP_8XY1\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vx] | chip8->registers[Vy];
            break;
        }

        case OP_8XY2:
        {
            // Vx is set to Vx AND Vy.
            printf_s("Initiating OP_8XY2\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vx] & chip8->registers[Vy];
            break;
        }

        case OP_8XY3:
        {
            // Vx is set to Vx XOR Vy.
            printf_s("Initiating OP_8XY3\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vx] ^ chip8->registers[Vy];
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
            printf_s("Initiating OP_8XY4\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vx] + chip8->registers[Vy];
            if (chip8->registers[Vx] > 0x00FF) chip8->registers[0x000F] = 0x0001;
            else chip8->registers[0x000F] = 0x0000;
            break;
        }

        case OP_8XY5:
        {
            // sets VX to the result of VX - VY.
            printf_s("Initiating OP_8XY5\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vx] - chip8->registers[Vy];
            break;
        }

        case OP_8XY6:
        {
            // Set VX to the value of VY, shift the value of VX
            // one bit to the right, set VF to 1 if the bit that
            // was shifted out was 1, or 0 if it was 0.
            printf_s("Initiating OP_8XY6\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy];
            unsigned short sh_bit = chip8->registers[Vx] & 0x000F;
            chip8->registers[Vx] >> 1u;
            if (sh_bit) chip8->registers[0x000F] = 0x0001;
            else chip8->registers[0x000F] = 0x0000;
            break;
        }

        case OP_8XY7:
        {
            // 8XY7 sets VX to the result of VY - VX.
            printf_s("Initiating OP_8XY7\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy] - chip8->registers[Vx];
            break;
        }

        case OP_8XYE:
        {
            // Set VX to the value of VY, shift the value of VX
            // one bit to the left, set VF to 1 if the bit that
            // was shifted out was 1, or 0 if it was 0.
            printf_s("Initiating OP_8XYE\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy];
            unsigned short sh_bit = chip8->registers[Vx] & 0xF000;
            chip8->registers[Vx] << 1u;
            if (sh_bit) chip8->registers[0x000F] = 0x0001;
            else chip8->registers[0x000F] = 0x0000;
            break;
        }

        case OP_9XY0:
        {
            printf_s("Initiating OP_9XY0\n");
            break;
        }

        case OP_ANNN:
        {
            // Sets the index register to the value NNN.
            printf_s("Initiating OP_ANNN\n");
            unsigned short NNN = (chip8->opcode & 0x0FFFu);
            chip8->index = NNN;
            printf_s("Index register = 0x%x\n", NNN);
            chip8->pc += 2;
            break;
        }

        case OP_BNNN:
        {
            printf_s("Initiating OP_BNNN\n");
            break;
        }

        case OP_CXNN:
        {
            printf_s("Initiating OP_CXNN\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8->opcode & 0x00FFu;
            unsigned char random = rand_byte() & NN;
            chip8->registers[Vx] = random;
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
            printf_s("Initiating OP_DXYN\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            unsigned char X = chip8->registers[Vx] & 0x3Fu;
            unsigned char Y = chip8->registers[Vy] & 0x1Fu;
            chip8->registers[0xFu] = 0x0u;
            unsigned char N = chip8->opcode & 0xFu;
            
            for (int row = 0; row < N; row++)
            {
                unsigned char sprite_byte = chip8->memory[chip8->index + row];
                for (int bit = 0; bit < 8; ++bit)
                {
                    unsigned char sprite_pixel = sprite_byte & (0x80u >> bit);
                    unsigned char screen_pixel = chip8->monitor[Y + row][X];

                    if (sprite_pixel)
                    {
                        if(screen_pixel)
                        {
                            chip8->registers[0xF] = 1;
                        }
                        
                        chip8->monitor[Y + row][X + bit] ^= 0x1;
                    }
                }
            }
            
            chip8->pc += 2;
            chip8->update_screen = 1;
            break;
        }

        case OP_EX9E:
        {
            printf_s("Initiating OP_EX9E\n");
            break;
        }

        case OP_EXA1:
        {
            printf_s("Initiating OP_EXA1\n");
            break;
        }

        case OP_FX07:
        {
            printf_s("Initiating OP_FX07\n");
            break;
        }

        case OP_FX0A:
        {
            printf_s("Initiating OP_FX0A\n");
            break;
        }

        case OP_FX15:
        {
            printf_s("Initiating OP_FX15\n");
            break;
        }

        case OP_FX18:
        {
            printf_s("Initiating OP_FX18\n");
            break;
        }

        case OP_FX1E:
        {
            printf_s("Initiating OP_FX1E\n");
            break;
        }

        case OP_FX29:
        {
            printf_s("Initiating OP_FX29\n");
            break;
        }

        case OP_FX33:
        {
            printf_s("Initiating OP_FX33\n");
            break;
        }

        case OP_FX55:
        {
            printf_s("Initiating OP_FX55\n");
            break;
        }

        case OP_FX65:
        {
            printf_s("Initiating OP_FX65\n");
            break;
        }

        default:
        {
            printf_s("There seems to be an error with determining the opcode.\n");
            exit(DET_OPCODE_ERROR);
            break;
        }
    }
}
