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

int WinMain(int argc, char* args[])
{
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
    
    CHIP8 chipsy = {};
    init_chip8(&chipsy, FILENAME);
    for (int i = 0; i < 50; ++i)
    {
        printf_s("Cycle %d: \n", i+1);
        cycle(&chipsy);
        printf_s("\n");
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 255, 0));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf_s("Program exited successfully.\n");
    exit(EXIT_SUCCESS);
}
