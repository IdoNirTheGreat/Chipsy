# include "chip8.h"
# include "SDL/include/SDL2/SDL.h"
# include <stdio.h>

# define SCALE 10
# define SCREEN_WIDTH 64 * SCALE
# define SCREEN_HEIGHT 32 * SCALE
# define MONITOR_REFRESH_INTERVAL 16 // In miliseconds (about 60 [Hz])
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
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (chip8->monitor[j][i])
            {
                SDL_RenderDrawPoint(renderer, i, j);
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
            // SDL_Delay(3000); // For debugging graphics
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
