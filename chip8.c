# include <stdio.h>
# include <stdlib.h>
# include "fonts.h"
# include "chip8.h"
# include "opcode.h"

const unsigned int START_ADDRESS = 0x200;

void load_ROM(CHIP8 chip8, char const* filename)
{
    // Open 'filename' as a stream of binary and move pointer to the end:
    FILE *fp = fopen(filename, "rb");

    if (fp) // If filename exists:
    {
        printf_s("File found.\n");
        // Get size of file and allocate buffer:
        fseek(fp, 0, SEEK_END);
        size_t fp_len = ftell(fp);
        char* buffer = calloc(fp_len, sizeof(char));

        // Reset file pointer, fill the buffer, close file:
        fseek(fp, 0, SEEK_SET); 
        fread(buffer, sizeof(fp_len), fp_len, fp); 
        fclose(fp);
        printf_s("File size is %d bits.\n", fp_len);
        
        // Load ROM contents into machine's memory, starting at 0x0200:
        for (int i = 0; i < fp_len * sizeof(unsigned char); ++i)
        {
            // printf_s("%d. %x\n", i, buffer[i]);
            chip8.memory[START_ADDRESS + i] = buffer[i];
            // if (chip8.memory[START_ADDRESS + i] != buffer[i])
            // {
            //     printf_s("%x, %x %d\n", chip8.memory[START_ADDRESS + i], buffer[i], i);
            // }
        }
        
        free(buffer);
        printf_s("ROM loaded successfully.\n");
    }

    else
    {
        printf_s("ROM loading has failed.\n");
    }
    
}

void load_fonts(CHIP8 chip8)
{
    // Load fonts into machine memory:
    for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
        chip8.memory[FONTSET_START_ADDRESS + i] = fontset[i];
    printf_s("Fonts loaded successfully.\n");
}

void init_chip8(CHIP8 chip8, char const* rom)
{
    load_ROM(chip8, rom);
    load_fonts(chip8);
    chip8.pc = START_ADDRESS;
}

void cycle(CHIP8 chip8)
{
    chip8.opcode = (chip8.memory[chip8.pc] << 8) + chip8.memory[chip8.pc + 1];
    printf_s("%x\n", chip8.opcode);
    det_opcode(chip8);
    chip8.opcode += 2;
}
