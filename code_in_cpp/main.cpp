#include <SDL2/SDL.h>
#include "Sphere.h"
#include "Plane.h"
#include "SdlFunction.h"
#include "scenery.h"
#include <iostream>
using namespace std;

int main() {
  SDL_Window* window = NULL; 
  SDL_Renderer* renderer = NULL;
  SDL_Event event; 
  double c[3] = {0.0,10.0,0.0};
  double ke[3] = {0.0,10.0,0.0};

  double wid = 600.0; 
  double h = 600.0; 
  double n_lines = 600.0; 
  double n_collumns = 600.0; 
  double dJ = 30.0; 

  double Dx = wid/n_lines; 
  double Dy = h/n_collumns;

  double z = -dJ; 
  double raioDaEsf = 80.0;

  double cJan[3] = {0.0,0.0,-dJ}; 
  double centroEsfera[3] = {0.0,0.0,-90}; 
  
  double Fonte_luminosa[3] = {};
  double L_amb[3] = {0.05, 0.05, 0.05};
  double I_f[3] = {}; 
  double K_d[3] = {255,0.0,0.0}; 
  
  Vector *ambient_light = new Vector(0.05,0.05,0.05);
  Vector *light_intensity = new Vector(0.7,0.7,0.7);
  Vector *light_position = new Vector(0.0,5.0,0.0);
  Vector *P_o = new Vector(0.0,0.0,0.0);

  
  /* initing the sdl window */
  renderer = init_sdl_window (
    wid,
    h,
    window,
    renderer
  );

  

  /* instanciating the scenery class */
  Scenery *theScenery = new Scenery(
    light_position,
    light_intensity,
    ambient_light,
    P_o,
    n_lines,
    n_collumns,
    h,
    wid,
    z,
    renderer
  );
  theScenery->set_Dx_and_Dy(Dx, Dy);

  double color_dChao[3] = {51,178,51};
  double color_eChao[3] = {0,0,0};
  /* instance of a sphere */
  Plane *thePlane = new Plane();
  thePlane->set_PI_Point(0.0, -40.0, 0.0);
  thePlane->set_N_vector(0.0, 1.0, 0.0);
  thePlane->set_K_d(color_dChao);
  thePlane->set_K_e(color_eChao);

  /* instance of a sphere */
  Sphere *theSphere = new Sphere(
    centroEsfera,
    K_d,
    K_d,
    10.0,
    60.0
  );

  /* adding an object to the scenery */
  theScenery->addObjectToTheScene(theSphere);
  theScenery->addObjectToTheScene(thePlane);
  
  

  /* calling the ray tracing algorithm */
  theScenery->ray_tracing_algorithm();

  /* this code below is treating the window's */
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

  
  

  return 0;
} 