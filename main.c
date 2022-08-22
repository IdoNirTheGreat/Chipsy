# include "chip8.h"
# include "SDL/include/SDL2/SDL.h"
# include <stdio.h>

# define SCALE 10
# define SCREEN_WIDTH 64 * SCALE
# define SCREEN_HEIGHT 32 * SCALE
# define MONITOR_REFRESH_INTERVAL 100 // In miliseconds
# define FILENAME ".\\IBM_Logo.ch8"

enum error_code
{
    SDL_FAILED,
    GUI_FAILED,
};

void update_screen(SDL_Renderer* renderer, unsigned char* monitor)
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

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    int row = 0;
    int col = 0;
    int sum = 0;
    printf_s("Actually drawn pixels: ");
    for (int i = 0; i < (ROWS * COLS); i++)
    {
        col++;
        if (!(i % COLS))
        {
            row++;  
            col = 0;         
        }

        if (monitor[i])
        {
            SDL_RenderDrawPoint(renderer, col, row);
            printf_s("[%d, %d], ", col, row);
            sum++;
        }
    }
    printf_s("]\nTotal = %d\n", sum);
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
        for (int i = 0; i < 10; ++i)
        {
            // printf_s("%d. Value at 0x%x = 0x%x\n", i, START_ADDRESS+i, chipsy.memory[START_ADDRESS+i]);
            printf_s("Cycle %d: \n", i+1);
            cycle(&chipsy);
            if (chipsy.update_screen)
            { 
                update_screen(renderer, chipsy.monitor);
                chipsy.update_screen = 0;
                SDL_Delay(MONITOR_REFRESH_INTERVAL);
                SDL_Delay(3000);
            }
            printf_s("\n");
        }
        
    }


    SDL_Delay(5000);

    // Program Termination:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf_s("Program exited successfully.\n");
    return EXIT_SUCCESS;
}
