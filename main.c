# include "chip8.h"
# include "randGen.h"
# include <stdio.h>

int main()
{
    CHIP8 chipsy = {};
    init_chip8(chipsy, "");
    for(int i=0;i<20; ++i)
    {
        printf("%d\n", rand_byte());
    }
    return 0;
}