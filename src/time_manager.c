#include "../inc/game.h"

void tick(uint32_t *delta, uint32_t *last_tick_time)
{
    uint32_t tick_time = SDL_GetTicks();
    *delta = tick_time - *last_tick_time;
    *last_tick_time = tick_time;
}

