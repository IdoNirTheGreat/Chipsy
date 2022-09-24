# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "opcode.h"
# include "randGen.h"
# include "fonts.h"

# define COLS 64
# define ROWS 32

void decode(CHIP8* chip8)
{
    unsigned char frst_bt = (chip8->opcode & 0xF000u) >> 12;
    switch (frst_bt)
    {
        case 0x0:
        {
            switch (chip8->opcode)
            {
                case 0x00E0u:
                {
                    execute(chip8, OP_00E0);
                    break;
                }

                case 0x00EEu:
                {
                    execute(chip8, OP_00EE);
                    break;
                }

                default:
                {
                    printf_s("There seems to be an error \
                            with determining the opcode. \
                            Opcode = 0x%x\n", chip8->opcode);
                    exit(DECODE_OPCODE_ERROR);
                    break;
                }
            }
            
            break;
        }

        case 0x1:
        {
            execute(chip8, OP_1NNN);
            break;
        }

        case 0x2:
        {
            execute(chip8, OP_2NNN);
            break;
        }

        case 0x3:
        {
            execute(chip8, OP_3XNN);
            break;
        }

        case 0x4:
        {
            execute(chip8, OP_4XNN);
            break;
        }

        case 0x5:
        {
            execute(chip8, OP_5XY0);
            break;
        }

        case 0x6:
        {
            execute(chip8, OP_6XNN);
            break;
        }

        case 0x7:
        {
            execute(chip8, OP_7XNN);
            break;
        }

        case 0x8:
        {
            unsigned char frth_bt = chip8->opcode & 0x000Fu;
            switch (frth_bt)
            {
                case 0x0:
                {
                    execute(chip8, OP_8XY0);
                    break;
                }

                case 0x1:
                {
                    execute(chip8, OP_8XY1);
                    break;
                }

                case 0x2:
                {
                    execute(chip8, OP_8XY2);
                    break;
                }

                case 0x3:
                {
                    execute(chip8, OP_8XY3);
                    break;
                }

                case 0x4:
                {
                    execute(chip8, OP_8XY4);
                    break;
                }

                case 0x5:
                {
                    execute(chip8, OP_8XY5);
                    break;
                }

                case 0x6:
                {
                    execute(chip8, OP_8XY6);
                    break;
                }

                case 0x7:
                {
                    execute(chip8, OP_8XY7);
                    break;
                }

                case 0xE:
                {
                    execute(chip8, OP_8XYE);
                    break;
                }

                default:
                {
                    printf_s("There seems to be an error \
                            with determining the opcode. \
                            Opcode = 0x%x\n", chip8->opcode);
                    exit(DECODE_OPCODE_ERROR);
                    break;
                }
            }

            break;
        }

        case 0x9:
        {
            execute(chip8, OP_9XY0);
            break;
        }

        case 0xA:
        {
            execute(chip8, OP_ANNN);
            break;
        }

        case 0xB:
        {
            execute(chip8, OP_BNNN);
            break;
        }

        case 0xC:
        {
            execute(chip8, OP_CXNN);
            break;
        }

        case 0xD:
        {
            execute(chip8, OP_DXYN);
            break;
        }

        case 0xE:
        {
            unsigned char thrd_bt = (chip8->opcode & 0x00F0u) >> 4;
            switch (thrd_bt)
            {
                case 0x9:
                {
                    execute(chip8, OP_EX9E);
                    break;
                }

                case 0xA:
                {
                    execute(chip8, OP_EXA1);
                    break;
                }

                default:
                {
                    printf_s("There seems to be an error \
                            with decoding the opcode. \
                            Opcode = 0x%x\n", chip8->opcode);
                    exit(DECODE_OPCODE_ERROR);
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
                            execute(chip8, OP_FX07);
                            break;
                        }

                        case 0xA:
                        {
                            execute(chip8, OP_FX0A);
                            break;
                        }

                        default:
                        {
                            printf_s("There seems to be an \
                            error with decoding the \
                            opcode. Opcode = 0x%x\n", 
                            chip8->opcode);
                            exit(DECODE_OPCODE_ERROR);
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
                            execute(chip8, OP_FX15);
                            break;
                        }

                        case 0x8:
                        {
                            execute(chip8, OP_FX18);
                            break;
                        }

                        case 0xE:
                        {
                            execute(chip8, OP_FX1E);
                            break;
                        }

                        default:
                        {
                            printf_s("There seems to be an \
                            error with decoding the \
                            opcode. Opcode = 0x%x\n",
                            chip8->opcode);
                            exit(DECODE_OPCODE_ERROR);
                            break;
                        }

                    }

                    break;
                }

                case 0x2:
                {
                    execute(chip8, OP_FX29);
                    break;
                }

                case 0x3:
                {
                    execute(chip8, OP_FX33);
                    break;
                }

                case 0x5:
                {
                    execute(chip8, OP_FX55);
                    break;
                }

                case 0x6:
                {
                    execute(chip8, OP_FX65);
                    break;
                }

                default:
                {
                    printf_s("There seems to be an error \
                            with decoding the opcode. \
                            Opcode = 0x%x\n", chip8->opcode);
                    exit(DECODE_OPCODE_ERROR);
                    break;
                }
            }
            break;
        }

        default:
        {
            printf_s("There seems to be an error \
                            with decoding the opcode. \
                            Opcode = 0x%x\n", chip8->opcode);
            exit(DECODE_OPCODE_ERROR);
            break;
        }
    }
}

void execute(CHIP8* chip8, int opcode)
{
    switch (opcode)
    {
        case OP_00E0:
        {   /*
             * This instruction clears the CHIP-8's screen.
             */
            memset(chip8->monitor, 0, sizeof(chip8->monitor[0]));
            chip8->update_screen = 1;
            chip8->pc += 2;
            break;
        }

        case OP_00EE:
        {   /*
             * This instruction finishes the subroutine in 
             * the top of the stack: it pops the subroutine 
             * out of the stack, and sets the pc to the new 
             * subroutine in the top of the stack.
             */
            chip8->stack[chip8->sp] = 0;
            --chip8->sp;
            chip8->pc = chip8->stack[chip8->sp];
            break;
        }

        case OP_1NNN:
        {   /*
             * This instruction should simply set PC to NNN, 
             * causing the program to jump to that memory 
             * location. Do not increment the PC afterwards, 
             * it jumps directly there.
             */
            unsigned short NNN = chip8->opcode & 0x0FFFu;
            chip8->pc = NNN;
            break;
        }

        case OP_2NNN:
        {   /*
             * This instruction calls the subroutine in NNN: 
             * Instead of jumping like in 1NNN, it pushes the
             * subroutine to the stack, and sets the pc to 
             * the new subroutine. Note that it should first 
             * push the next-to-current PC first so it can 
             * return to the current place later.
             */
            unsigned short NNN = chip8->opcode & 0x0FFFu;
            chip8->stack[chip8->sp] = chip8->pc + 2;
            ++chip8->sp;
            chip8->pc = NNN;
            break;
        }

        case OP_3XNN:
        {   /*
             * Skips the next instruction if VX equals NN 
             * (Usually the next instruction is a jump to 
             * skip a code block).
             */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned char NN = chip8->opcode & 0x00FFu;
            if (chip8->registers[Vx] == NN)
                chip8->pc += 2;
            chip8->pc += 2;
            break;
        }

        case OP_4XNN:
        {   /*
            * Skips the next instruction if VX does not equal
            * NN (Usually the next instruction is a jump to 
            * skip a code block).
             */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned char NN = chip8->opcode & 0x00FFu;
            if (chip8->registers[Vx] != NN)
                chip8->pc += 2;
            chip8->pc += 2;
            break;
        }

        case OP_5XY0:
        {   /*
             * Skips the next instruction if VX equals VY 
             * (Usually the next instruction is a jump to 
             * skip a code block).
             */
            
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
            /* Simply set the register Vx to the value NN. */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8->opcode & 0x00FFu;
            chip8->registers[Vx] = NN;
            chip8->pc += 2;
            break;
        }

        case OP_7XNN:
        {
            /* Add the value NN to Vx (no flag). */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8->opcode & 0x00FFu;
            chip8->registers[Vx] += NN;
            chip8->pc += 2;
            break;
        }

        case OP_8XY0:
        {
            /* Vx is set to the value of Vy. */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY1:
        {
            /* Vx is set to Vx OR Vy. */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] |= chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY2:
        {
            /* Vx is set to Vx AND Vy. */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] &= chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY3:
        {
            /* Vx is set to Vx XOR Vy. */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] ^= chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY4:
        {   /*
             * VX is set to the value of VX plus the value of
             * VY. VY is not affected. Unlike 7XNN, this 
             * addition will affect the carry flag. If the 
             * result is larger than 255 (and thus overflows 
             * the 8-bit register VX), the flag register VF 
             * is set to 1. If it doesn’t overflow, VF is set
             * to 0.
             */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            if (chip8->registers[Vx] + chip8->registers[Vy] > 0xFF)
                chip8->registers[0xF] = 1;
            else
                chip8->registers[0xF] = 0;
            chip8->registers[Vx] += chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY5:
        {   /*
             * Sets VX to the result of VX - VY. Vf is set to 
             * 0 if there is a borrow, 1 if there isn't.
             */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            if ((int)chip8->registers[Vx] - chip8->registers[Vy] < 0)
                chip8->registers[0xF] = 0;
            else 
                chip8->registers[0xF] = 1;
            chip8->registers[Vx] -= chip8->registers[Vy];
            chip8->pc += 2;
            break;
        }

        case OP_8XY6:
        {   /*
             * Set VX to the value of VY, shift the value of 
             * VX one bit to the right, set VF to 1 if the 
             * bit that was shifted out was 1, or 0 if it was
             * 0.
             */ 
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy];
            unsigned short sh_bit = chip8->registers[Vx] & 0xF;
            chip8->registers[Vx] >>= 1u;
            if (sh_bit) 
                chip8->registers[0xF] = 1;
            else 
                chip8->registers[0xF] = 0;
            chip8->pc += 2;
            break;
        }

        case OP_8XY7:
        {
            /* Sets VX to the result of VY - VX. */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy] - chip8->registers[Vx];
            chip8->pc += 2;
            break;
        }

        case OP_8XYE:
        {   /*
             * Set VX to the value of VY, shift the value of 
             * VX one bit to the left, set VF to 1 if the bit
             * that was shifted out was 1, or 0 if it was 0.
             */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            chip8->registers[Vx] = chip8->registers[Vy];
            unsigned short sh_bit = chip8->registers[Vx] & 0xF000u;
            chip8->registers[Vx] <<= 1u;
            if (sh_bit) 
                chip8->registers[0xF] = 1;
            else 
                chip8->registers[0x0F] = 0;
            chip8->pc += 2;
            break;
        }

        case OP_9XY0:
        {   /*
             * Skips instruction if Vx and Vy are not equal.
             */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned char Vy = (chip8->opcode & 0x00F0u) >> 4u;
            if (chip8->registers[Vx] != chip8->registers[Vy])
                chip8->pc += 2;
            chip8->pc += 2;
            break;
        }

        case OP_ANNN:
        {
            /* Sets the index register to the value NNN. */
            unsigned short NNN = (chip8->opcode & 0x0FFFu);
            chip8->index = NNN;
            chip8->pc += 2;
            break;
        }

        case OP_BNNN:
        {
            /* Jumps to the address NNN plus V0. */
            unsigned short NNN = chip8->opcode & 0x0FFFu;
            chip8->pc = chip8->registers[0x0] + NNN;
            break;
        }

        case OP_CXNN:
        {   /*
             * Sets VX to the result of a bitwise and 
             * operation on a random number (Typically: 0 
             * to 255) and NN.
             */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short NN = chip8->opcode & 0x00FFu;
            unsigned char random = rand_byte() & NN;
            chip8->registers[Vx] = random;
            chip8->pc += 2;
            break;
        }

        case OP_DXYN:
        {   /*
             * This is the drawing instruction. It will draw
             * an N pixels tall sprite from the memory 
             * location that the I index register is holding 
             * to the screen, at the horizontal X coordinate 
             * in VX and the Y coordinate in VY. All the 
             * pixels that are “on” in the sprite will flip 
             * the pixels on the screen that it is drawn to. 
             * If any pixels on the screen were turned “off” 
             * by this, the VF flag register is set to 1. 
             * Otherwise, it’s set to 0.
             */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
            unsigned char X = chip8->registers[Vx] & 0x3Fu;
            unsigned char Y = chip8->registers[Vy] & 0x1Fu;
            chip8->registers[0xFu] = 0;
            unsigned char N = chip8->opcode & 0xF;
            
            for (int row = 0; row < N; row++)
            {
                unsigned char sprite_byte = chip8->memory[chip8->index + row];
                for (int bit = 0; bit < 8; ++bit)
                {
                    unsigned char sprite_pixel = sprite_byte & (0x80u >> bit);
                    if (sprite_pixel)
                    {
                        if(chip8->monitor[Y + row][X + bit])
                            chip8->registers[0xF] = 1;
                        
                        chip8->monitor[Y + row][X + bit] ^= 1;
                    }
                }
            }
            
            chip8->pc += 2;
            chip8->update_screen = 1;
            break;
        }

        case OP_EX9E:
        {   /*
             * Skip one instruction (increment PC by 2) if 
             * the key corresponding to the value in Vx is 
             * pressed.
             */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            if(chip8->active_keys[chip8->registers[Vx]])
                chip8->pc += 2;
            chip8->pc += 2;
            break;
        }

        case OP_EXA1:
        {   /*
             * Skip one instruction (increment PC by 2) if 
             * the key corresponding to the value in Vx is 
             * *not* pressed.
             */
            unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
            if(!chip8->active_keys[chip8->registers[Vx]])
                chip8->pc += 2;
            chip8->pc += 2;
            break;
        }

        case OP_FX07:
        {   /*
             * Sets Vx to the current value of the delay 
             * timer.
             */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            chip8->registers[Vx] = chip8->delay_timer;
            chip8->pc += 2;
            break;
        }

        case OP_FX0A:
        {   /*
             * This instruction “blocks”; it stops executing 
             * instructions and waits for key input. If a key
             * is pressed while this instruction is waiting 
             * for input, its hexadecimal value will be put 
             * in VX and execution continues. Timers still 
             * work at BG.
             */
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
            /* Sets the delay timer to the value in Vx. */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            chip8->delay_timer = chip8->registers[Vx];
            chip8->pc += 2;
            break;
        }

        case OP_FX18:
        {
            /* Sets the sound timer to the value in Vx. */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            chip8->sound_timer = chip8->registers[Vx];
            chip8->pc += 2;
            break;
        }

        case OP_FX1E:
        {   /*
             * The index register I will get the value in 
             * VX added to it.
             */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            chip8->index += chip8->registers[Vx];
            chip8->pc += 2;
            break;
        }

        case OP_FX29:
        {   /* 
             * The index register I is set to the address of
             * the hexadecimal character in VX.
             */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;

            // Each character is 5 sprite bytes:
            chip8->index = FONTSET_START_ADDRESS + chip8->registers[Vx] * 5; 

            chip8->pc += 2;
            break;
        }

        case OP_FX33:
        {   /*
             * This instruction takes the number stored in 
             * Vx, converts it to decimal base and stores 
             * it's decimal digits in the index register.
             */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            unsigned char value = chip8->registers[Vx];
            chip8->memory[chip8->index] = value / 100;
            chip8->memory[chip8->index + 1] = value / 10 - 10 * (value / 100);
            chip8->memory[chip8->index + 2] = value % 10;
            chip8->pc += 2;
            break;
        }

        case OP_FX55:
        {   /*
             * For FX55, the value of each variable register 
             * from V0 to VX inclusive (if X is 0, then only 
             * V0) will be stored in successive memory 
             * addresses, starting with the one that’s stored
             * in I. V0 will be stored at the address in I,
             * V1 will be stored in I + 1, and so on, until 
             * VX is stored in I + X.
             */
            unsigned char Vx = (chip8->opcode & 0x0F00u) >> 8u;
            for (int i = 0; i <= Vx; i++)
            {
                chip8->memory[chip8->index + i] = chip8->registers[i];
            }
            chip8->pc += 2;
            break;
        }

        case OP_FX65:
        {   /*
             * For FX65, the value of each variable register 
             * from V0 to VX inclusive (if X is 0, then only 
             * V0) will be set in by values in successive 
             * memory addresses, starting with the one that’s
             * stored in I. V0 will be set as the value in 
             * address in I, V1 will be set as the value in 
             * I + 1, and so on, until VX is set as the value
             * in I + X.
             */
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
            printf_s("There seems to be an error with \
                    decoding the opcode. Opcode = 0x%x\n",
                    chip8->opcode);
            exit(DECODE_OPCODE_ERROR);
            break;
        }
    }
}
