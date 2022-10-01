#include "../inc/scene_manager.h"

t_Scene scene_logo(uint32_t *delta, int *size_logo, SDL_Renderer *gRenderer, SDL_Texture **bgTexture)
{
    *size_logo += *delta;

    SDL_FRect imagePos = {(WIDTH_SCREEN - (((*size_logo / 20) + 80) * 2)) / 2.0f, (HEIGHT_SCREEN - ((*size_logo / 20) + 80)) / 2.0f, (((*size_logo / 20) + 80) * 2), ((*size_logo / 20) + 80)};

    SDL_RenderCopyExF(gRenderer, bgTexture[7], NULL, &imagePos, 0, NULL, SDL_FLIP_NONE);

    if ((*size_logo / 20) >= 80)
    {
        return Menu;
    }

    return Logo;
}

t_Scene scene_game(SDL_Renderer *gRenderer, SDL_Event windowEvent, t_layer *layers, t_layer *initial_layers,
                   SDL_Texture *bgTexture, Mix_Music *ambient, bool *is_lose, int *score, int *lifes, uint32_t *delta, float *speed_multiplier)
{
    ambient_music(ambient);

    *speed_multiplier += ((float)(*delta) / 1000000.0);

    if (just_pressed_key(&windowEvent, SDLK_ESCAPE))
    {
        *speed_multiplier = 0;
        *score = 0;
        *lifes = 10;
        *is_lose = false;
        Mix_PauseMusic();
        return Menu;
    }

    if (layers[3].is_interact_layer && !layers[3].is_press)
    {
        if (just_pressed_key(&windowEvent, layers[3].key))
        {
            layers[3].is_press = true;
            (*score) += 5;
        }
    }

    if (is_barrier(&layers[3]) && layers[3].is_press)
    {
        if (just_pressed_any_key(&windowEvent))
        {
            layers[3].is_press = false;
        }
    }

    bool is_scrolled = layers_animation(!(*is_lose), gRenderer, bgTexture, layers, delta, speed_multiplier, initial_layers, 8);

    if (is_scrolled)
    {
        if (is_barrier(&layers[4]))
        {
            if (layers[4].is_press)
            {
                (*score) += 5;
            }
            else
            {
                (*lifes)--;
            }
        }

        if (layers[4].is_interact_layer && !layers[4].is_press)
        {
            (*lifes)--;

            if (*lifes <= 0)
            {
                *is_lose = true;
            }
        }
    }

    char *score_text = mx_itoa(*score);
    char *score_all_text = concat("score: ", score_text);
    char *lifes_text = mx_itoa(*lifes);
    char *lifes_all_text = concat("lifes: ", lifes_text);

    SDL_Color fgC1 = {255, 255, 255, 255};

    SDL_Texture *score_textute = drawText(gRenderer, -(WIDTH_SCREEN / 2.3), -(HEIGHT_SCREEN / 2.2), score_all_text, 15, fgC1);
    SDL_Texture *lifes_texture = drawText(gRenderer, -(WIDTH_SCREEN / 2.3), -(HEIGHT_SCREEN / 2.4), lifes_all_text, 15, fgC1);

    SDL_DestroyTexture(score_textute);
    SDL_DestroyTexture(lifes_texture);
    free(score_text);
    free(score_all_text);
    free(lifes_text);
    free(lifes_all_text);

    return Game;
}

t_Scene scene_menu(SDL_Window *window, SDL_Renderer *gRenderer, SDL_Event windowEvent, SDL_Texture **bgTexture)
{
    Mix_VolumeMusic(25);

    SDL_Color fgC2 = {255, 255, 255, 255};

    SDL_FRect imagePos = {(WIDTH_SCREEN - 600) / 2.0f, ((HEIGHT_SCREEN - 200) / 2.0f) - 160, 600, 200};

    SDL_RenderCopyExF(gRenderer, bgTexture[8], NULL, &imagePos, 0, NULL, SDL_FLIP_NONE);

    if (just_pressed_key(&windowEvent, SDLK_RETURN))
    {
        Mix_PauseMusic();
        return Game;
    }

    if (just_pressed_key(&windowEvent, SDLK_q))
    {
        return End;
    }

    SDL_Texture *m_play = drawText(gRenderer, 0, +(HEIGHT_SCREEN / 14), "Play", 25, fgC2);
    // SDL_Texture *m_sett = drawText(gRenderer, 0, +(HEIGHT_SCREEN / 8), "Settings", 25, fgC2);
    // SDL_Texture *m_cred = drawText(gRenderer, 0, +(HEIGHT_SCREEN / 5.7), "Credits", 25, fgC2);
    SDL_Texture *m_quit = drawText(gRenderer, 0, +(HEIGHT_SCREEN / 8), "Quit", 25, fgC2);

    SDL_DestroyTexture(m_play);
    // SDL_DestroyTexture(m_sett);
    // SDL_DestroyTexture(m_cred);
    SDL_DestroyTexture(m_quit);
    SDL_RenderPresent(gRenderer);

    return Menu;
}
