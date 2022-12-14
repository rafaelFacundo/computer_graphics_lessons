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

  Vector *ambient_light = new Vector(0.3,0.3,0.3);
  Vector *light_intensity = new Vector(0.7,0.7,0.7);
  Vector *light_position = new Vector(0.0,95.0,0);
  Vector *P_o = new Vector(0.0,0.0,0.0);
  Vector *directionLight = new Vector(0,-0.5,-1);

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

  Light* light_list[1] = {theLight};

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
  double K_e_plan_backgrnd[3] = {0.501,0.501,0.501};
  Plan *Floor = new Plan();
  Floor->set_PI_Point(0.0,-150.0,0.0);
  Floor->set_N_vector(0.0,1.0,0.0);
  Floor->set_K_a(K_e_plan_backgrnd);
  Floor->set_K_d(K_e_plan_backgrnd);
  Floor->set_K_e(K_e_plan_backgrnd);
  Floor->set_shine(1);
  //Floor->set_TextureImage("./image/asphalt.jpg", true);

  /* Plan 3 */
  double K_plan3[3] = {0,0.498,1};
  Plan *front_wall = new Plan();
  front_wall->set_PI_Point(200.0,-150.0,-700.0);
  front_wall->set_N_vector(0.0,0.0,1.0);
  front_wall->set_K_a(K_plan3);
  front_wall->set_K_e(K_plan3);
  front_wall->set_K_d(K_plan3);
  front_wall->set_shine(1);
  //front_wall->set_TextureImage("./image/back.jpg", false);



  /* The sphere */








  // CENÁRIO FINAL


  double trave_ks[3] = {0.9, 0.9, 0.9};
  double height_trave = 45;
  Cylinder *trave_1_esq = new Cylinder();
  trave_1_esq->set_B_vector(-350.0,-150.0, -484.5);
  trave_1_esq->set_height(height_trave);
  trave_1_esq->set_K_a(trave_ks);
  trave_1_esq->set_K_d(trave_ks);
  trave_1_esq->set_K_e(trave_ks);
  trave_1_esq->set_shine(1);
  trave_1_esq->set_radius(5);
  trave_1_esq->set_unitary_vector(0.0,1.0,0.0);

  Cylinder *trave_1_dir = new Cylinder();
  trave_1_dir->set_B_vector(-350.0,-150.0, -477.5);
  trave_1_dir->set_height(height_trave);
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
  trave_2_esq->set_height(height_trave);
  trave_2_esq->set_K_a(trave_ks);
  trave_2_esq->set_K_d(trave_ks);
  trave_2_esq->set_K_e(trave_ks);
  trave_2_esq->set_shine(1);
  trave_2_esq->set_radius(5);
  trave_2_esq->set_unitary_vector(0.0,1.0,0.0);

  Cylinder *trave_2_dir = new Cylinder();
  trave_2_dir->set_B_vector(350.0,-150.0, -484.5);
  trave_2_dir->set_height(height_trave);
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
  double widthSoccerField = 700;
  double heightSoccerField = 245;
  MeshWithTexture *soccerField = new MeshWithTexture(iniPoint, widthSoccerField, heightSoccerField);
  soccerField->set_K_a(K_e_plan_backgrnd);
  soccerField->set_K_d(K_e_plan_backgrnd);
  soccerField->set_K_e(K_e_plan_backgrnd);
  soccerField->set_shine(1);
  soccerField->set_TextureImage("./image/soccerField.jpg", true);
  soccerField->addWrapper(
    new Vector(-350, -150, -477.5),
    700,
    122.5,
    new Vector(1,0,0)
  );

  double centroEsfera[3] = {0.0,-140.0, -477.5};
  double K_d[3] = {0.845, 0.647, 0.125};
  Sphere *theSphere = new Sphere(
    centroEsfera,
    K_d,
    K_d,
    1.0,
    50.0
  );
  theSphere->set_K_a(K_d);


  //Vector *iniPoint = new Vector(-350.0,-150.0, -600);
  //MeshWithTexture *soccerField = new MeshWithTexture(iniPoint, 700, 245);

  double comp_aresta_cubos = 50.0;
  double cubos_ks[3] = {0.9, 0.9, 0.9};

  Vector *base_cubo_1_esq = new Vector((iniPoint->get_x_Point()-(comp_aresta_cubos/2)),(iniPoint->get_y_Point()), (iniPoint->get_z_Point()-(comp_aresta_cubos/2)));
  Mesh *cubo_1_esq = new Mesh();
  cubo_1_esq->set_K_a(cubos_ks);
  cubo_1_esq->set_K_e(cubos_ks);
  cubo_1_esq->set_K_d(cubos_ks);
  cubo_1_esq->set_shine(5);

  Vector *base_cubo_1_dir = new Vector((iniPoint->get_x_Point()+widthSoccerField+(comp_aresta_cubos/2)),(iniPoint->get_y_Point()), (iniPoint->get_z_Point()-(comp_aresta_cubos/2)));
  Mesh *cubo_1_dir = new Mesh();
  cubo_1_dir->set_K_a(cubos_ks);
  cubo_1_dir->set_K_e(cubos_ks);
  cubo_1_dir->set_K_d(cubos_ks);
  cubo_1_dir->set_shine(5);

  Vector *base_cubo_2_esq = new Vector((iniPoint->get_x_Point()-(comp_aresta_cubos/2)),(iniPoint->get_y_Point()), (iniPoint->get_z_Point()+heightSoccerField+(comp_aresta_cubos/2)));
  Mesh *cubo_2_esq = new Mesh();
  cubo_2_esq->set_K_a(cubos_ks);
  cubo_2_esq->set_K_e(cubos_ks);
  cubo_2_esq->set_K_d(cubos_ks);
  cubo_2_esq->set_shine(5);

  Vector *base_cubo_2_dir = new Vector((iniPoint->get_x_Point()+widthSoccerField+(comp_aresta_cubos/2)),(iniPoint->get_y_Point()), (iniPoint->get_z_Point()+heightSoccerField+(comp_aresta_cubos/2)));
  Mesh *cubo_2_dir = new Mesh();
  cubo_2_dir->set_K_a(cubos_ks);
  cubo_2_dir->set_K_e(cubos_ks);
  cubo_2_dir->set_K_d(cubos_ks);
  cubo_2_dir->set_shine(5);

  Vector *iniPointRoofBack = new Vector(iniPoint->get_x_Point(),(iniPoint->get_y_Point()+comp_aresta_cubos), (iniPoint->get_z_Point()-comp_aresta_cubos));
  MeshWithTexture *roofBack = new MeshWithTexture(iniPointRoofBack, widthSoccerField, comp_aresta_cubos);
  roofBack->set_K_a(cubos_ks);
  roofBack->set_K_d(cubos_ks);
  roofBack->set_K_e(cubos_ks);
  roofBack->set_shine(1);
  roofBack->addWrapper(
    new Vector(-350,-100,-625),
    700,
    25,
    new Vector(1,0,0)
  );
  roofBack->set_TextureImage("./image/telhado.jpg", true);

  Vector *iniPointRoofFront = new Vector(iniPoint->get_x_Point(),(iniPoint->get_y_Point()+comp_aresta_cubos), (iniPoint->get_z_Point()+heightSoccerField));
  MeshWithTexture *roofFront = new MeshWithTexture(iniPointRoofFront, widthSoccerField, comp_aresta_cubos);
  roofFront->set_K_a(cubos_ks);
  roofFront->set_K_d(cubos_ks);
  roofFront->set_K_e(cubos_ks);
  roofFront->set_shine(1);
  roofFront->addWrapper(
    new Vector(-350,-100,-330),
    700,
    25,
    new Vector(1,0,0)
  );

  roofFront->set_TextureImage("./image/telhado.jpg", true);

  Vector *iniPointRoofLeft = new Vector((iniPoint->get_x_Point()-comp_aresta_cubos),(iniPoint->get_y_Point()+comp_aresta_cubos), iniPoint->get_z_Point());
  MeshWithTexture *roofLeft = new MeshWithTexture(iniPointRoofLeft, comp_aresta_cubos, widthSoccerField);
  roofLeft->set_K_a(cubos_ks);
  roofLeft->set_K_d(cubos_ks);
  roofLeft->set_K_e(cubos_ks);
  roofLeft->set_shine(1);
  roofLeft->addWrapper(
    new Vector(-375,-100,-355),
    245,
    25,
    new Vector(0,0,-1)
  );
  roofLeft->set_TextureImage("./image/telhado.jpg", true);

  Vector *iniPointRoofRight = new Vector((iniPoint->get_x_Point()+widthSoccerField),(iniPoint->get_y_Point()+comp_aresta_cubos), iniPoint->get_z_Point());
  MeshWithTexture *roofRight = new MeshWithTexture(iniPointRoofRight, comp_aresta_cubos, widthSoccerField);
  roofRight->set_K_a(cubos_ks);
  roofRight->set_K_d(cubos_ks);
  roofRight->set_K_e(cubos_ks);
  roofRight->set_shine(1);
  roofRight->addWrapper(
    new Vector(375,-100,-355),
    245,
    25,
    new Vector(0,0,-1)
  );
  roofRight->set_TextureImage("./image/telhado.jpg", true);

  cubo_1_esq->insertApoint(new Point(
    base_cubo_1_esq->get_x_Point() - (comp_aresta_cubos),
    base_cubo_1_esq->get_y_Point(),
    base_cubo_1_esq->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_1_esq->insertApoint(new Point(
    base_cubo_1_esq->get_x_Point() - (comp_aresta_cubos),
    base_cubo_1_esq->get_y_Point(),
    base_cubo_1_esq->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_1_esq->insertApoint(new Point(
    base_cubo_1_esq->get_x_Point() + (comp_aresta_cubos),
    base_cubo_1_esq->get_y_Point(),
    base_cubo_1_esq->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_1_esq->insertApoint(new Point(
    base_cubo_1_esq->get_x_Point() + (comp_aresta_cubos),
    base_cubo_1_esq->get_y_Point(),
    base_cubo_1_esq->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_1_esq->insertApoint(new Point(
    base_cubo_1_esq->get_x_Point() - (comp_aresta_cubos),
    base_cubo_1_esq->get_y_Point() + comp_aresta_cubos,
    base_cubo_1_esq->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_1_esq->insertApoint(new Point(
    base_cubo_1_esq->get_x_Point() - (comp_aresta_cubos),
    base_cubo_1_esq->get_y_Point() + comp_aresta_cubos,
    base_cubo_1_esq->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_1_esq->insertApoint(new Point(
    base_cubo_1_esq->get_x_Point() + (comp_aresta_cubos),
    base_cubo_1_esq->get_y_Point() + comp_aresta_cubos,
    base_cubo_1_esq->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_1_esq->insertApoint(new Point(
    base_cubo_1_esq->get_x_Point() + (comp_aresta_cubos),
    base_cubo_1_esq->get_y_Point() + comp_aresta_cubos,
    base_cubo_1_esq->get_z_Point() - (comp_aresta_cubos)
  ));


  cubo_1_dir->insertApoint(new Point(
    base_cubo_1_dir->get_x_Point() - (comp_aresta_cubos),
    base_cubo_1_dir->get_y_Point(),
    base_cubo_1_dir->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_1_dir->insertApoint(new Point(
    base_cubo_1_dir->get_x_Point() - (comp_aresta_cubos),
    base_cubo_1_dir->get_y_Point(),
    base_cubo_1_dir->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_1_dir->insertApoint(new Point(
    base_cubo_1_dir->get_x_Point() + (comp_aresta_cubos),
    base_cubo_1_dir->get_y_Point(),
    base_cubo_1_dir->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_1_dir->insertApoint(new Point(
    base_cubo_1_dir->get_x_Point() + (comp_aresta_cubos),
    base_cubo_1_dir->get_y_Point(),
    base_cubo_1_dir->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_1_dir->insertApoint(new Point(
    base_cubo_1_dir->get_x_Point() - (comp_aresta_cubos),
    base_cubo_1_dir->get_y_Point() + comp_aresta_cubos,
    base_cubo_1_dir->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_1_dir->insertApoint(new Point(
    base_cubo_1_dir->get_x_Point() - (comp_aresta_cubos),
    base_cubo_1_dir->get_y_Point() + comp_aresta_cubos,
    base_cubo_1_dir->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_1_dir->insertApoint(new Point(
    base_cubo_1_dir->get_x_Point() + (comp_aresta_cubos),
    base_cubo_1_dir->get_y_Point() + comp_aresta_cubos,
    base_cubo_1_dir->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_1_dir->insertApoint(new Point(
    base_cubo_1_dir->get_x_Point() + (comp_aresta_cubos),
    base_cubo_1_dir->get_y_Point() + comp_aresta_cubos,
    base_cubo_1_dir->get_z_Point() - (comp_aresta_cubos)
  ));


  cubo_2_esq->insertApoint(new Point(
    base_cubo_2_esq->get_x_Point() - (comp_aresta_cubos),
    base_cubo_2_esq->get_y_Point(),
    base_cubo_2_esq->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_2_esq->insertApoint(new Point(
    base_cubo_2_esq->get_x_Point() - (comp_aresta_cubos),
    base_cubo_2_esq->get_y_Point(),
    base_cubo_2_esq->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_2_esq->insertApoint(new Point(
    base_cubo_2_esq->get_x_Point() + (comp_aresta_cubos),
    base_cubo_2_esq->get_y_Point(),
    base_cubo_2_esq->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_2_esq->insertApoint(new Point(
    base_cubo_2_esq->get_x_Point() + (comp_aresta_cubos),
    base_cubo_2_esq->get_y_Point(),
    base_cubo_2_esq->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_2_esq->insertApoint(new Point(
    base_cubo_2_esq->get_x_Point() - (comp_aresta_cubos),
    base_cubo_2_esq->get_y_Point() + comp_aresta_cubos,
    base_cubo_2_esq->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_2_esq->insertApoint(new Point(
    base_cubo_2_esq->get_x_Point() - (comp_aresta_cubos),
    base_cubo_2_esq->get_y_Point() + comp_aresta_cubos,
    base_cubo_2_esq->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_2_esq->insertApoint(new Point(
    base_cubo_2_esq->get_x_Point() + (comp_aresta_cubos),
    base_cubo_2_esq->get_y_Point() + comp_aresta_cubos,
    base_cubo_2_esq->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_2_esq->insertApoint(new Point(
    base_cubo_2_esq->get_x_Point() + (comp_aresta_cubos),
    base_cubo_2_esq->get_y_Point() + comp_aresta_cubos,
    base_cubo_2_esq->get_z_Point() - (comp_aresta_cubos)
  ));


  cubo_2_dir->insertApoint(new Point(
    base_cubo_2_dir->get_x_Point() - (comp_aresta_cubos),
    base_cubo_2_dir->get_y_Point(),
    base_cubo_2_dir->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_2_dir->insertApoint(new Point(
    base_cubo_2_dir->get_x_Point() - (comp_aresta_cubos),
    base_cubo_2_dir->get_y_Point(),
    base_cubo_2_dir->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_2_dir->insertApoint(new Point(
    base_cubo_2_dir->get_x_Point() + (comp_aresta_cubos),
    base_cubo_2_dir->get_y_Point(),
    base_cubo_2_dir->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_2_dir->insertApoint(new Point(
    base_cubo_2_dir->get_x_Point() + (comp_aresta_cubos),
    base_cubo_2_dir->get_y_Point(),
    base_cubo_2_dir->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_2_dir->insertApoint(new Point(
    base_cubo_2_dir->get_x_Point() - (comp_aresta_cubos),
    base_cubo_2_dir->get_y_Point() + comp_aresta_cubos,
    base_cubo_2_dir->get_z_Point() - (comp_aresta_cubos)
  ));

  cubo_2_dir->insertApoint(new Point(
    base_cubo_2_dir->get_x_Point() - (comp_aresta_cubos),
    base_cubo_2_dir->get_y_Point() + comp_aresta_cubos,
    base_cubo_2_dir->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_2_dir->insertApoint(new Point(
    base_cubo_2_dir->get_x_Point() + (comp_aresta_cubos),
    base_cubo_2_dir->get_y_Point() + comp_aresta_cubos,
    base_cubo_2_dir->get_z_Point() + (comp_aresta_cubos)
  ));

  cubo_2_dir->insertApoint(new Point(
    base_cubo_2_dir->get_x_Point() + (comp_aresta_cubos),
    base_cubo_2_dir->get_y_Point() + comp_aresta_cubos,
    base_cubo_2_dir->get_z_Point() - (comp_aresta_cubos)
  ));


  cubo_1_esq->insertAEdge(
    new Edge(0,1)
  );

  cubo_1_esq->insertAEdge(
    new Edge(1,2)
  );

  cubo_1_esq->insertAEdge(
    new Edge(2,3)
  );

  cubo_1_esq->insertAEdge(
    new Edge(3,0)
  );

  cubo_1_esq->insertAEdge(
    new Edge(4,5)
  );

  cubo_1_esq->insertAEdge(
    new Edge(5,6)
  );

  cubo_1_esq->insertAEdge(
    new Edge(6,7)
  );

  cubo_1_esq->insertAEdge(
    new Edge(7,4)
  );

  cubo_1_esq->insertAEdge(
    new Edge(0,4)
  );

  cubo_1_esq->insertAEdge(
    new Edge(1,5)
  );

  cubo_1_esq->insertAEdge(
    new Edge(2,6)
  );

  cubo_1_esq->insertAEdge(
    new Edge(3,7)
  );

  cubo_1_esq->insertAEdge(
    new Edge(2,7)
  );

  cubo_1_esq->insertAEdge(
    new Edge(5,7)
  );

  cubo_1_esq->insertAEdge(
    new Edge(5,2)
  );

  cubo_1_esq->insertAEdge(
    new Edge(1,4)
  );

  cubo_1_esq->insertAEdge(
    new Edge(1,3)
  );

  cubo_1_esq->insertAEdge(
    new Edge(3,4)
  );


  cubo_1_dir->insertAEdge(
    new Edge(0,1)
  );

  cubo_1_dir->insertAEdge(
    new Edge(1,2)
  );

  cubo_1_dir->insertAEdge(
    new Edge(2,3)
  );

  cubo_1_dir->insertAEdge(
    new Edge(3,0)
  );

  cubo_1_dir->insertAEdge(
    new Edge(4,5)
  );

  cubo_1_dir->insertAEdge(
    new Edge(5,6)
  );

  cubo_1_dir->insertAEdge(
    new Edge(6,7)
  );

  cubo_1_dir->insertAEdge(
    new Edge(7,4)
  );

  cubo_1_dir->insertAEdge(
    new Edge(0,4)
  );

  cubo_1_dir->insertAEdge(
    new Edge(1,5)
  );

  cubo_1_dir->insertAEdge(
    new Edge(2,6)
  );

  cubo_1_dir->insertAEdge(
    new Edge(3,7)
  );

  cubo_1_dir->insertAEdge(
    new Edge(2,7)
  );

  cubo_1_dir->insertAEdge(
    new Edge(5,7)
  );

  cubo_1_dir->insertAEdge(
    new Edge(5,2)
  );

  cubo_1_dir->insertAEdge(
    new Edge(1,4)
  );

  cubo_1_dir->insertAEdge(
    new Edge(1,3)
  );

  cubo_1_dir->insertAEdge(
    new Edge(3,4)
  );


  cubo_2_esq->insertAEdge(
    new Edge(0,1)
  );

  cubo_2_esq->insertAEdge(
    new Edge(1,2)
  );

  cubo_2_esq->insertAEdge(
    new Edge(2,3)
  );

  cubo_2_esq->insertAEdge(
    new Edge(3,0)
  );

  cubo_2_esq->insertAEdge(
    new Edge(4,5)
  );

  cubo_2_esq->insertAEdge(
    new Edge(5,6)
  );

  cubo_2_esq->insertAEdge(
    new Edge(6,7)
  );

  cubo_2_esq->insertAEdge(
    new Edge(7,4)
  );

  cubo_2_esq->insertAEdge(
    new Edge(0,4)
  );

  cubo_2_esq->insertAEdge(
    new Edge(1,5)
  );

  cubo_2_esq->insertAEdge(
    new Edge(2,6)
  );

  cubo_2_esq->insertAEdge(
    new Edge(3,7)
  );

  cubo_2_esq->insertAEdge(
    new Edge(2,7)
  );

  cubo_2_esq->insertAEdge(
    new Edge(5,7)
  );

  cubo_2_esq->insertAEdge(
    new Edge(5,2)
  );

  cubo_2_esq->insertAEdge(
    new Edge(1,4)
  );

  cubo_2_esq->insertAEdge(
    new Edge(1,3)
  );

  cubo_2_esq->insertAEdge(
    new Edge(3,4)
  );


  cubo_2_dir->insertAEdge(
    new Edge(0,1)
  );

  cubo_2_dir->insertAEdge(
    new Edge(1,2)
  );

  cubo_2_dir->insertAEdge(
    new Edge(2,3)
  );

  cubo_2_dir->insertAEdge(
    new Edge(3,0)
  );

  cubo_2_dir->insertAEdge(
    new Edge(4,5)
  );

  cubo_2_dir->insertAEdge(
    new Edge(5,6)
  );

  cubo_2_dir->insertAEdge(
    new Edge(6,7)
  );

  cubo_2_dir->insertAEdge(
    new Edge(7,4)
  );

  cubo_2_dir->insertAEdge(
    new Edge(0,4)
  );

  cubo_2_dir->insertAEdge(
    new Edge(1,5)
  );

  cubo_2_dir->insertAEdge(
    new Edge(2,6)
  );

  cubo_2_dir->insertAEdge(
    new Edge(3,7)
  );

  cubo_2_dir->insertAEdge(
    new Edge(2,7)
  );

  cubo_2_dir->insertAEdge(
    new Edge(5,7)
  );

  cubo_2_dir->insertAEdge(
    new Edge(5,2)
  );

  cubo_2_dir->insertAEdge(
    new Edge(1,4)
  );

  cubo_2_dir->insertAEdge(
    new Edge(1,3)
  );

  cubo_2_dir->insertAEdge(
    new Edge(3,4)
  );


  cubo_1_esq->insertAFace(
    new Face(6, 10, 12)
  );

  cubo_1_esq->insertAFace(
    new Face(12, 2, 11)
  );

  cubo_1_esq->insertAFace(
    new Face(7, 4, 13)
  );

  cubo_1_esq->insertAFace(
    new Face(13, 5, 6)
  );

  cubo_1_esq->insertAFace(
    new Face(5, 14, 10)
  );

  cubo_1_esq->insertAFace(
    new Face(9, 1, 14)
  );

  cubo_1_esq->insertAFace(
    new Face(4, 15, 9)
  );

  cubo_1_esq->insertAFace(
    new Face(8, 0, 15)
  );

  cubo_1_esq->insertAFace(
    new Face(1, 16, 2)
  );

  cubo_1_esq->insertAFace(
    new Face(3, 16, 10)
  );

  cubo_1_esq->insertAFace(
    new Face(11, 17, 7)
  );

  cubo_1_esq->insertAFace(
    new Face(3, 8, 17)
  );


  cubo_1_dir->insertAFace(
    new Face(6, 10, 12)
  );

  cubo_1_dir->insertAFace(
    new Face(12, 2, 11)
  );

  cubo_1_dir->insertAFace(
    new Face(7, 4, 13)
  );

  cubo_1_dir->insertAFace(
    new Face(13, 5, 6)
  );

  cubo_1_dir->insertAFace(
    new Face(5, 14, 10)
  );

  cubo_1_dir->insertAFace(
    new Face(9, 1, 14)
  );

  cubo_1_dir->insertAFace(
    new Face(4, 15, 9)
  );

  cubo_1_dir->insertAFace(
    new Face(8, 0, 15)
  );

  cubo_1_dir->insertAFace(
    new Face(1, 16, 2)
  );

  cubo_1_dir->insertAFace(
    new Face(3, 16, 10)
  );

  cubo_1_dir->insertAFace(
    new Face(11, 17, 7)
  );

  cubo_1_dir->insertAFace(
    new Face(3, 8, 17)
  );


  cubo_2_esq->insertAFace(
    new Face(6, 10, 12)
  );

  cubo_2_esq->insertAFace(
    new Face(12, 2, 11)
  );

  cubo_2_esq->insertAFace(
    new Face(7, 4, 13)
  );

  cubo_2_esq->insertAFace(
    new Face(13, 5, 6)
  );

  cubo_2_esq->insertAFace(
    new Face(5, 14, 10)
  );

  cubo_2_esq->insertAFace(
    new Face(9, 1, 14)
  );

  cubo_2_esq->insertAFace(
    new Face(4, 15, 9)
  );

  cubo_2_esq->insertAFace(
    new Face(8, 0, 15)
  );

  cubo_2_esq->insertAFace(
    new Face(1, 16, 2)
  );

  cubo_2_esq->insertAFace(
    new Face(3, 16, 10)
  );

  cubo_2_esq->insertAFace(
    new Face(11, 17, 7)
  );

  cubo_2_esq->insertAFace(
    new Face(3, 8, 17)
  );


  cubo_2_dir->insertAFace(
    new Face(6, 10, 12)
  );

  cubo_2_dir->insertAFace(
    new Face(12, 2, 11)
  );

  cubo_2_dir->insertAFace(
    new Face(7, 4, 13)
  );

  cubo_2_dir->insertAFace(
    new Face(13, 5, 6)
  );

  cubo_2_dir->insertAFace(
    new Face(5, 14, 10)
  );

  cubo_2_dir->insertAFace(
    new Face(9, 1, 14)
  );

  cubo_2_dir->insertAFace(
    new Face(4, 15, 9)
  );

  cubo_2_dir->insertAFace(
    new Face(8, 0, 15)
  );

  cubo_2_dir->insertAFace(
    new Face(1, 16, 2)
  );

  cubo_2_dir->insertAFace(
    new Face(3, 16, 10)
  );

  cubo_2_dir->insertAFace(
    new Face(11, 17, 7)
  );

  cubo_2_dir->insertAFace(
    new Face(3, 8, 17)
  );


  cubo_1_esq->addWrapper(
    base_cubo_1_esq,
    50,
    25,
    new Vector(0,1,0)
  );

  cubo_1_dir->addWrapper(
    base_cubo_1_dir,
    50,
    25,
    new Vector(0,1,0)
  );

  cubo_2_esq->addWrapper(
    base_cubo_2_esq,
    50,
    25,
    new Vector(0,1,0)
  );

  cubo_2_dir->addWrapper(
    base_cubo_2_dir,
    50,
    25,
    new Vector(0,1,0)
  );


  double mesh_ks[3] = {0.845, 0.647, 0.125};
  Vector *baseVector2 = new Vector(-350.0,-150.0, -650);
  Mesh *frontStands = new Mesh();
  frontStands->set_K_a(mesh_ks);
  frontStands->set_K_e(mesh_ks);
  frontStands->set_K_d(mesh_ks);
  frontStands->set_shine(5);

  frontStands->insertApoint(new Point(-350,-150,-650));
  frontStands->insertApoint(new Point(-350,-150,-600));
  frontStands->insertApoint(new Point(350,-150,-600));
  frontStands->insertApoint(new Point(350,-150,-650));

  frontStands->insertApoint(new Point(-350,-100,-650));
  frontStands->insertApoint(new Point(-350,-100,-640));
  frontStands->insertApoint(new Point(-350,-110,-640));
  frontStands->insertApoint(new Point(-350,-110,-630));
  frontStands->insertApoint(new Point(-350,-120,-630));
  frontStands->insertApoint(new Point(-350,-120,-620));
  frontStands->insertApoint(new Point(-350,-130,-620));
  frontStands->insertApoint(new Point(-350,-130,-610));
  frontStands->insertApoint(new Point(-350,-140,-610));
  frontStands->insertApoint(new Point(-350,-140,-600));

  frontStands->insertApoint(new Point(350, -140, -600));
  frontStands->insertApoint(new Point(350, -140, -610));
  frontStands->insertApoint(new Point(350, -130, -610));
  frontStands->insertApoint(new Point(350, -130, -620));
  frontStands->insertApoint(new Point(350, -120, -620));
  frontStands->insertApoint(new Point(350, -120, -630));
  frontStands->insertApoint(new Point(350, -110, -630));
  frontStands->insertApoint(new Point(350, -110, -640));
  frontStands->insertApoint(new Point(350, -100, -640));
  frontStands->insertApoint(new Point(350, -100, -650));

  frontStands->insertAEdge(new Edge(4,0));
  frontStands->insertAEdge(new Edge(0,3));
  frontStands->insertAEdge(new Edge(3,23));
  frontStands->insertAEdge(new Edge(23,4));
  frontStands->insertAEdge(new Edge(4,5));
  frontStands->insertAEdge(new Edge(5,22));
  frontStands->insertAEdge(new Edge(22,23));
  frontStands->insertAEdge(new Edge(6,7));
  frontStands->insertAEdge(new Edge(7,20));
  frontStands->insertAEdge(new Edge(20,21));
  frontStands->insertAEdge(new Edge(21,6));
  frontStands->insertAEdge(new Edge(8,9));
  frontStands->insertAEdge(new Edge(9,18));
  frontStands->insertAEdge(new Edge(18,19));
  frontStands->insertAEdge(new Edge(19,8));
  frontStands->insertAEdge(new Edge(10,11));
  frontStands->insertAEdge(new Edge(11,16));
  frontStands->insertAEdge(new Edge(16,17));
  frontStands->insertAEdge(new Edge(17,10));
  frontStands->insertAEdge(new Edge(12,13));
  frontStands->insertAEdge(new Edge(13,14));
  frontStands->insertAEdge(new Edge(14,15));
  frontStands->insertAEdge(new Edge(15,12));
  frontStands->insertAEdge(new Edge(1,2));

  frontStands->insertAEdge(new Edge(5,6));
  frontStands->insertAEdge(new Edge(22,21));
  frontStands->insertAEdge(new Edge(7,8));
  frontStands->insertAEdge(new Edge(20,19));
  frontStands->insertAEdge(new Edge(9,10));
  frontStands->insertAEdge(new Edge(18,17));
  frontStands->insertAEdge(new Edge(11,12));
  frontStands->insertAEdge(new Edge(16,15));
  frontStands->insertAEdge(new Edge(13,1));
  frontStands->insertAEdge(new Edge(14,2));

  frontStands->insertAEdge(new Edge(3,4));
  frontStands->insertAEdge(new Edge(4,22));
  frontStands->insertAEdge(new Edge(6,22));
  frontStands->insertAEdge(new Edge(6,20));
  frontStands->insertAEdge(new Edge(8,20));
  frontStands->insertAEdge(new Edge(8,18));
  frontStands->insertAEdge(new Edge(10,18));
  frontStands->insertAEdge(new Edge(10,16));
  frontStands->insertAEdge(new Edge(12,16));
  frontStands->insertAEdge(new Edge(12,14));
  frontStands->insertAEdge(new Edge(1,14));


  frontStands->insertAFace(new Face(0,1,34));
  frontStands->insertAFace(new Face(3,34,2));
  frontStands->insertAFace(new Face(6,3,35));
  frontStands->insertAFace(new Face(4,5,35));
  frontStands->insertAFace(new Face(25,36,10));
  frontStands->insertAFace(new Face(5,24,36));
  frontStands->insertAFace(new Face(9,10,37));
  frontStands->insertAFace(new Face(7,8,37));
  frontStands->insertAFace(new Face(27,38,14));
  frontStands->insertAFace(new Face(8,26,38));
  frontStands->insertAFace(new Face(13,14,39));
  frontStands->insertAFace(new Face(11,12,39));
  frontStands->insertAFace(new Face(12,28,40));
  frontStands->insertAFace(new Face(29,40,18));
  frontStands->insertAFace(new Face(17,18,41));
  frontStands->insertAFace(new Face(41,15,16));
  frontStands->insertAFace(new Face(31,42,22));
  frontStands->insertAFace(new Face(16,30,42));
  frontStands->insertAFace(new Face(21,22,43));
  frontStands->insertAFace(new Face(19,20,43));
  frontStands->insertAFace(new Face(23,33,44));
  frontStands->insertAFace(new Face(20,32,44));

  frontStands->addWrapper(
    new Vector(-350,-125,-600),
    710,
    30,
    new Vector(1,0,0)
  );


  Mesh *leftSideStands = new Mesh();
  leftSideStands->set_K_a(mesh_ks);
  leftSideStands->set_K_e(mesh_ks);
  leftSideStands->set_K_d(mesh_ks);
  leftSideStands->set_shine(5);

  leftSideStands->insertApoint(new Point(-400,-150,-355));
  leftSideStands->insertApoint(new Point(-350,-150,-355));
  leftSideStands->insertApoint(new Point(-350,-150,-600));
  leftSideStands->insertApoint(new Point(-400,-150,-655));

  leftSideStands->insertApoint(new Point(-400,-100,-355));
  leftSideStands->insertApoint(new Point(-390,-100,-355));
  leftSideStands->insertApoint(new Point(-390,-110,-355));
  leftSideStands->insertApoint(new Point(-380,-110,-355));
  leftSideStands->insertApoint(new Point(-380,-120,-355));
  leftSideStands->insertApoint(new Point(-370,-120,-355));
  leftSideStands->insertApoint(new Point(-370,-130,-355));
  leftSideStands->insertApoint(new Point(-360,-130,-355));
  leftSideStands->insertApoint(new Point(-360,-140,-355));
  leftSideStands->insertApoint(new Point(-350,-140,-355));

  leftSideStands->insertApoint(new Point(-350,-140,-600));
  leftSideStands->insertApoint(new Point(-360,-140,-600));
  leftSideStands->insertApoint(new Point(-360,-130,-600));
  leftSideStands->insertApoint(new Point(-370,-130,-600));
  leftSideStands->insertApoint(new Point(-370,-120,-600));
  leftSideStands->insertApoint(new Point(-380,-120,-600));
  leftSideStands->insertApoint(new Point(-380,-110,-600));
  leftSideStands->insertApoint(new Point(-390,-110,-600));
  leftSideStands->insertApoint(new Point(-390,-100,-600));
  leftSideStands->insertApoint(new Point(-400,-100,-600));

  leftSideStands->insertAEdge(new Edge(4,0));
  leftSideStands->insertAEdge(new Edge(0,3));
  leftSideStands->insertAEdge(new Edge(3,23));
  leftSideStands->insertAEdge(new Edge(23,4));
  leftSideStands->insertAEdge(new Edge(4,5));
  leftSideStands->insertAEdge(new Edge(5,22));
  leftSideStands->insertAEdge(new Edge(22,23));
  leftSideStands->insertAEdge(new Edge(6,7));
  leftSideStands->insertAEdge(new Edge(7,20));
  leftSideStands->insertAEdge(new Edge(20,21));
  leftSideStands->insertAEdge(new Edge(21,6));
  leftSideStands->insertAEdge(new Edge(8,9));
  leftSideStands->insertAEdge(new Edge(9,18));
  leftSideStands->insertAEdge(new Edge(18,19));
  leftSideStands->insertAEdge(new Edge(19,8));
  leftSideStands->insertAEdge(new Edge(10,11));
  leftSideStands->insertAEdge(new Edge(11,16));
  leftSideStands->insertAEdge(new Edge(16,17));
  leftSideStands->insertAEdge(new Edge(17,10));
  leftSideStands->insertAEdge(new Edge(12,13));
  leftSideStands->insertAEdge(new Edge(13,14));
  leftSideStands->insertAEdge(new Edge(14,15));
  leftSideStands->insertAEdge(new Edge(15,12));
  leftSideStands->insertAEdge(new Edge(1,2));

  leftSideStands->insertAEdge(new Edge(5,6));
  leftSideStands->insertAEdge(new Edge(22,21));
  leftSideStands->insertAEdge(new Edge(7,8));
  leftSideStands->insertAEdge(new Edge(20,19));
  leftSideStands->insertAEdge(new Edge(9,10));
  leftSideStands->insertAEdge(new Edge(18,17));
  leftSideStands->insertAEdge(new Edge(11,12));
  leftSideStands->insertAEdge(new Edge(16,15));
  leftSideStands->insertAEdge(new Edge(13,1));
  leftSideStands->insertAEdge(new Edge(14,2));

  leftSideStands->insertAEdge(new Edge(3,4));
  leftSideStands->insertAEdge(new Edge(4,22));
  leftSideStands->insertAEdge(new Edge(6,22));
  leftSideStands->insertAEdge(new Edge(6,20));
  leftSideStands->insertAEdge(new Edge(8,20));
  leftSideStands->insertAEdge(new Edge(8,18));
  leftSideStands->insertAEdge(new Edge(10,18));
  leftSideStands->insertAEdge(new Edge(10,16));
  leftSideStands->insertAEdge(new Edge(12,16));
  leftSideStands->insertAEdge(new Edge(12,14));
  leftSideStands->insertAEdge(new Edge(1,14));


  leftSideStands->insertAFace(new Face(0,1,34));
  leftSideStands->insertAFace(new Face(3,34,2));
  leftSideStands->insertAFace(new Face(6,3,35));
  leftSideStands->insertAFace(new Face(4,5,35));
  leftSideStands->insertAFace(new Face(25,36,10));
  leftSideStands->insertAFace(new Face(5,24,36));
  leftSideStands->insertAFace(new Face(9,10,37));
  leftSideStands->insertAFace(new Face(7,8,37));
  leftSideStands->insertAFace(new Face(27,38,14));
  leftSideStands->insertAFace(new Face(8,26,38));
  leftSideStands->insertAFace(new Face(13,14,39));
  leftSideStands->insertAFace(new Face(11,12,39));
  leftSideStands->insertAFace(new Face(12,28,40));
  leftSideStands->insertAFace(new Face(29,40,18));
  leftSideStands->insertAFace(new Face(17,18,41));
  leftSideStands->insertAFace(new Face(41,15,16));
  leftSideStands->insertAFace(new Face(31,42,22));
  leftSideStands->insertAFace(new Face(16,30,42));
  leftSideStands->insertAFace(new Face(21,22,43));
  leftSideStands->insertAFace(new Face(19,20,43));
  leftSideStands->insertAFace(new Face(23,33,44));
  leftSideStands->insertAFace(new Face(20,32,44));

  leftSideStands->addWrapper(
    new Vector(-375,-125,-350),
    250,
    30,
    new Vector(0,0,-1)
  );

  Mesh *rightSideStands = new Mesh();
  rightSideStands->set_K_a(mesh_ks);
  rightSideStands->set_K_e(mesh_ks);
  rightSideStands->set_K_d(mesh_ks);
  rightSideStands->set_shine(5);

  rightSideStands->insertApoint(new Point(400,-150,-600));
  rightSideStands->insertApoint(new Point(350,-150,-600));
  rightSideStands->insertApoint(new Point(350,-150,-355));
  rightSideStands->insertApoint(new Point(400,-150,-355));


  rightSideStands->insertApoint(new Point(400,-100,-600));
  rightSideStands->insertApoint(new Point(390,-100,-600));
  rightSideStands->insertApoint(new Point(390,-110,-600));
  rightSideStands->insertApoint(new Point(380,-110,-600));
  rightSideStands->insertApoint(new Point(380,-120,-600));
  rightSideStands->insertApoint(new Point(370,-120,-600));
  rightSideStands->insertApoint(new Point(370,-130,-600));
  rightSideStands->insertApoint(new Point(360,-130,-600));
  rightSideStands->insertApoint(new Point(360,-140,-600));
  rightSideStands->insertApoint(new Point(350,-140,-600));

  rightSideStands->insertApoint(new Point(350,-140,-355));
  rightSideStands->insertApoint(new Point(360,-140,-355));
  rightSideStands->insertApoint(new Point(360,-130,-355));
  rightSideStands->insertApoint(new Point(370,-130,-355));
  rightSideStands->insertApoint(new Point(370,-120,-355));
  rightSideStands->insertApoint(new Point(380,-120,-355));
  rightSideStands->insertApoint(new Point(380,-110,-355));
  rightSideStands->insertApoint(new Point(390,-110,-355));
  rightSideStands->insertApoint(new Point(390,-100,-355));
  rightSideStands->insertApoint(new Point(400,-100,-355));

  rightSideStands->insertAEdge(new Edge(4,0));
  rightSideStands->insertAEdge(new Edge(0,3));
  rightSideStands->insertAEdge(new Edge(3,23));
  rightSideStands->insertAEdge(new Edge(23,4));
  rightSideStands->insertAEdge(new Edge(4,5));
  rightSideStands->insertAEdge(new Edge(5,22));
  rightSideStands->insertAEdge(new Edge(22,23));
  rightSideStands->insertAEdge(new Edge(6,7));
  rightSideStands->insertAEdge(new Edge(7,20));
  rightSideStands->insertAEdge(new Edge(20,21));
  rightSideStands->insertAEdge(new Edge(21,6));
  rightSideStands->insertAEdge(new Edge(8,9));
  rightSideStands->insertAEdge(new Edge(9,18));
  rightSideStands->insertAEdge(new Edge(18,19));
  rightSideStands->insertAEdge(new Edge(19,8));
  rightSideStands->insertAEdge(new Edge(10,11));
  rightSideStands->insertAEdge(new Edge(11,16));
  rightSideStands->insertAEdge(new Edge(16,17));
  rightSideStands->insertAEdge(new Edge(17,10));
  rightSideStands->insertAEdge(new Edge(12,13));
  rightSideStands->insertAEdge(new Edge(13,14));
  rightSideStands->insertAEdge(new Edge(14,15));
  rightSideStands->insertAEdge(new Edge(15,12));
  rightSideStands->insertAEdge(new Edge(1,2));

  rightSideStands->insertAEdge(new Edge(5,6));
  rightSideStands->insertAEdge(new Edge(22,21));
  rightSideStands->insertAEdge(new Edge(7,8));
  rightSideStands->insertAEdge(new Edge(20,19));
  rightSideStands->insertAEdge(new Edge(9,10));
  rightSideStands->insertAEdge(new Edge(18,17));
  rightSideStands->insertAEdge(new Edge(11,12));
  rightSideStands->insertAEdge(new Edge(16,15));
  rightSideStands->insertAEdge(new Edge(13,1));
  rightSideStands->insertAEdge(new Edge(14,2));

  rightSideStands->insertAEdge(new Edge(3,4));
  rightSideStands->insertAEdge(new Edge(4,22));
  rightSideStands->insertAEdge(new Edge(6,22));
  rightSideStands->insertAEdge(new Edge(6,20));
  rightSideStands->insertAEdge(new Edge(8,20));
  rightSideStands->insertAEdge(new Edge(8,18));
  rightSideStands->insertAEdge(new Edge(10,18));
  rightSideStands->insertAEdge(new Edge(10,16));
  rightSideStands->insertAEdge(new Edge(12,16));
  rightSideStands->insertAEdge(new Edge(12,14));
  rightSideStands->insertAEdge(new Edge(1,14));


  rightSideStands->insertAFace(new Face(0,1,34));
  rightSideStands->insertAFace(new Face(3,34,2));
  rightSideStands->insertAFace(new Face(6,3,35));
  rightSideStands->insertAFace(new Face(4,5,35));
  rightSideStands->insertAFace(new Face(25,36,10));
  rightSideStands->insertAFace(new Face(5,24,36));
  rightSideStands->insertAFace(new Face(9,10,37));
  rightSideStands->insertAFace(new Face(7,8,37));
  rightSideStands->insertAFace(new Face(27,38,14));
  rightSideStands->insertAFace(new Face(8,26,38));
  rightSideStands->insertAFace(new Face(13,14,39));
  rightSideStands->insertAFace(new Face(11,12,39));
  rightSideStands->insertAFace(new Face(12,28,40));
  rightSideStands->insertAFace(new Face(29,40,18));
  rightSideStands->insertAFace(new Face(17,18,41));
  rightSideStands->insertAFace(new Face(41,15,16));
  rightSideStands->insertAFace(new Face(31,42,22));
  rightSideStands->insertAFace(new Face(16,30,42));
  rightSideStands->insertAFace(new Face(21,22,43));
  rightSideStands->insertAFace(new Face(19,20,43));
  rightSideStands->insertAFace(new Face(23,33,44));
  rightSideStands->insertAFace(new Face(20,32,44));

  rightSideStands->addWrapper(
    new Vector(375,-125,-350),
    250,
    30,
    new Vector(0,0,-1)
  );


  Mesh *backStands = new Mesh();
  backStands->set_K_a(mesh_ks);
  backStands->set_K_e(mesh_ks);
  backStands->set_K_d(mesh_ks);
  backStands->set_shine(5);

  backStands->insertApoint(new Point(350,-150,-305));
  backStands->insertApoint(new Point(350,-150,-355));
  backStands->insertApoint(new Point(-350,-150,-355));
  backStands->insertApoint(new Point(-350,-150,-305));

  backStands->insertApoint(new Point(350,-100,-305));
  backStands->insertApoint(new Point(350,-100,-315));
  backStands->insertApoint(new Point(350,-110,-315));
  backStands->insertApoint(new Point(350,-110,-325));
  backStands->insertApoint(new Point(350,-120,-325));
  backStands->insertApoint(new Point(350,-120,-335));
  backStands->insertApoint(new Point(350,-130,-335));
  backStands->insertApoint(new Point(350,-130,-345));
  backStands->insertApoint(new Point(350,-140,-345));
  backStands->insertApoint(new Point(350,-140,-355));

  backStands->insertApoint(new Point(-350, -140, -355));
  backStands->insertApoint(new Point(-350, -140, -345));
  backStands->insertApoint(new Point(-350, -130, -345));
  backStands->insertApoint(new Point(-350, -130, -335));
  backStands->insertApoint(new Point(-350, -120, -335));
  backStands->insertApoint(new Point(-350, -120, -325));
  backStands->insertApoint(new Point(-350, -110, -325));
  backStands->insertApoint(new Point(-350, -110, -315));
  backStands->insertApoint(new Point(-350, -100, -315));
  backStands->insertApoint(new Point(-350, -100, -305));

  backStands->insertAEdge(new Edge(4,0));
  backStands->insertAEdge(new Edge(0,3));
  backStands->insertAEdge(new Edge(3,23));
  backStands->insertAEdge(new Edge(23,4));
  backStands->insertAEdge(new Edge(4,5));
  backStands->insertAEdge(new Edge(5,22));
  backStands->insertAEdge(new Edge(22,23));
  backStands->insertAEdge(new Edge(6,7));
  backStands->insertAEdge(new Edge(7,20));
  backStands->insertAEdge(new Edge(20,21));
  backStands->insertAEdge(new Edge(21,6));
  backStands->insertAEdge(new Edge(8,9));
  backStands->insertAEdge(new Edge(9,18));
  backStands->insertAEdge(new Edge(18,19));
  backStands->insertAEdge(new Edge(19,8));
  backStands->insertAEdge(new Edge(10,11));
  backStands->insertAEdge(new Edge(11,16));
  backStands->insertAEdge(new Edge(16,17));
  backStands->insertAEdge(new Edge(17,10));
  backStands->insertAEdge(new Edge(12,13));
  backStands->insertAEdge(new Edge(13,14));
  backStands->insertAEdge(new Edge(14,15));
  backStands->insertAEdge(new Edge(15,12));
  backStands->insertAEdge(new Edge(1,2));

  backStands->insertAEdge(new Edge(5,6));
  backStands->insertAEdge(new Edge(22,21));
  backStands->insertAEdge(new Edge(7,8));
  backStands->insertAEdge(new Edge(20,19));
  backStands->insertAEdge(new Edge(9,10));
  backStands->insertAEdge(new Edge(18,17));
  backStands->insertAEdge(new Edge(11,12));
  backStands->insertAEdge(new Edge(16,15));
  backStands->insertAEdge(new Edge(13,1));
  backStands->insertAEdge(new Edge(14,2));

  backStands->insertAEdge(new Edge(3,4));
  backStands->insertAEdge(new Edge(4,22));
  backStands->insertAEdge(new Edge(6,22));
  backStands->insertAEdge(new Edge(6,20));
  backStands->insertAEdge(new Edge(8,20));
  backStands->insertAEdge(new Edge(8,18));
  backStands->insertAEdge(new Edge(10,18));
  backStands->insertAEdge(new Edge(10,16));
  backStands->insertAEdge(new Edge(12,16));
  backStands->insertAEdge(new Edge(12,14));
  backStands->insertAEdge(new Edge(1,14));


  backStands->insertAFace(new Face(0,1,34));
  backStands->insertAFace(new Face(3,34,2));
  backStands->insertAFace(new Face(6,3,35));
  backStands->insertAFace(new Face(4,5,35));
  backStands->insertAFace(new Face(25,36,10));
  backStands->insertAFace(new Face(5,24,36));
  backStands->insertAFace(new Face(9,10,37));
  backStands->insertAFace(new Face(7,8,37));
  backStands->insertAFace(new Face(27,38,14));
  backStands->insertAFace(new Face(8,26,38));
  backStands->insertAFace(new Face(13,14,39));
  backStands->insertAFace(new Face(11,12,39));
  backStands->insertAFace(new Face(12,28,40));
  backStands->insertAFace(new Face(29,40,18));
  backStands->insertAFace(new Face(17,18,41));
  backStands->insertAFace(new Face(41,15,16));
  backStands->insertAFace(new Face(31,42,22));
  backStands->insertAFace(new Face(16,30,42));
  backStands->insertAFace(new Face(21,22,43));
  backStands->insertAFace(new Face(19,20,43));
  backStands->insertAFace(new Face(23,33,44));
  backStands->insertAFace(new Face(20,32,44));

  backStands->addWrapper(
    new Vector(-350,-125,-330),
    710,
    30,
    new Vector(1,0,0)
  );


  Vector *P_oArb = new Vector(0,0,0);
  Vector *P_look = new Vector(0.0,-150.0,0.0);
  Vector *P_up = new Vector(15, 10,0);


  /* theScenery->addObjectToTheScene(soccerField);
  theScenery->addObjectToTheScene(theSphere); */

  /* theScenery->addObjectToTheScene(trave_1_esq);
  theScenery->addObjectToTheScene(trave_1_dir);
  theScenery->addObjectToTheScene(trave_1_travessao);
  theScenery->addObjectToTheScene(trave_2_dir);
  theScenery->addObjectToTheScene(trave_2_esq);
  theScenery->addObjectToTheScene(trave_2_travessao); */

  /* theScenery->addObjectToTheScene(Floor);
  theScenery->addObjectToTheScene(front_wall); */

  /* theScenery->addObjectToTheScene(Floor);
  theScenery->addObjectToTheScene(front_wall);



  theScenery->addObjectToTheScene(soccerField);
  theScenery->addObjectToTheScene(cubo_1_esq);
  theScenery->addObjectToTheScene(cubo_1_dir);
  theScenery->addObjectToTheScene(cubo_2_esq);
  theScenery->addObjectToTheScene(cubo_2_dir); */

  /* theScenery->addObjectToTheScene(roofBack);
  theScenery->addObjectToTheScene(roofFront);
  theScenery->addObjectToTheScene(roofLeft);
  theScenery->addObjectToTheScene(roofRight);

  theScenery->addObjectToTheScene(frontStands);
  theScenery->addObjectToTheScene(leftSideStands);
  theScenery->addObjectToTheScene(rightSideStands);
  theScenery->addObjectToTheScene(backStands);

  theScenery->addObjectToTheScene(Floor);
  theScenery->addObjectToTheScene(front_wall); */

 //theScenery->addObjectToTheScene(cubo_1_esq);


  /* double cone_ks[3] = {0.0,1.0,0.498};
  Cone *theCone = new Cone();
  theCone->set_K_a(cone_ks);
  theCone->set_K_d(cone_ks);
  theCone->set_K_e(cone_ks);
  theCone->set_radius(90);
  theCone->set_height(150);
  theCone->set_direction_vector(0.0,1.0,0.0);
  theCone->set_B_vector(0.0,-60.0,-200.0);
  theCone->set_shine(1); */


  /* double cylinder_ks[3] = {0.0,1.0,0.498};
  Cylinder *theCylinder = new Cylinder();
  theCylinder->set_B_vector(0.0,-150.0,-300.0);
  theCylinder->set_height(250);
  theCylinder->set_K_a(cylinder_ks);
  theCylinder->set_K_d(cylinder_ks);
  theCylinder->set_K_e(cylinder_ks);
  theCylinder->set_shine(1);
  theCylinder->set_radius(20);
  theCylinder->set_unitary_vector(0.0,1.0,0.0); */



  double edgeLeng = 40.0;
  Vector *baseVector = new Vector(0.0, -150.0, -165.0);

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
  );

  theMesh->addWrapper(
    new Vector(0.0, -150.0, -165.0),
    50,
    30,
    new Vector(0,1,0)
  );



  theScenery->addObjectToTheScene(theMesh);
  theScenery->addObjectToTheScene(Floor);

  /* calling the ray tracing algorithm */
  theScenery->ray_tracing_algorithm();



  SDL_events(theScenery, &event, window);






  return 0;
}
