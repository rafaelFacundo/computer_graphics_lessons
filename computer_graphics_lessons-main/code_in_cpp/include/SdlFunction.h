#pragma once
#include "./scenery.h"
#include <SDL2/SDL.h>

SDL_Renderer* init_sdl_window (
    int width,
    int height,
    SDL_Window *window,
    SDL_Renderer *renderer
);



void show_the_window(SDL_Renderer *renderer);

void SDL_events( Scenery *scenery, SDL_Event *event, SDL_Window* window);

void handleMouseEvent(SDL_Window* window, Scenery *scenery, SDL_MouseButtonEvent &event);

void updateWindow(SDL_Window * window);
