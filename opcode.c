# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <conio.h>
# include "opcode.h"
# include "randGen.h"
# include "fonts.h"
# define COLS 64
# define ROWS 32

void det_opcode(CHIP8* chip8)
{
    // printf_s("Opcode in determination function: %x\n", chip8->opcode);
    unsigned char frst_bt = (chip8->opcode & 0xF000u) >> 12;
    switch (frst_bt)
    {
        case 0x0:
        {
            switch (chip8->opcode)
            {
                case 0x00E0u:
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
            unsigned char thrd_bt = (chip8->opcode & 0x00F0u) >> 4;
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

void instruction(CHIP8* chip8, int instruction)
{
    switch (instruction)
    {
        case OP_00E0:
        {
            // printf_s("Initiating OP_00E0\n");
            // printf_s("Clearing screen...\n");
            memset(chip8->monitor, 0, sizeof(chip8->monitor[0]));
            chip8->update_screen = 1;
            chip8->pc += 2;
            break;
        }

        case OP_00EE:
        {
            // This instruction finishes the subroutine in the
            // top of the stack: it pops the subroutine out of
            // the stack, and sets the pc to the new subroutine
            // in the top of the stack.
            // printf_s("Initiating OP_00EE\n");
            chip8->stack[chip8->sp] = 0;
            --chip8->sp;
            chip8->pc = chip8->stack[chip8->sp];
            // printf_s("*** Start of Stack ***\n");
            // int i = 0;
            // for(i = 0; i < chip8->sp; i++)
            // {
            //     printf_s("|(%d): 0x%x|", i, chip8->stack[i]);
            // }
            // printf_s("|(%d): 0x%x|\n", i, chip8->pc);
            // printf_s("*** End of Stack ***\n");
            break;
        }

        case OP_0NNN:
        {
            // Call machine language subroutine at address NNN.
            //  printf_s("Initiating OP_0NNN\n");
            chip8->pc += 2;
            break;
        }

        case OP_1NNN:
        {
            // This instruction should simply set PC to NNN,
            // causing the program to jump to that memory location.
            // Do not increment the PC afterwards, it jumps directly there.
            //  printf_s("Initiating OP_1NNN\n");
            unsigned short NNN = chip8->opcode & 0x0FFFu;
            chip8->pc = NNN;
            break;
        }

        case OP_2NNN:
        {
            // This instruction calls the subroutine in NNN:
            // Instead of jumping like in 1NNN, it pushes the
            // subroutine to the stack, and sets the pc to the 
            // new subroutine. Note that it should first push the
            // next-to-current PC first so it can return to the current 
            // place later.
            // printf_s("Initiating OP_2NNN\n");
            unsigned short NNN = chip8->opcode & 0x0FFFu;
            chip8->stack[chip8->sp] = chip8->pc + 2;
            ++chip8->sp;
            chip8->pc = NNN;
            // printf_s("*** Start of Stack ***\n");
            // int i = 0;
            // for(i = 0; i < chip8->sp; i++)
            // {
            //     printf_s("|(%d): 0x%x|", i, chip8->stack[i]);
            // }
            // printf_s("|(%d): 0x%x|\n", i, chip8->pc);
            // printf_s("*** End of Stack ***\n");
            break;
        }

        case OP_3XNN:
        {
            // Skips the next instruction if VX equals NN. 
            // (Usually the next instruction is a jump to skip
            // a code block);
            // printf_s("Initiating OP_3XNN\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned char NN = chip8->opcode & 0x00FFu;
            if (chip8->registers[Vx] == NN)
            {
                chip8->pc += 2;
            }
            chip8->pc += 2;
            break;
        }

        case OP_4XNN:
        {
            // Skips the next instruction if VX does not equal NN.
            // (Usually the next instruction is a jump to skip a code
            // block);
            // printf_s("Initiating OP_4XNN\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned char NN = chip8->opcode & 0x00FFu;
            if (chip8->registers[Vx] != NN)
            {
                chip8->pc += 2;
            }
            chip8->pc += 2;
            break;
        }

        case OP_5XY0:
        {
            // Skips the next instruction if VX equals VY.
            // (Usually the next instruction is a jump to skip
            // a code block);
            // printf_s("Initiating OP_5XY0\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned char Vy = (chip8->opcode & 0x00F0u) >> 4u;
            if (chip8->registers[Vx] == chip8->registers[Vy])
            {
                chip8->pc += 2;
            }
            chip8->pc += 2;
            break;
        }

        case OP_6XNN:
        {
            // Simply set the register Vx to the value NN.
            // printf_s("Initiating OP_6XNN\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8->opcode & 0x00FFu;
            chip8->registers[Vx] = NN;
            chip8->pc += 2;
            break;
        }

        case OP_7XNN:
        {
            // Add the value NN to Vx (no flag).
            // printf_s("Initiating OP_7XNN\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8->opcode & 0x00FFu;
            chip8->registers[Vx] += NN;
            chip8->pc += 2;
            break;
        }

        case OP_8XY0:
        {
            // Vx is set to the value of Vy.
            // printf_s("Initiating OP_8XY0\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY1:
        {
            // Vx is set to Vx OR Vy.
            // printf_s("Initiating OP_8XY1\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] |= chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY2:
        {
            // Vx is set to Vx AND Vy.
            // printf_s("Initiating OP_8XY2\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] &= chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY3:
        {
            // Vx is set to Vx XOR Vy.
            // printf_s("Initiating OP_8XY3\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] ^= chip8->registers[Vy];
            chip8->pc += 2;
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
            // printf_s("Initiating OP_8XY4\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            if (chip8->registers[Vx] + chip8->registers[Vy] > 0xFF) chip8->registers[0xF] = 1;
            else chip8->registers[0xF] = 0;
            chip8->registers[Vx] += chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY5:
        {
            // sets VX to the result of VX - VY.
            // printf_s("Initiating OP_8XY5\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            if ((int)chip8->registers[Vx] - chip8->registers[Vy] < 0) chip8->registers[0xF] = 0;
            else chip8->registers[0xF] = 1;
            chip8->registers[Vx] -= chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY6:
        {
            // Set VX to the value of VY, shift the value of VX
            // one bit to the right, set VF to 1 if the bit that
            // was shifted out was 1, or 0 if it was 0.
            // printf_s("Initiating OP_8XY6\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy];
            unsigned short sh_bit = chip8->registers[Vx] & 0x000F;
            chip8->registers[Vx] >>= 1u;
            if (sh_bit) chip8->registers[0x000F] = 0x0001;
            else chip8->registers[0x000F] = 0x0000;
            chip8->pc += 2;
            break;
        }

        case OP_8XY7:
        {
            // 8XY7 sets VX to the result of VY - VX.
            // printf_s("Initiating OP_8XY7\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy] - chip8->registers[Vx];
            chip8->pc += 2;
            break;
        }

        case OP_8XYE:
        {
            // Set VX to the value of VY, shift the value of VX
            // one bit to the left, set VF to 1 if the bit that
            // was shifted out was 1, or 0 if it was 0.
            // printf_s("Initiating OP_8XYE\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy];
            unsigned short sh_bit = chip8->registers[Vx] & 0xF000;
            chip8->registers[Vx] <<= 1u;
            if (sh_bit) chip8->registers[0x000F] = 0x0001;
            else chip8->registers[0x000F] = 0x0000;
            chip8->pc += 2;
            break;
        }

        case OP_9XY0:
        {
            // Skips instruction if Vx and Vy are not equal.
            // printf_s("Initiating OP_9XY0\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned char Vy = (chip8->opcode & 0x00F0u) >> 4u;
            if (chip8->registers[Vx] != chip8->registers[Vy])
            {
                chip8->pc += 2;
            }
            chip8->pc += 2;
            break;
        }

        case OP_ANNN:
        {
            // Sets the index register to the value NNN.
            // printf_s("Initiating OP_ANNN\n");
            unsigned short NNN = (chip8->opcode & 0x0FFFu);
            chip8->index = NNN;
            chip8->pc += 2;
            break;
        }

        case OP_BNNN:
        {
            // Jumps to the address NNN plus V0.
            // printf_s("Initiating OP_BNNN\n");
            unsigned short NNN = chip8->opcode & 0x0FFFu;
            chip8->pc = chip8->registers[0x0] + NNN;
            break;
        }

        case OP_CXNN:
        {
            // Sets VX to the result of a bitwise and operation on
            // a random number (Typically: 0 to 255) and NN.
            // printf_s("Initiating OP_CXNN\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8->opcode & 0x00FFu;
            unsigned char random = rand_byte() & NN;
            chip8->registers[Vx] = random;
            chip8->pc += 2;
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
            // printf_s("Initiating OP_DXYN\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            unsigned char X = chip8->registers[Vx] & 0x3Fu;
            unsigned char Y = chip8->registers[Vy] & 0x1Fu;
            chip8->registers[0xFu] = 0;
            unsigned char N = chip8->opcode & 0xFu;
            
            for (int row = 0; row < N; row++)
            {
                unsigned char sprite_byte = chip8->memory[chip8->index + row];
                for (int bit = 0; bit < 8; ++bit)
                {
                    unsigned char sprite_pixel = sprite_byte & (0x80u >> bit);
                    
                    if (sprite_pixel)
                    {
                        if(chip8->monitor[Y + row][X + bit])
                        {
                            chip8->registers[0xF] = 1;
                        }
                        chip8->monitor[Y + row][X + bit] ^= 1;
                    }

                    // if(chip8->flag)
                    // {
                    //     // printf_s("sprite pixel = %d; screen pixel = %d; Vf = %d\n", sprite_pixel, chip8->monitor[Y + row][X + bit], chip8->registers[0xF]);
                    // }
                }
            }
            
            chip8->pc += 2;
            chip8->update_screen = 1;
            break;
        }

        case OP_EX9E:
        {
            // Skip one instruction (increment PC by 2) if the key
            // corresponding to the value in Vx is pressed.
            // printf_s("Initiating OP_EX9E\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            if(chip8->active_keys[chip8->registers[Vx]])
            {
                chip8->pc += 2;
            }
            chip8->pc += 2;
            break;
        }

        case OP_EXA1:
        {
            // Skip one instruction (increment PC by 2) if the key
            // corresponding to the value in Vx is *not* pressed.
            // printf_s("Initiating OP_EXA1\n");
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            if(!chip8->active_keys[chip8->registers[Vx]])
            {
                chip8->pc += 2;
            }
            chip8->pc += 2;
            break;
        }

        case OP_FX07:
        {
            // Sets Vx to the current value of the delay timer.
            // printf_s("Initiating OP_FX07\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            chip8->registers[Vx] = chip8->delay_timer;
            chip8->pc += 2;
            break;
        }

        case OP_FX0A:
        {
            // This instruction “blocks”; it stops executing instructions
            // and waits for key input. If a key is pressed while this 
            // instruction is waiting for input, its hexadecimal value will
            // be put in VX and execution continues. Timers still work at BG.
            // printf_s("Initiating OP_FX0A\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            
            if (chip8->is_kbhit)
            {
                for (int i = 0; i < KEYS; i++)
                {
                    if (chip8->active_keys[i])
                    {
                        chip8->registers[Vx] = i;
                        chip8->pc += 2;
                    }
                }
            }
            
            break;
        }

        case OP_FX15:
        {
            // Sets the delay timer to the value in Vx.
            // printf_s("Initiating OP_FX15\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            chip8->delay_timer = chip8->registers[Vx];
            // printf_s("***Delay timer has changed: %d***\n", chip8->delay_timer);
            chip8->pc += 2;
            break;
        }

        case OP_FX18:
        {
            // Sets the sound timer to the value in Vx.
            // printf_s("Initiating OP_FX18\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            chip8->sound_timer = chip8->registers[Vx];
            chip8->pc += 2;
            break;
        }

        case OP_FX1E:
        {
            // The index register I will get the value in VX added to it.
            // printf_s("Initiating OP_FX1E\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            chip8->index += chip8->registers[Vx];
            chip8->pc += 2;
            break;
        }

        case OP_FX29:
        {
            // The index register I is set to the address of 
            // the hexadecimal character in VX.
            // printf_s("Initiating OP_FX29\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            chip8->index = FONTSET_START_ADDRESS + chip8->registers[Vx] * 5; // Each character is 5 sprite bytes
            chip8->pc += 2;
            break;
        }

        case OP_FX33:
        {
            // This instruction takes the number stored in Vx,
            // converts it to decimal base and stores it's decimal
            // digits in the index register.
            // printf_s("Initiating OP_FX33\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned char value = chip8->registers[Vx];
            chip8->memory[chip8->index] = value / 100;
            chip8->memory[chip8->index + 1] = value / 10 - 10 * (value / 100);
            chip8->memory[chip8->index + 2] = value % 10;
            chip8->pc += 2;
            break;
        }

        case OP_FX55:
        {
            // For FX55, the value of each variable register from V0
            // to VX inclusive (if X is 0, then only V0) will be stored
            // in successive memory addresses, starting with the one 
            // that’s stored in I. V0 will be stored at the address in I,
            // V1 will be stored in I + 1, and so on, until VX is stored
            // in I + X.
            // printf_s("Initiating OP_FX55\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            for (int i = 0; i <= Vx; i++)
            {
                chip8->memory[chip8->index + i] = chip8->registers[i];
            }
            chip8->pc += 2;
            break;
        }

        case OP_FX65:
        {
            // For FX65, the value of each variable register from V0
            // to VX inclusive (if X is 0, then only V0) will be set
            // in by values in successive memory addresses, starting 
            // with the one that’s stored in I. V0 will be set as the
            // the value in address in I, V1 will be set as the value
            // in I + 1, and so on, until VX is set as the value in 
            // I + X.
            // printf_s("Initiating OP_FX65\n");
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            for (int i = 0; i <= Vx; i++)
            {
                chip8->registers[i] = chip8->memory[chip8->index + i];
            }
            chip8->pc += 2;
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
