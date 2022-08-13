# include <stdio.h>
# include <stdlib.h>
# include "fonts.h"
# include "chip8.h"

const unsigned int START_ADDRESS = 0x200;

void load_ROM(CHIP8 chip8, char const* filename)
{
    // Open 'filename' as a stream of binary and move pointer to the end:
    FILE *fp = fopen(filename, "wb+");

    if (fp) // If filename exists:
    {
        // Get size of file and allocate buffer:
        fseek(fp, 0, SEEK_END);
        size_t fp_len = ftell(fp);
        char* buffer = calloc(fp_len, sizeof(char));

        // Reset file pointer, fill the buffer, close file:
        fseek(fp, 0, SEEK_SET); 
        fread(buffer, sizeof(fp_len), 1, fp); 
        fclose(fp);

        // Load ROM contents into machine's memory, starting at 0x200:
        for (long i = 0; i < fp_len, ++i;)
            chip8.memory[START_ADDRESS + i] = buffer[i];

        // Free the buffer to save space:
        free(buffer);
    }

}

void load_fonts(CHIP8 chip8)
{
    // Load fonts int machine memory:
    for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
        chip8.memory[FONTSET_START_ADDRESS + i] = fontset[i];
}

void init_chip8(CHIP8 chip8, char const* rom)
{
    load_ROM(chip8, rom);
    load_fonts(chip8);
}