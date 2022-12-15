#pragma once
#include <SDL2/SDL.h>

void set_sdl_draw_color (
    SDL_Renderer *renderer,
    double R,
    double G,
    double B,
    double A
);

void paint_the_point (
    SDL_Renderer *renderer,
    int column,
    int line
);
