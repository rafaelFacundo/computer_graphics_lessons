#pragma once
#include <SDL2/SDL.h>


SDL_Renderer* init_sdl_window (
    int width,
    int height,
    SDL_Window *window,
    SDL_Renderer *renderer
);

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

void show_the_window(SDL_Renderer *renderer);

void SDL_events();