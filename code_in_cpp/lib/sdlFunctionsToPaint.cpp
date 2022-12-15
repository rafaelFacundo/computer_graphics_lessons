#include "../include/sdlFunctionsToPaint.h"


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


