# include "chip8.h"
# include "SDL/include/SDL2/SDL.h"
# include <stdio.h>

# define SCALE 14
# define SCREEN_WIDTH 64 * SCALE
# define SCREEN_HEIGHT 32 * SCALE
# define MONITOR_REFRESH_INTERVAL 16 // In miliseconds (about 60 [Hz])
# define R_VAL 0 // Red display value
# define G_VAL 255 // Green display value
# define B_VAL 0 // Blue display value
# define FILENAME ".\\Games\\PONG"

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

void update_input(SDL_Event* event, CHIP8* chip8)
{
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

    printf_s("Printing key values:\n");
    for(int i = 0; i < KEYS; i++)
    {
        printf_s("Value of key 0x%x = %d\n", i, chip8->active_keys[i]);
    }
}

void update_kbhit(CHIP8* chip8)
{
    printf_s("Printing key values:\n");

    for(int i = 0; i < KEYS; i++)
    {
        printf_s("Value of key 0x%x = %d\n", i, chip8->active_keys[i]);
    }

    unsigned char kbhit = 0;
    for(int i = 0; i < KEYS; i++)
    {
        if(chip8->active_keys[i])
        {
            kbhit = 1;
        }
    }

    chip8->is_kbhit = kbhit;
    printf_s("kbhit value: %d\n", chip8->is_kbhit);
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
            if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = 0;
                }

                else
                {
                    // Process KB input:
                    update_input(&event, &chipsy);
                    //SDL_Delay(7000);
                    update_kbhit(&chipsy);
                    //SDL_Delay(7000);
                }
            }
        }

        // Emulated CPU Cycles:
        cycle(&chipsy);
        if (chipsy.opcode == 0xE0u)
            SDL_Delay(4000);
        if (chipsy.update_screen)
        { 
            update_screen(renderer, &chipsy);
            chipsy.update_screen = 0;
            SDL_Delay(MONITOR_REFRESH_INTERVAL);
        }
        printf_s("\n");
        
    }


    //SDL_Delay(1000);

    // Program Termination:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf_s("Program exited successfully.\n");
    return EXIT_SUCCESS;
}
