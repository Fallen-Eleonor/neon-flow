#include "../inc/scene_manager.h"

int main(void)
{
    srand(time(NULL));

    t_Scene current_scene = Logo;

    SDL_Event windowEvent;
    SDL_Surface *screen_surface = NULL;
    SDL_Window *window = window_init(WIDTH_SCREEN, HEIGHT_SCREEN, screen_surface);
    SDL_Renderer *gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *bgTexture[9];
    bgTexture[0] = loadTexture("./resource/textures/Quadrate.png", gRenderer);
    bgTexture[1] = loadTexture("./resource/textures/Triangle.png", gRenderer);
    bgTexture[2] = loadTexture("./resource/textures/Barrier.png", gRenderer);
    bgTexture[3] = loadTexture("./resource/textures/Bad.png", gRenderer);
    bgTexture[4] = loadTexture("./resource/textures/Good.png", gRenderer);
    bgTexture[5] = loadTexture("./resource/textures/Underline.png", gRenderer);
    bgTexture[6] = loadTexture("./resource/textures/Round.png", gRenderer);
    bgTexture[7] = loadTexture("./resource/textures/LogoHD.png", gRenderer);
    bgTexture[8] = loadTexture("./resource/textures/GameLogo.png", gRenderer);

    init_music();
    init_text();

    Mix_Music *ambient = Mix_LoadMUS("./resource/music/Ambient.wav");

    t_layer *initial_layers = initial_init_layers(bgTexture);
    t_layer *layers = init_layers(initial_layers, 8);

    uint32_t last_tick_time = 0;
    uint32_t delta = 0;

    int size_logo = 100;

    float speed_multiplier = 0;

    int score = 0;
    int lifes = 10;

    bool is_lose = false;

    while (true)
    {
        SDL_RenderClear(gRenderer);

        tick(&delta, &last_tick_time);

        if (finish_program(&windowEvent) || current_scene == End)
        {
            break;
        }

        switch (current_scene)
        {
        case Game:
            current_scene = scene_game(gRenderer, windowEvent, layers, initial_layers, bgTexture, ambient, &is_lose, &score, &lifes, &delta, &speed_multiplier);
            break;
        case Logo:
            current_scene = scene_logo(&delta, &size_logo, gRenderer, bgTexture);
            break;
        case Menu:
            current_scene = scene_menu(window, gRenderer, windowEvent, bgTexture);
            break;
        }

        SDL_RenderPresent(gRenderer);
    }

    free(initial_layers);
    free(layers);

    Mix_FreeMusic(ambient);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
