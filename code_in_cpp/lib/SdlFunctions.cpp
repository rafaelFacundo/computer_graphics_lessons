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

void handleMouseEvent(SDL_Window* window, Scenery *scenery, SDL_MouseButtonEvent &event, SDL_Renderer *renderer) {
    int yMouse, xMouse;
    int resposta;
    int numLines;
    int numCol;
    switch (event.button) {
        case SDL_BUTTON_LEFT:
            SDL_GetMouseState(&xMouse, &yMouse);
            break;
    };
    int indexIntercObj = scenery->verifyIfClickHitsSomeObjetc(xMouse, yMouse);
    if (indexIntercObj > -1) {
        cout << "Você deseja alterar o cenário ou o objeto selecionado? \n";
        cout << "1 - alterar objeto.\n";
        cout << "2 - alterar cenário.\n";
        cout << "3 - alterar tamanho da janela.\n";
        cin >> resposta;
        if ( cin.fail() || resposta > 3 || resposta < 1 ) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "entrada inválida.";
        } else if (resposta == 1) {
            scenery->makeModificationOnObject(indexIntercObj);
        }else if (resposta == 2) {
            scenery->modifyScenery();
        }else {
            SDL_DestroyWindow (window);
            SDL_Quit ();
            cout << "Digite o número de linhas: ";
            cin >> numLines;
            if ( cin.fail() || numLines < 1) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "entrada inválida.";
                return;
            }
            cout << "Digite o número de colunas: ";
            cin >> numCol;
            if ( cin.fail() || numCol < 1) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "entrada inválida.";
                return;
            }
            scenery->set_nLines(numLines);
            scenery->set_nCol(numCol);
            renderer = init_sdl_window (
                numLines,
                numCol,
                window,
                renderer
            );
            scenery->set_renderer(renderer);
            scenery->ray_tracing_algorithm();
            SDL_RenderPresent(renderer);

        }

    };
    SDL_UpdateWindowSurface(window);

};

void SDL_events( Scenery *scenery, SDL_Event *event, SDL_Window* window,SDL_Renderer *renderer) {
  int isRunning = 1;
  while (isRunning) {
      while (SDL_PollEvent (event) != 0) {
        switch (event->type) {
            case SDL_QUIT:
                isRunning = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseEvent(window,scenery, event->button, renderer);
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

