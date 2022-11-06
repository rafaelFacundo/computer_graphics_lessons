#include <SDL2/SDL.h>
#include "Sphere.h"
#include "Plan.h"
#include "SdlFunction.h"
#include "scenery.h"
#include "Cylinder.h"
#include "Cone.h"
#include <iostream>
using namespace std;

int main() {
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Event event;
  double wid = 60.0;
  double h = 60.0;
  double n_lines = 500.0;
  double n_collumns = 500.0;
  double dJ = 30.0;
  double z = -dJ;
  double cJan[3] = {0.0,0.0,-dJ};
  double centroEsfera[3] = {0.0,0.0,-100};
  double K_d[3] = {0.7, 0.2, 0.2};

  Vector *ambient_light = new Vector(0.3,0.3,0.3);
  Vector *light_intensity = new Vector(0.7,0.7,0.7);
  Vector *light_position = new Vector(0.0,60.0,-30.0);
  Vector *P_o = new Vector(0.0,0.0,0.0);

  /* initing the sdl window */
  renderer = init_sdl_window (
    n_lines,
    n_collumns,
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

  double color_dChao[3] = {0.2, 0.7, 0.2};
  double color_eChao[3] = {0.2, 0.7, 0.2};
  /* instance of a sphere */
  Plan *thePlane = new Plan();
  thePlane->set_PI_Point(0.0, -40.0, 0.0);
  thePlane->set_N_vector(0.0, 1.0, 0.0);
  thePlane->set_K_d(color_dChao);
  thePlane->set_K_e(color_eChao);
  thePlane->set_K_a(color_dChao);
  thePlane->set_shine(1.0);

  double K_e_plan_backgrnd[3] = {0.3,0.3,0.7};
  double K_d_plan_backgrnd[3] = {0.3,0.3,0.7};

  Plan *backgrnd_plan = new Plan();
  backgrnd_plan->set_PI_Point(0.0,0.0,-200.0);
  backgrnd_plan->set_N_vector(0.0,0.0,1.0);
  backgrnd_plan->set_K_d(K_d_plan_backgrnd);
  backgrnd_plan->set_K_e(K_e_plan_backgrnd);
  backgrnd_plan->set_K_a(K_d_plan_backgrnd);
  backgrnd_plan->set_shine(1.0);

  /* instance of a sphere */
  Sphere *theSphere = new Sphere(
    centroEsfera,
    K_d,
    K_d,
    10.0,
    40.0
  );
  theSphere->set_K_a(K_d);

  double centroEsfera2[3] = {50.0,0.0,-100};
  double K_d2[3] = {0.7, 0.2, 0.2};
  Sphere *theSphere2 = new Sphere(
    centroEsfera2,
    K_d2,
    K_d2,
    10.0,
    40.0
  );
  theSphere2->set_K_a(K_d2);

  double cylinderCoeficients[3] =  {0.2, 0.3, 0.8};
  Cylinder *theCylinder = new Cylinder();
  theCylinder->set_B_vector(0.0,0.0,-100.0);
  theCylinder->set_height(theSphere->get_radius()*3 - 50);
  /* -1/sqrt(3), 1/sqrt(3), -1/sqrt(3) */
  theCylinder->set_unitary_vector(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
  theCylinder->set_K_a(cylinderCoeficients);
  theCylinder->set_K_d(cylinderCoeficients);
  theCylinder->set_K_e(cylinderCoeficients);
  theCylinder->set_shine(5);
  theCylinder->set_radius(40.0/3.0);

  double coeficients_Cone[3] = {0.8, 0.3, 0.2};
  Cone *theCone = new Cone();
  theCone->set_K_a(coeficients_Cone);
  theCone->set_K_d(coeficients_Cone);
  theCone->set_K_e(coeficients_Cone);
  theCone->set_radius(1.5*theSphere->get_radius());
  theCone->set_height(theCone->get_radius()/3);
  theCone->set_direction_vector(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
  /* theCylinder->get_center_top_vector() */
  theCone->set_B_vector(theCylinder->get_center_top_vector());



  /* adding an object to the scenery */
  theScenery->addObjectToTheScene(theSphere);
  theScenery->addObjectToTheScene(thePlane);
  theScenery->addObjectToTheScene(backgrnd_plan);
  //theScenery->addObjectToTheScene(theSphere2);
  theScenery->addObjectToTheScene(theCylinder);
  theScenery->addObjectToTheScene(theCone);



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
