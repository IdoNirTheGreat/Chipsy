// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #include "SDL/include/SDL2/SDL.h"
// #include "utils.h"

// static const int width = 800;
// static const int height = 600;

// // Draw points with random colors and positions
// void draw_random_points(int nr_points, bool randomizeColor, SDL_Renderer *renderer)
// {
//     for(int i = 0; i < nr_points; ++i)
//     {
//         if(randomizeColor)
//         {
//             SDL_SetRenderDrawColor(renderer, randomColor(), randomColor(), randomColor(), 255);
//         }
//         SDL_RenderDrawPoint(renderer, randomNumber(0, width), randomNumber(0, height));
//     }
// }

// // Draw random lines with random color
// void draw_random_lines(int nr_lines, bool randomizeColor, SDL_Renderer *renderer)
// {
//     for(int i = 0; i < nr_lines; ++i)
//     {
//         if(randomizeColor)
//         {
//             SDL_SetRenderDrawColor(renderer, randomColor(), randomColor(), randomColor(), 255);
//         }
//         SDL_RenderDrawLine(renderer, randomNumber(0, width), randomNumber(0, height), randomNumber(0, width), randomNumber(0, height));
//     }
// }


// int WinMain(int argc, char **argv)
// {
//     // Initialize SDL
//     SDL_Init(SDL_INIT_VIDEO);

//     // Create a SDL window
//     SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

//     // Create a renderer (accelerated and in sync with the display refresh rate)
//     SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     // SDL_RenderSetScale(renderer, 4, 4);

//     bool running = true;
//     SDL_Event event;
//     while(running)
//     {
//         // Process events
//         while(SDL_PollEvent(&event))
//         {
//             if(event.type == SDL_QUIT)
//             {
//                 running = false;
//             }
//         }

//         // Clear screen with black
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);

//         // Draw
//         SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow color
//         draw_random_points(500, true, renderer);
//         draw_random_lines(500, true, renderer);

//         // Draw a rectangle
//         SDL_Rect rect = {30, 100, 200, 200};
//         SDL_RenderFillRect(renderer, &rect);

//         // Draw a wired rectangle
//         SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
//         SDL_Rect rect2 = {250, 300, 200, 250};
//         SDL_RenderDrawRect(renderer, &rect2);


//         // Show what was drawn
//         SDL_RenderPresent(renderer);
//     }

//     // Release resources
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }

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
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (unsigned int row = 0; row < SCREEN_HEIGHT; ++row)
    {
        for (unsigned int col = 0; col < SCREEN_WIDTH; ++col)
        {
            if (monitor[COLS * (col) + row] == 1)
            {
                SDL_RenderDrawPoint(renderer, row, col);
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

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!SDL_RenderSetScale(renderer, SCALE, SCALE)) printf_s("%s\n", SDL_GetError());

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
        for (int i = 0; i < 50; ++i)
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
