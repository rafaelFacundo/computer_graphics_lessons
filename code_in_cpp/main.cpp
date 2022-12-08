#include <SDL2/SDL.h>
#include "./include/Sphere.h"
#include "./include/Plan.h"
#include "./include/SdlFunction.h"
#include "./include/scenery.h"
#include "./include/Cylinder.h"
#include "./include/Cone.h"
#include "./include/Mesh.h"
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

  /*  Fonte pontual: Intensidade da fonte  I_F = (0.7, 0.7, 0.7),
  posição da fonte P_F = (0, 60cm, -30cm)
11) Luz ambiente: Intensidade I_A = (0.3, 0.3, 0.3) */

  Vector *ambient_light = new Vector(0.3,0.3,0.3);
  Vector *light_intensity = new Vector(0.7,0.7,0.7);
  Vector *light_position = new Vector(-100,140.0,-20.0);
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


  /* Plan 1 */
  double K_e_plan_backgrnd[3] = {0.686,0.933,0.933};
  Plan *Floor = new Plan();
  Floor->set_PI_Point(0.0,-150.0,0.0);
  Floor->set_N_vector(0.0,1.0,0.0);
  Floor->set_K_a(K_e_plan_backgrnd);
  Floor->set_K_d(K_e_plan_backgrnd);
  Floor->set_K_e(K_e_plan_backgrnd);
  Floor->set_shine(1);

  /* Plan 2 */
  double K_plan2[3] = {0.686,0.933,0.933};
  Plan *right_side_wall = new Plan();
  right_side_wall->set_PI_Point(200.0, -150.0, 0.0);
  right_side_wall->set_N_vector(-1.0,0.0,0.0);
  right_side_wall->set_K_a(K_plan2);
  right_side_wall->set_K_d(K_plan2);
  right_side_wall->set_K_e(K_plan2);
  right_side_wall->set_shine(1);

  /* Plan 3 */
  double K_plan3[3] = {0.686,0.933,0.933};
  Plan *front_wall = new Plan();
  front_wall->set_PI_Point(200.0,-150.0,-400.0);
  front_wall->set_N_vector(0.0,0.0,1.0);
  front_wall->set_K_a(K_plan3);
  front_wall->set_K_e(K_plan3);
  front_wall->set_K_d(K_plan3);
  front_wall->set_shine(1);

  /* Plan 4 */
  double K_plan4[3] = {0.686,0.933,0.933};
  Plan *left_side_wall = new Plan();
  left_side_wall->set_PI_Point(-200.0,-150.0,0.0);
  left_side_wall->set_N_vector(1.0,0.0,0.0);
  left_side_wall->set_K_a(K_plan4);
  left_side_wall->set_K_d(K_plan4);
  left_side_wall->set_K_e(K_plan4);
  left_side_wall->set_shine(1);

  /* Plan 5 */
  double K_plan5[3] = {0.933,0.933,0.933};
  Plan *ceiling = new Plan();
  ceiling->set_PI_Point(0.0,150.0,0.0);
  ceiling->set_N_vector(0.0,-1.0,0.0);
  ceiling->set_K_a(K_plan5);
  ceiling->set_K_d(K_plan5);
  ceiling->set_K_e(K_plan5);
  ceiling->set_shine(1);

  /* The cylinder */
  double cylinder_ks[3] = {0.824, 0.706, 0.549};
  Cylinder *theCylinder = new Cylinder();
  theCylinder->set_B_vector(0.0,-150.0,-200.0);
  theCylinder->set_height(90);
  theCylinder->set_K_a(cylinder_ks);
  theCylinder->set_K_d(cylinder_ks);
  theCylinder->set_K_e(cylinder_ks);
  theCylinder->set_shine(1);
  theCylinder->set_radius(5);
  theCylinder->set_unitary_vector(0.0,1.0,0.0);

  /* The cone */
  double cone_ks[3] = {0.0,1.0,0.498};
  Cone *theCone = new Cone();
  theCone->set_K_a(cone_ks);
  theCone->set_K_d(cone_ks);
  theCone->set_K_e(cone_ks);
  theCone->set_radius(90);
  theCone->set_height(150);
  theCone->set_direction_vector(0.0,1.0,0.0);
  theCone->set_B_vector(0.0,-60.0,-200.0);
  theCone->set_shine(1);

  /* The sphere */
  double centroEsfera[3] = {0.0,95.0,-200};
  double K_d[3] = {0.845, 0.647, 0.125};
  Sphere *theSphere = new Sphere(
    centroEsfera,
    K_d,
    K_d,
    1.0,
    5.0
  );
  theSphere->set_K_a(K_d);

  /* the cube */

  /* double edgeLeng = 40.0;
  Vector *baseVector = new Vector(0.0, -150.0, -165.0);
  double mesh_ks[3] = {1.0, 0.078, 0.576};
  Mesh *theMesh = new Mesh();
  theMesh->set_K_a(mesh_ks);
  theMesh->set_K_e(mesh_ks);
  theMesh->set_K_d(mesh_ks);
  theMesh->set_shine(5);

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() - (edgeLeng/2),
    baseVector->get_y_Point(),
    baseVector->get_z_Point() - (edgeLeng/2)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() - (edgeLeng/2),
    baseVector->get_y_Point(),
    baseVector->get_z_Point() + (edgeLeng/2)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() + (edgeLeng/2),
    baseVector->get_y_Point(),
    baseVector->get_z_Point() + (edgeLeng/2)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() + (edgeLeng/2),
    baseVector->get_y_Point(),
    baseVector->get_z_Point() - (edgeLeng/2)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() - (edgeLeng/2),
    baseVector->get_y_Point() + edgeLeng,
    baseVector->get_z_Point() - (edgeLeng/2)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() - (edgeLeng/2),
    baseVector->get_y_Point() + edgeLeng,
    baseVector->get_z_Point() + (edgeLeng/2)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() + (edgeLeng/2),
    baseVector->get_y_Point() + edgeLeng,
    baseVector->get_z_Point() + (edgeLeng/2)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() + (edgeLeng/2),
    baseVector->get_y_Point() + edgeLeng,
    baseVector->get_z_Point() - (edgeLeng/2)
  ));


  theMesh->insertAEdge(
    new Edge(0,1)
  );


  theMesh->insertAEdge(
    new Edge(1,2)
  );


  theMesh->insertAEdge(
    new Edge(2,3)
  );


  theMesh->insertAEdge(
    new Edge(3,0)
  );


  theMesh->insertAEdge(
    new Edge(4,5)
  );


  theMesh->insertAEdge(
    new Edge(5,6)
  );


  theMesh->insertAEdge(
    new Edge(6,7)
  );


  theMesh->insertAEdge(
    new Edge(7,4)
  );

  theMesh->insertAEdge(
    new Edge(0,4)
  );


  theMesh->insertAEdge(
    new Edge(1,5)
  );


  theMesh->insertAEdge(
    new Edge(2,6)
  );


  theMesh->insertAEdge(
    new Edge(3,7)
  );


  theMesh->insertAEdge(
    new Edge(2,7)
  );


  theMesh->insertAEdge(
    new Edge(5,7)
  );


  theMesh->insertAEdge(
    new Edge(5,2)
  );

  theMesh->insertAEdge(
    new Edge(1,4)
  );

  theMesh->insertAEdge(
    new Edge(1,3)
  );

  theMesh->insertAEdge(
    new Edge(3,4)
  );



  theMesh->insertAFace(
    new Face(6, 10, 12)
  );

  theMesh->insertAFace(
    new Face(12, 2, 11)
  );

  theMesh->insertAFace(
    new Face(7, 4, 13)
  );

  theMesh->insertAFace(
    new Face(13, 5, 6)
  );

  theMesh->insertAFace(
    new Face(5, 14, 10)
  );

  theMesh->insertAFace(
    new Face(9, 1, 14)
  );

  theMesh->insertAFace(
    new Face(4, 15, 9)
  );

  theMesh->insertAFace(
    new Face(8, 0, 15)
  );

  theMesh->insertAFace(
    new Face(1, 16, 2)
  );

  theMesh->insertAFace(
    new Face(3, 16, 10)
  );

  theMesh->insertAFace(
    new Face(11, 17, 7)
  );

  theMesh->insertAFace(
    new Face(3, 8, 17)
  ); */



  /* adding an object to the scenery */

  //theScenery->addObjectToTheScene(theSphere);
  /* theScenery->addObjectToTheScene(Floor);
  theScenery->addObjectToTheScene(ceiling);
  theScenery->addObjectToTheScene(right_side_wall);
  theScenery->addObjectToTheScene(left_side_wall);
  theScenery->addObjectToTheScene(front_wall);
  theScenery->addObjectToTheScene(theCone);
  theScenery->addObjectToTheScene(theCylinder); */
  //theScenery->addObjectToTheScene(theMesh);
  //theScenery->addObjectToTheScene(theCone);
  //theScenery->addObjectToTheScene(Floor);
  //theScenery->addObjectToTheScene(front_wall);
  //theScenery->addObjectToTheScene(theCylinder);
  
  Vector *P_oArb = new Vector(0,0,0);
  Vector *P_look = new Vector(0.0,-150.0,0.0);
  Vector *P_up = new Vector(15, 10,0);


  theScenery->addObjectToTheScene(Floor);
  Floor->applyConvertWordVectoToCanvas(P_oArb, P_look, P_up);
  


  /* calling the ray tracing algorithm */
  theScenery->ray_tracing_algorithm();



  SDL_events(theScenery, &event, window);






  return 0;
}
