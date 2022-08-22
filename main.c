# include "chip8.h"
# include "SDL/include/SDL2/SDL.h"
# include <stdio.h>

# define SCALE 10
# define SCREEN_WIDTH 64 * SCALE
# define SCREEN_HEIGHT 32 * SCALE
# define MONITOR_REFRESH_INTERVAL 100 // In miliseconds
# define R_VAL 0 // Red display value
# define G_VAL 255 // Green display value
# define B_VAL 0 // Blue display value
# define FILENAME ".\\IBM_Logo.ch8"

enum error_code
{
    SDL_FAILED,
    GUI_FAILED,
};

void update_screen(SDL_Renderer* renderer, CHIP8* chip8)
{
    // int sum = 0;
    // printf_s("Actually drawn pixels: ");
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // for (unsigned int row = 0; row < ROWS; ++row)
    // {
    //     for (unsigned int col = 0; col < COLS; ++col)
    //     {
    //         if (monitor[COLS * (col) + row] == 1)
    //         {
    //             SDL_RenderDrawPoint(renderer, row, col);
    //             printf_s("[%d, %d], ", row, col);
    //             sum++;
    //         }
    //     }
    // }
    // printf_s("]\nTotal = %d\n", sum);
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // int row = 0;
    // int col = 0;
    // int sum = 0;
    // printf_s("Actually drawn pixels: ");
    // for (int i = 0; i < (ROWS * COLS); i++)
    // {
    //     col++;
    //     if (!(i % COLS))
    //     {
    //         row++;  
    //         col = 0;         
    //     }
    //     if (monitor[i])
    //     {
    //         SDL_RenderDrawPoint(renderer, col, row);
    //         printf_s("%d, ", i);
    //         //printf_s("[%d, %d], ", col, row);
    //         sum++;
    //     }
    // }
    // printf_s("]\nTotal = %d\n", sum);
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    unsigned short Vx = (chip8->opcode & 0x0F00u) >> 8u;
    unsigned short Vy = (chip8->opcode & 0x00F0u) >> 4u;
    unsigned char X = chip8->registers[Vx] & 0x3Fu;
    unsigned char Y = chip8->registers[Vy] & 0x1Fu;
    chip8->registers[0xFu] = 0x0u;
    unsigned char N = chip8->opcode & 0xFu;
    // int sum = 0;
    // printf_s("Actually drawn pixels: [");
    for (int row = 0; row < N; ++row)
    {
        unsigned char sprite_byte = chip8->memory[chip8->index + row];
        for (int bit = 0; bit < 8; ++bit)
        {
            unsigned char sprite_pixel = sprite_byte & (0x80u >> bit);
            unsigned char screen_pixel = chip8->monitor[((Y + row) * ROWS) + X];
            
            if (chip8->monitor[(Y + row) * ROWS + X + bit])
            {
                SDL_RenderDrawPoint(renderer, (X + bit), (Y + row));
                // printf_s("[%d,%d], ", (X + bit) , (Y + row));
                // printf_s("%d, ", (Y + row) * ROWS + X + bit);
                // sum++;
            }
        }
    }

    SDL_RenderPresent(renderer);
}

int WinMain(int argc, char* args[])
{
    // SDL Setup:
    SDL_Window* window = SDL_CreateWindow("Chipsy - The Best CHIP-8 Emulator!",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED, 
                                         SCREEN_WIDTH, SCREEN_HEIGHT, 
                                         SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!SDL_RenderSetScale(renderer, SCALE, SCALE))
        printf_s("%s\n", SDL_GetError());

    // CHIP-8 Setup:
    CHIP8 chipsy = {};
    init_chip8(&chipsy, FILENAME);

    // Main loop:
    int running = 1;

    SDL_Event event;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        // Emulated CPU Cycles:
        cycle(&chipsy);
        if (chipsy.update_screen)
        { 
            update_screen(renderer, &chipsy);
            chipsy.update_screen = 0;
            SDL_Delay(MONITOR_REFRESH_INTERVAL);
            // SDL_Delay(3000); // For debugging
        }
        printf_s("\n");
        
        // for (int i = 0; i < 10; ++i)
        // {
        //     // printf_s("%d. Value at 0x%x = 0x%x\n", i, START_ADDRESS+i, chipsy.memory[START_ADDRESS+i]);
        //     printf_s("Cycle %d: \n", i+1);
        //     cycle(&chipsy);
        //     if (chipsy.update_screen)
        //     { 
        //         update_screen(renderer, &chipsy);
        //         chipsy.update_screen = 0;
        //         SDL_Delay(MONITOR_REFRESH_INTERVAL);
        //         SDL_Delay(3000);
        //     }
        //     printf_s("\n");
        // }
        
    }


    SDL_Delay(5000);

    // Program Termination:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf_s("Program exited successfully.\n");
    return EXIT_SUCCESS;
}
