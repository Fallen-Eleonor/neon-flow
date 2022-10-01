#ifndef MENU
#define MENU

#include "../inc/game.h"
#include "../inc/graphic.h"
#include "../inc/text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef enum e_Scene
{
    Logo,
    Menu,
    Settings,
    Game,
    Music,
    End
} t_Scene;

t_Scene scene_logo(uint32_t *delta, int *size_logo, SDL_Renderer *gRenderer, SDL_Texture **bgTexture);
t_Scene scene_game(SDL_Renderer *gRenderer, SDL_Event windowEvent, t_layer *layers, t_layer *initial_layers,
                   SDL_Texture *bgTexture, Mix_Music *ambient, bool *is_lose, int *score, int *lifes, uint32_t *delta, float *speed_multiplier);
t_Scene scene_menu(SDL_Window *window, SDL_Renderer *gRenderer, SDL_Event windowEvent, SDL_Texture **bgTexture);

#endif
