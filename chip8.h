# ifndef INC_CHIP8_H
# define INC_CHIP8_H
# define COLS 64
# define ROWS 32
# define KEYS 16

extern const unsigned int START_ADDRESS;    /* 
                                             * Start address 
                                             * for the 
                                             * CHIP8's ROM.
                                             */

typedef struct CHIP8    /* 
                         * The struct which holds all of the 
                         * CHIP-8's machines attributes.
                         */
{
    unsigned char registers[16];    /* 
                                     * 16 registers with a 
                                     * size of one byte each.
                                     */

    unsigned char memory[4096];     /* 
                                     * ROM size of 4096 
                                     * bytes.
                                     */

    unsigned short index;           /*
                                     * The index pointer.
                                     * Sometimes mentioned as
                                     * 'I'.
                                     */
                                    
    unsigned short pc;              /* The program counter. */

    unsigned short stack[16];       /* 
                                     * A stack that holds up 
                                     * to 16 instructions. 
                                     */

    unsigned char sp;               /* 
                                     * A stack pointer 
                                     * (points to the head 
                                     * of the stack). 
                                    */

    unsigned char delay_timer;      /* 
                                     * A delay timer with a 
                                     * 60 [Hz] refresh rate. 
                                    */

    unsigned char sound_timer;      /* 
                                    * A sound timer with a 60
                                    * [Hz] refresh rate. 
                                     */

    unsigned char monitor[ROWS][COLS]; /* 
                                        * A 2d array which 
                                        * stores each 
                                        * pixels's status. 
                                        */

    unsigned long opcode;   /* 
                             * A byte that holds the current 
                             * instruction's opcode.
                             */

    unsigned char update_screen;    /* 
                                     * A flag that tells if 
                                     * the screen needs to be
                                     * refreshed.
                                     */
                                
    unsigned char active_keys[KEYS]; /* 
                                      * An array of flags 
                                      * that tells if the key
                                      * in the matching index
                                      * is pressed or not.
                                      */

    unsigned char is_kbhit; /* 
                             * A flag that tells if there is 
                             * a key which is pressed down at
                             * all.
                             */
} CHIP8; 

void load_ROM(CHIP8* chip8, char const* filename);  
    /*
     * Loads ROM data from filename to chip8 VM.
     */

void load_fonts(CHIP8* chip8); 
    /*
     * Loads fonts to chip8 VM.
     */

void init_chip8(CHIP8* chip8, char const* rom); 
    /*
     * Main function to init VM.
     */

void cycle(CHIP8* chip8);  
    /*
     * Operate one CPU cycle.
     */

#endif
