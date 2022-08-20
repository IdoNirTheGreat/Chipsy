# include "chip8.h"
# include "SDL/include/SDL2/SDL.h"
# include <stdio.h>

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define FILENAME ".\\IBM_Logo.ch8"

enum error_code
{
    SDL_FAILED,
    GUI_FAILED,
};

void update_screen(SDL_Renderer* renderer, unsigned char* monitor)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (unsigned int row = 0; row < ROWS; ++row)
    {
        for (unsigned int col = 0; col < COLS; ++col)
        {
            SDL_RenderDrawPoint(renderer, row, col);
        }
    }

    SDL_RenderPresent(renderer);
}

int WinMain(int argc, char* args[])
{
    // SDL Setup:
    /*
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
    fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
    exit(SDL_FAILED);
    }

    window = SDL_CreateWindow(
	 		    "Chipsy - A CHIP-8 Emulator in C!",
	 		    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	 		    SCREEN_WIDTH, SCREEN_HEIGHT,
	 		    SDL_WINDOW_SHOWN
	 		    );

    if (window == NULL)
    {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        exit(GUI_FAILED);
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
    SDL_UpdateWindowSurface(window);
    */
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 1, 1);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderDrawPoint(renderer, 0, 0);

    SDL_RenderPresent(renderer);

    // CHIP-8 Setup:
    CHIP8 chipsy = {};
    init_chip8(&chipsy, FILENAME);

    // Emulated CPU Cycles:
    for (int i = 0; i < 132; ++i)
    {
        // printf_s("Value at 0x%x = 0x%x\n", START_ADDRESS+i, chipsy.memory[START_ADDRESS+i]);
        printf_s("Cycle %d: \n", i+1);
        cycle(&chipsy);
        update_screen(renderer, chipsy.monitor);
        SDL_Delay(500);
        printf_s("\n");
    }

    SDL_Delay(5000);
    // Program Termination:
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf_s("Program exited successfully.\n");
    return EXIT_SUCCESS;
}
