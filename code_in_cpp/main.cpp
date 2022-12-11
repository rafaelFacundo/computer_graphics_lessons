#include <SDL2/SDL.h>
#include "./include/Sphere.h"
#include "./include/Plan.h"
#include "./include/SdlFunction.h"
#include "./include/scenery.h"
#include "./include/Cylinder.h"
#include "./include/Cone.h"
#include "./include/Mesh.h"
#include "./include/Light.h"
#include "./include/MeshWithTexture.h"
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

  Vector *ambient_light = new Vector(0.9,0.9,0.9);
  Vector *light_intensity = new Vector(0.7,0.7,0.7);
  Vector *light_position = new Vector(0.0,95.0,0);
  Vector *P_o = new Vector(0.0,0.0,0.0);
  Vector *directionLight = new Vector(0,-0.8,-1);

  DirectionalLight* theLight = new DirectionalLight();
  theLight->setIntesity(light_intensity);
  theLight->setDirection(directionLight);
  theLight->setType(2);

  PointLight* pLigh = new PointLight();
  pLigh->setIntesity(light_intensity);
  pLigh->setPostion(directionLight);
  pLigh->setType(0);

  SpotLight* spot = new SpotLight();
  spot->setIntesity(light_intensity);
  spot->setPostion(light_position);
  spot->setDirection(directionLight);
  spot->setAngle(0.5);
  spot->setType(1);

  Light* light_list[1] = {pLigh};

  /* initing the sdl window */
  renderer = init_sdl_window (
    n_lines,
    n_collumns,
    window,
    renderer
  );

  /* instanciating the scenery class */
  Scenery *theScenery = new Scenery(
    light_list,
    1,
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
  Floor->set_TextureImage("./image/asphalt.jpg", true);

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
  double K_plan3[3] = {0.710,0.555,0.321};
  Plan *front_wall = new Plan();
  front_wall->set_PI_Point(200.0,-150.0,-700.0);
  front_wall->set_N_vector(0.0,0.0,1.0);
  front_wall->set_K_a(K_plan3);
  front_wall->set_K_e(K_plan3);
  front_wall->set_K_d(K_plan3);
  front_wall->set_shine(1);
  front_wall->set_TextureImage("./image/back.jpg", false);

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








  // CENÁRIO FINAL

  double trave_ks[3] = {0.9, 0.9, 0.9};
  Cylinder *trave_1_esq = new Cylinder();
  trave_1_esq->set_B_vector(-350.0,-150.0, -484.5);
  trave_1_esq->set_height(73);
  trave_1_esq->set_K_a(trave_ks);
  trave_1_esq->set_K_d(trave_ks);
  trave_1_esq->set_K_e(trave_ks);
  trave_1_esq->set_shine(1);
  trave_1_esq->set_radius(5);
  trave_1_esq->set_unitary_vector(0.0,1.0,0.0);

  Cylinder *trave_1_dir = new Cylinder();
  trave_1_dir->set_B_vector(-350.0,-150.0, -477.5);
  trave_1_dir->set_height(73);
  trave_1_dir->set_K_a(trave_ks);
  trave_1_dir->set_K_d(trave_ks);
  trave_1_dir->set_K_e(trave_ks);
  trave_1_dir->set_shine(1);
  trave_1_dir->set_radius(5);
  trave_1_dir->set_unitary_vector(0.0,1.0,0.0);



  Vector *top = trave_1_dir->get_center_top_vector();
  Vector *top2 = trave_1_esq->get_center_top_vector();
  double travesaoAltura = top->minus_with_the_vector(top2)->getNormOfThisVector();
  Cylinder *trave_1_travessao = new Cylinder();
  trave_1_travessao->set_B_vector(
    top->get_x_Point(),
    top->get_y_Point() - 2.5,
    top->get_z_Point()
  );
  trave_1_travessao->set_height(travesaoAltura);
  trave_1_travessao->set_K_a(trave_ks);
  trave_1_travessao->set_K_d(trave_ks);
  trave_1_travessao->set_K_e(trave_ks);
  trave_1_travessao->set_shine(1);
  trave_1_travessao->set_radius(5);
  trave_1_travessao->set_unitary_vector(0.0,0.0,-1.0);



  Cylinder *trave_2_esq = new Cylinder();
  trave_2_esq->set_B_vector(350.0,-150.0, -477.5);
  trave_2_esq->set_height(73);
  trave_2_esq->set_K_a(trave_ks);
  trave_2_esq->set_K_d(trave_ks);
  trave_2_esq->set_K_e(trave_ks);
  trave_2_esq->set_shine(1);
  trave_2_esq->set_radius(5);
  trave_2_esq->set_unitary_vector(0.0,1.0,0.0);

  Cylinder *trave_2_dir = new Cylinder();
  trave_2_dir->set_B_vector(350.0,-150.0, -484.5);
  trave_2_dir->set_height(73);
  trave_2_dir->set_K_a(trave_ks);
  trave_2_dir->set_K_d(trave_ks);
  trave_2_dir->set_K_e(trave_ks);
  trave_2_dir->set_shine(1);
  trave_2_dir->set_radius(5);
  trave_2_dir->set_unitary_vector(0.0,1.0,0.0);


  top = trave_2_dir->get_center_top_vector();
  top2 = trave_2_esq->get_center_top_vector();
  travesaoAltura = top->minus_with_the_vector(top2)->getNormOfThisVector();

  Cylinder *trave_2_travessao = new Cylinder();
  trave_2_travessao->set_B_vector(
    top->get_x_Point(),
    top->get_y_Point() - 2.5,
    top->get_z_Point()
  );
  trave_2_travessao->set_height(travesaoAltura);
  trave_2_travessao->set_K_a(trave_ks);
  trave_2_travessao->set_K_d(trave_ks);
  trave_2_travessao->set_K_e(trave_ks);
  trave_2_travessao->set_shine(1);
  trave_2_travessao->set_radius(5);
  trave_2_travessao->set_unitary_vector(0.0,0.0,-1.0);

  Vector *iniPoint = new Vector(-350.0,-150.0, -600);
  MeshWithTexture *soccerField = new MeshWithTexture(iniPoint, 700, 245);
  soccerField->set_K_a(K_e_plan_backgrnd);
  soccerField->set_K_d(K_e_plan_backgrnd);
  soccerField->set_K_e(K_e_plan_backgrnd);
  soccerField->set_shine(1);
  soccerField->set_TextureImage("./image/soccerField.jpg", true);

  double centroEsfera[3] = {0.0,-140.0, -477.5};
  double K_d[3] = {0.845, 0.647, 0.125};
  Sphere *theSphere = new Sphere(
    centroEsfera,
    K_d,
    K_d,
    1.0,
    10.0
  );
  theSphere->set_K_a(K_d);



  /*theScenery->addObjectToTheScene(Floor);
   theScenery->addObjectToTheScene(trave_1_esq);
  theScenery->addObjectToTheScene(trave_1_dir);
  theScenery->addObjectToTheScene(trave_1_travessao); */

  //theScenery->addObjectToTheScene(theCylinder);


  double edgeLeng = 40.0;
  Vector *baseVector = new Vector(0.0, -150.0, -300.0);
  double mesh_ks[3] = {1.0, 0.078, 0.576};
  Mesh *theMesh = new Mesh();
  theMesh->set_K_a(mesh_ks);
  theMesh->set_K_e(mesh_ks);
  theMesh->set_K_d(mesh_ks);
  theMesh->set_shine(5);


  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() - (edgeLeng),
    baseVector->get_y_Point(),
    baseVector->get_z_Point() - (edgeLeng)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() - (edgeLeng),
    baseVector->get_y_Point(),
    baseVector->get_z_Point() + (edgeLeng)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() + (edgeLeng),
    baseVector->get_y_Point(),
    baseVector->get_z_Point() + (edgeLeng)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() + (edgeLeng),
    baseVector->get_y_Point(),
    baseVector->get_z_Point() - (edgeLeng)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() - (edgeLeng),
    baseVector->get_y_Point() + edgeLeng,
    baseVector->get_z_Point() - (edgeLeng)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() - (edgeLeng),
    baseVector->get_y_Point() + edgeLeng,
    baseVector->get_z_Point() + (edgeLeng)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() + (edgeLeng),
    baseVector->get_y_Point() + edgeLeng,
    baseVector->get_z_Point() + (edgeLeng)
  ));

  theMesh->insertApoint(new Point(
    baseVector->get_x_Point() + (edgeLeng),
    baseVector->get_y_Point() + edgeLeng,
    baseVector->get_z_Point() - (edgeLeng)
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
  );

  theMesh->addWrapper(
    new Vector(-40,-130,-300),
    80,
    40,
    new Vector(1,0,0)
  );




  Vector *baseVector2 = new Vector(90.0, -150.0, -300.0);
  Mesh *theMesh2 = new Mesh();
  theMesh2->set_K_a(mesh_ks);
  theMesh2->set_K_e(mesh_ks);
  theMesh2->set_K_d(mesh_ks);
  theMesh2->set_shine(5);

  theMesh2->insertApoint(new Point(
    baseVector2->get_x_Point() - (edgeLeng),
    baseVector2->get_y_Point(),
    baseVector2->get_z_Point() - (edgeLeng)
  ));

  theMesh2->insertApoint(new Point(
    baseVector2->get_x_Point() - (edgeLeng),
    baseVector2->get_y_Point(),
    baseVector2->get_z_Point() + (edgeLeng)
  ));

  theMesh2->insertApoint(new Point(
    baseVector2->get_x_Point() + (edgeLeng),
    baseVector2->get_y_Point(),
    baseVector2->get_z_Point() + (edgeLeng)
  ));

  theMesh2->insertApoint(new Point(
    baseVector2->get_x_Point() + (edgeLeng),
    baseVector2->get_y_Point(),
    baseVector2->get_z_Point() - (edgeLeng)
  ));

  theMesh2->insertApoint(new Point(
    baseVector2->get_x_Point() - (edgeLeng),
    baseVector2->get_y_Point() + edgeLeng,
    baseVector2->get_z_Point() - (edgeLeng)
  ));

  theMesh2->insertApoint(new Point(
    baseVector2->get_x_Point() - (edgeLeng),
    baseVector2->get_y_Point() + edgeLeng,
    baseVector2->get_z_Point() + (edgeLeng)
  ));

  theMesh2->insertApoint(new Point(
    baseVector2->get_x_Point() + (edgeLeng),
    baseVector2->get_y_Point() + edgeLeng,
    baseVector2->get_z_Point() + (edgeLeng)
  ));

  theMesh2->insertApoint(new Point(
    baseVector2->get_x_Point() + (edgeLeng),
    baseVector2->get_y_Point() + edgeLeng,
    baseVector2->get_z_Point() - (edgeLeng)
  ));


  theMesh2->insertAEdge(
    new Edge(0,1)
  );


  theMesh2->insertAEdge(
    new Edge(1,2)
  );


  theMesh2->insertAEdge(
    new Edge(2,3)
  );


  theMesh2->insertAEdge(
    new Edge(3,0)
  );


  theMesh2->insertAEdge(
    new Edge(4,5)
  );


  theMesh2->insertAEdge(
    new Edge(5,6)
  );


  theMesh2->insertAEdge(
    new Edge(6,7)
  );


  theMesh2->insertAEdge(
    new Edge(7,4)
  );

  theMesh2->insertAEdge(
    new Edge(0,4)
  );


  theMesh2->insertAEdge(
    new Edge(1,5)
  );


  theMesh2->insertAEdge(
    new Edge(2,6)
  );


  theMesh2->insertAEdge(
    new Edge(3,7)
  );


  theMesh2->insertAEdge(
    new Edge(2,7)
  );


  theMesh2->insertAEdge(
    new Edge(5,7)
  );


  theMesh2->insertAEdge(
    new Edge(5,2)
  );

  theMesh2->insertAEdge(
    new Edge(1,4)
  );

  theMesh2->insertAEdge(
    new Edge(1,3)
  );

  theMesh2->insertAEdge(
    new Edge(3,4)
  );



  theMesh2->insertAFace(
    new Face(6, 10, 12)
  );

  theMesh2->insertAFace(
    new Face(12, 2, 11)
  );

  theMesh2->insertAFace(
    new Face(7, 4, 13)
  );

  theMesh2->insertAFace(
    new Face(13, 5, 6)
  );

  theMesh2->insertAFace(
    new Face(5, 14, 10)
  );

  theMesh2->insertAFace(
    new Face(9, 1, 14)
  );

  theMesh2->insertAFace(
    new Face(4, 15, 9)
  );

  theMesh2->insertAFace(
    new Face(8, 0, 15)
  );

  theMesh2->insertAFace(
    new Face(1, 16, 2)
  );

  theMesh2->insertAFace(
    new Face(3, 16, 10)
  );

  theMesh2->insertAFace(
    new Face(11, 17, 7)
  );

  theMesh2->insertAFace(
    new Face(3, 8, 17)
  );

  theMesh2->addWrapper(
    new Vector(90,-130,-300),
    80,
    60,
    new Vector(1,0,0)
  );




  Vector *P_oArb = new Vector(0,0,0);
  Vector *P_look = new Vector(0.0,-150.0,0.0);
  Vector *P_up = new Vector(15, 10,0);


  /* theScenery->addObjectToTheScene(soccerField);
  theScenery->addObjectToTheScene(trave_1_esq);
  theScenery->addObjectToTheScene(trave_1_dir);
  theScenery->addObjectToTheScene(trave_1_travessao);
  theScenery->addObjectToTheScene(trave_2_dir);
  theScenery->addObjectToTheScene(trave_2_esq);
  theScenery->addObjectToTheScene(trave_2_travessao);
  theScenery->addObjectToTheScene(Floor);
  theScenery->addObjectToTheScene(front_wall);
  theScenery->addObjectToTheScene(theSphere); */


  //theScenery->addObjectToTheScene(theMesh);
  theScenery->addObjectToTheScene(theMesh);

  /* calling the ray tracing algorithm */
  theScenery->ray_tracing_algorithm();



  SDL_events(theScenery, &event, window);






  return 0;
}
