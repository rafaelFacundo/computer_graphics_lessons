#include "SdlFunction.h"

void init_sdl_window (
    int width,
    int height,
    SDL_Window *window,
    SDL_Renderer *renderer
){
    SDL_Init(SDL_INIT_VIDEO); 
    SDL_CreateWindowAndRenderer(width,height, 0, &window, &renderer);
    SDL_RenderClear(renderer);
};

void set_sdl_draw_color (
    SDL_Renderer *renderer,
    float R,
    float G,
    float B,
    float A
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