# include "chip8.h"
# include <stdio.h>

enum error_code
{
    EXIT_SUCCESSFULLY,
    TOO_MANY_ARGUMENTS
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf_s("Too many arguments!\n");
        return TOO_MANY_ARGUMENTS;
    }
    
    CHIP8 chipsy = {};
    init_chip8(chipsy, argv[1]);
}