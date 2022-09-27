#include <SDL2/SDL.h>
#include "Sphere.h"
#include "scenery.h"
#include <iostream>
using namespace std;

int main() {
  SDL_Renderer *renderer;
  double c[3] = {0.0,10.0,0.0};
  double ke[3] = {0.0,10.0,0.0};

  double wid = 600.0; 
  double h = 600.0; 
  double n_lines = 600.0; 
  double n_collumns = 600.0; 
  double dJ = 50.0; 

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
  
  Sphere *theSphere = new Sphere();
  theSphere->set_radius(10.0);
  theSphere->set_K_d(K_d);
  


  



  return 0;
} 