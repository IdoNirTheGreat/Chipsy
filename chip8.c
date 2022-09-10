# include <stdio.h>
# include <stdlib.h>
# include "fonts.h"
# include "chip8.h"
# include "opcode.h"
# define printf_s

const unsigned int START_ADDRESS = 0x0200u;

void load_ROM(CHIP8* chip8, char const* filename)
{
    // Open 'filename' as a stream of binary and move pointer to the end:
    FILE *fp = fopen(filename, "rb");

    if (fp) // If filename exists:
    {
        printf_s("File found.\n");
        // Get size of file and allocate buffer:
        fseek(fp, 0, SEEK_END);
        size_t fp_len = ftell(fp);
        char* buffer = (char*) calloc(fp_len, sizeof(char));

        // Reset file pointer, fill the buffer, close file:
        fseek(fp, 0, SEEK_SET); 
        fread(buffer, sizeof(fp_len), fp_len, fp); 
        fclose(fp);
        printf_s("File size is %d bits.\n", fp_len);
        
        // Load ROM contents into machine's memory, starting at 0x0200:
        for (int i = 0; i < fp_len * sizeof(unsigned char); ++i)
        {
            chip8->memory[START_ADDRESS + i] = buffer[i];
        }
        
        free(buffer);
        printf_s("ROM loaded successfully.\n");
    }

    else
    {
        printf_s("ROM loading has failed.\n");
    }
    
}

void load_fonts(CHIP8* chip8)
{
    // Load fonts into machine memory:
    for (unsigned int i = 0; i < FONTSET_SIZE; i++)
        chip8->memory[FONTSET_START_ADDRESS + i] = fontset[i];
    printf_s("Fonts loaded successfully.\n");
}

void init_chip8(CHIP8* chip8, char const* rom)
{
    load_ROM(chip8, rom);
    load_fonts(chip8);
    chip8->pc = START_ADDRESS;
    chip8->update_screen = 0;
    printf_s("PC at 0x%x\n", chip8->pc);
}

void cycle(CHIP8* chip8)
{
    chip8->opcode = (chip8->memory[chip8->pc] << 8u) + chip8->memory[chip8->pc + 1];
    printf_s("Current opcode: %04x\n", chip8->opcode);
    det_opcode(chip8);
    printf_s("PC at %x\n", chip8->pc);
    if (chip8->delay_timer > 0) --chip8->delay_timer;
    if (chip8->sound_timer > 0) --chip8->sound_timer;
    printf_s("Delay timer = %d, Sound timer = %d\n", chip8->delay_timer, chip8->sound_timer);
}
