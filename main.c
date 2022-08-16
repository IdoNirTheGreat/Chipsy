# include "chip8.h"
# include <stdio.h>

enum error_code
{
    EXIT_SUCCESSFULLY,
    INCORRECT_AMOUNT_ARGUMENTS
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf_s("Incorrect amount of arguments!\n");
        return INCORRECT_AMOUNT_ARGUMENTS;
    }
    
    CHIP8 chipsy = {};
    init_chip8(&chipsy, argv[1]);
    for (int i = 0; i < 50; ++i)
    {
        printf_s("Cycle %d: ", i+1);
        cycle(&chipsy);
        printf_s("\n");
    }
}