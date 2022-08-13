# ifndef INC_CHIP8_H
# define INC_CHIP8_H
# define COLS 64
# define ROWS 32
# define KEYS 16

extern const unsigned int START_ADDRESS; /** Start address for CHIP8's ROM.*/;

typedef struct CHIP8 /** The CHIP8 Struct which holds all VM's components.*/
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
    unsigned long monitor[COLS * ROWS];
    unsigned long opcode;
} CHIP8; 

void load_ROM(CHIP8 chip8, char const* filename); /** Loads ROM data from filename to chip8 VM.*/

void load_fonts(CHIP8 chip8); /** Loads fonts to chip8 VM.*/

void init_chip8(CHIP8 chip8, char const* rom); /** Main function to init VM.*/

#endif