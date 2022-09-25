# include <stdio.h>
# include "chip8.h"
# include "SDL/include/SDL2/SDL.h"

# define SCALE 14
# define SCREEN_WIDTH 64 * SCALE
# define SCREEN_HEIGHT 32 * SCALE
# define MONITOR_REFRESH_INTERVAL 16u // 60 [Hz]
# define R_VAL 0 // Red display value
# define G_VAL 255 // Green display value
# define B_VAL 0 // Blue display value
# define A_VAL 255 // Alpha value
# define DEFAULT_FILENAME ".\\Games\\Intro_logo.ch8"

enum error_code
{
    SDL_FAILED,
    GUI_FAILED,
};

unsigned int update_screen(SDL_Renderer* renderer, CHIP8* chip8)
{   /* 
     * Draws each pixel by using the SDL library.
     */
    unsigned int delay = SDL_GetTicks();

    // Draw "on" pixels:
    SDL_SetRenderDrawColor(renderer, R_VAL, G_VAL, B_VAL, A_VAL);
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

    // Draw "off" pixels:
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (!chip8->monitor[j][i])
            {                
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }

    SDL_RenderPresent(renderer);
    return delay;
}

void update_input(SDL_Event* event, CHIP8* chip8)
{   /*
     * Updates each key's flag to represent if it's pressed 
     * down, in the CHIP-8 struct.
     */
    // Press Key Event:
    if(event->type == SDL_KEYDOWN)
    {
        switch(event->key.keysym.sym)
        {    
            case SDLK_1:
            {
                chip8->active_keys[1] = 1;
                break;
            }

            case SDLK_2:
            {
                chip8->active_keys[2] = 1;
                break;
            }

            case SDLK_3:
            {
                chip8->active_keys[3] = 1;
                break;
            }

            case SDLK_4:
            {
                chip8->active_keys[0xC] = 1;
                break;
            }

            case SDLK_q:
            {
                chip8->active_keys[4] = 1;
                break;
            }

            case SDLK_w:
            {
                chip8->active_keys[5] = 1;
                break;
            }

            case SDLK_e:
            {
                chip8->active_keys[6] = 1;
                break;
            }

            case SDLK_r:
            {
                chip8->active_keys[0xD] = 1;
                break;
            }

            case SDLK_a:
            {
                chip8->active_keys[7] = 1;
                break;
            }

            case SDLK_s:
            {
                chip8->active_keys[8] = 1;
                break;
            }

            case SDLK_d:
            {
                chip8->active_keys[9] = 1;
                break;
            }

            case SDLK_f:
            {
                chip8->active_keys[0xE] = 1;
                break;
            }

            case SDLK_z:
            {
                chip8->active_keys[0xA] = 1;
                break;
            }

            case SDLK_x:
            {
                chip8->active_keys[0] = 1;
                break;
            }

            case SDLK_c:
            {
                chip8->active_keys[0xB] = 1;
                break;
            }

            case SDLK_v:
            {
                chip8->active_keys[0xF] = 1;
                break;
            }

            default:
            {
                break;
            }
        }     
    }

    // Release Key Event:
    if(event->type == SDL_KEYUP)
    {
        switch(event->key.keysym.sym)
        {
            case SDLK_1:
            {
                chip8->active_keys[1] = 0;
                break;
            }

            case SDLK_2:
            {
                chip8->active_keys[2] = 0;
                break;
            }

            case SDLK_3:
            {
                chip8->active_keys[3] = 0;
                break;
            }

            case SDLK_4:
            {
                chip8->active_keys[0xC] = 0;
                break;
            }

            case SDLK_q:
            {
                chip8->active_keys[4] = 0;
                break;
            }

            case SDLK_w:
            {
                chip8->active_keys[5] = 0;
                break;
            }

            case SDLK_e:
            {
                chip8->active_keys[6] = 0;
                break;
            }

            case SDLK_r:
            {
                chip8->active_keys[0xD] = 0;
                break;
            }

            case SDLK_a:
            {
                chip8->active_keys[7] = 0;
                break;
            }

            case SDLK_s:
            {
                chip8->active_keys[8] = 0;
                break;
            }

            case SDLK_d:
            {
                chip8->active_keys[9] = 0;
                break;
            }

            case SDLK_f:
            {
                chip8->active_keys[0xE] = 0;
                break;
            }

            case SDLK_z:
            {
                chip8->active_keys[0xA] = 0;
                break;
            }

            case SDLK_x:
            {
                chip8->active_keys[0] = 0;
                break;
            }

            case SDLK_c:
            {
                chip8->active_keys[0xB] = 0;
                break;
            }

            case SDLK_v:
            {
                chip8->active_keys[0xF] = 0;
                break;
            }

            default:
            {
                break;
            }
        }     
    }
}

void update_kbhit(CHIP8* chip8)
{   /*
     * Updates the kbhit flag in the CHIP-8 struct.
     */
    unsigned char kbhit = 0;
    for(int i = 0; i < KEYS; i++)
    {
        if(chip8->active_keys[i])
        {
            kbhit = 1;
        }
    }

    chip8->is_kbhit = kbhit;
}

int main(int argc, char* argv[])
{   /*
     * The program's main function. What it does by order is:
     * 1. Creates SDL structs.
     * 2. Creates the CHIP-8 struct instance.
     * 3. Plays intro.
     * 4. Runs selected ROM in a main loop.
     */
    // SDL Setup:
    SDL_Window* window = SDL_CreateWindow(
                        "Chipsy - The Best CHIP-8 Emulator!",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED, 
                        SCREEN_WIDTH, SCREEN_HEIGHT, 
                        SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(
                            window,
                            -1,
                            SDL_RENDERER_ACCELERATED |
                            SDL_RENDERER_PRESENTVSYNC);

    if(!SDL_RenderSetScale(renderer, SCALE, SCALE))
        printf_s("%s\n", SDL_GetError());

    // CHIP-8 Setup:
    CHIP8 chipsy = {};
    if (argc > 1) init_chip8(&chipsy, argv[1]);
    else init_chip8(&chipsy, DEFAULT_FILENAME);

    // Main loop:
    int running = 1;
    SDL_Event event;
    while(running)
    {
        // Process Key Events:
        while(SDL_PollEvent(&event))
        {
            if  (event.type == SDL_KEYDOWN || 
                event.type == SDL_KEYUP)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = 0;
                }

                else
                {
                    // Process KB input:
                    update_input(&event, &chipsy);
                    update_kbhit(&chipsy);
                }
            }
        }

        // Emulated CPU Cycles:
        cycle(&chipsy);
        if (chipsy.update_screen)
        { 
            unsigned int delay = update_screen(
                                                renderer,
                                                &chipsy);
            chipsy.update_screen = 0;
            if (MONITOR_REFRESH_INTERVAL > delay)
            {
                SDL_Delay(MONITOR_REFRESH_INTERVAL- delay);
            } 
        }
    }

    // Program Termination:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf_s("Program exited successfully.\n");
    return EXIT_SUCCESS;
}
