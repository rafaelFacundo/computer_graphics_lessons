#include "../include/SdlFunction.h"
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

void show_the_window( SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
};

void handleMouseEvent(SDL_Window* window, Scenery *scenery, SDL_MouseButtonEvent &event) {
    int yMouse, xMouse;
    switch (event.button) {
        case SDL_BUTTON_LEFT:
            SDL_GetMouseState(&xMouse, &yMouse);
            break;
    };
    int indexIntercObj = scenery->verifyIfClickHitsSomeObjetc(xMouse, yMouse);
    if (indexIntercObj > -1) {
        scenery->makeModificationOnObject(indexIntercObj);
    };
    SDL_UpdateWindowSurface(window);

};

void SDL_events( Scenery *scenery, SDL_Event *event, SDL_Window* window) {
  int isRunning = 1;
  while (isRunning) {
      while (SDL_PollEvent (event) != 0) {
        switch (event->type) {
            case SDL_QUIT:
                isRunning = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseEvent(window,scenery, event->button);
        }
          /* if(event->type == SDL_QUIT)
          isRunning = 0; */
      }
  SDL_UpdateWindowSurface(window);
  }
  SDL_DestroyWindow (window);
  SDL_Quit ();
};

void updateWindow(SDL_Window * window) {
    SDL_UpdateWindowSurface(window);
};

