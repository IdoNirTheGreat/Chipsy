# include <stdio.h>
# include <stdlib.h>
# include "fonts.h"
# define COLS 64
# define ROWS 32
# define KEYS 16
const unsigned int START_ADDRESS = 0x200;

struct Machine
{
    unsigned char registers[16];
    unsigned char memory[4096];
    unsigned short index;
    unsigned short pc;
    unsigned short stack[16];
    unsigned char sp;
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned char keypad[KEYS];
    unsigned long video[COLS * ROWS];
    unsigned long opcode;
};

void load_ROM(struct Machine chip8, char const* filename)
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

    // Initialize program counter:
    chip8.pc = START_ADDRESS;

    // Load fonts int machine memory:
    for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
        chip8.memory[FONTSET_START_ADDRESS + i] = fontset[i];
}

int main()
{
    printf("Hello world!\n");
    printf("%d", sizeof(unsigned char));
    return 0;
}