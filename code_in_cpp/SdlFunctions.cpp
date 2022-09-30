#include "SdlFunction.h"
#include <iostream>
using namespace std;

SDL_Renderer* init_sdl_window (
    int width,
    int height,
    SDL_Window *window,
    SDL_Renderer *renderer
){
    
    SDL_Init(SDL_INIT_VIDEO); 
    SDL_CreateWindowAndRenderer(width,height, 0, &window, &renderer);
    SDL_RenderClear(renderer);
    return renderer;

};

void set_sdl_draw_color (
    SDL_Renderer *renderer,
    double R,
    double G,
    double B,
    double A
) {
    SDL_SetRenderDrawColor(renderer, R, G, B, A); 
};

void paint_the_point (
    SDL_Renderer *renderer,
    int column,
    int line
){
    SDL_RenderDrawPoint(renderer, column, line);
};

void show_the_window( SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
};

/* void SDL_events() {
    int isRunning = 1; 
    while (isRunning) { 
        while (SDL_PollEvent (&event) != 0) { 
            if(event.type == SDL_QUIT) 
            isRunning = 0; 
        }
    SDL_UpdateWindowSurface (window); 
    } 
    SDL_DestroyWindow (window); 
    SDL_Quit ();
    
}; */