#include "../include/scenery.h"
#include "../include/Vector.h"
#include <iostream>
using namespace std;


Scenery::Scenery() {

}


/* Vector* Scenery::get_light_position(int index){
    if (this->list_of_light[index]->getType() != 2) {
        return ((PointLight)this->list_of_light[index]).getPosition();
    };
}; */


Vector* Scenery::get_ambient_light_intensity() {
    return this->Ambient_Light_intesity;
};


Vector* Scenery::get_observer_position(){
    return this->observer_point;
};

int Scenery::get_Object_list_lenght() {
    return this->list_Of_Objects.size();
};

void Scenery::addLight(Light *light){
    this->list_of_light.push_back(light);
};

void Scenery::addLights(Light **lights, int lenght){
    for (int i = 0; i < lenght; i++) {
        this->list_of_light.push_back(lights[i]);
    }

};

void Scenery::set_ambient_light_intensity(Vector *light){
    this->Ambient_Light_intesity = light;
};

void Scenery::set_observer_postion(Vector *observer){
    this->observer_point = observer;
};

void Scenery::addObjectToTheScene(Object *object) {
    this->list_Of_Objects.push_back(object);
};

void Scenery::set_n_lines_and_columns(double lines, double column) {
    this->n_lines = lines;
    this->n_collumns = column;
};
void Scenery::set_width_and_height(double width, double height) {
    this->width = width;
    this->height = height;
};
void Scenery::set_z(int z) {
    this->z = z;
};

void Scenery::set_renderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
};

SDL_Renderer* Scenery::get_sceneryRender(){
    return this->renderer;
};

double Scenery::get_z() {
    return this->z;
};

double Scenery::get_minimun(double num1, double num2) {
    if ( num1 < num2 ) {
        return num1;
    }

    return num2;
};

double Scenery::get_max_rgb(double num1, double num2, double num3) {
    if (num1 > num2 && num1 > num3) {
        return num1;
    }else if (num2 > num1 && num2 > num3) {
        return num2;
    }else {
        return num3;
    }
};


Scenery::Scenery(
    Light** lights,
    int numberOfLights,
    Vector* Ambient_Light_intesity,
    Vector* observer_point,
    double n_lines,
    double n_collumns,
    double height,
    double width,
    double z,
    SDL_Renderer *renderer
) {

    this->addLights(lights, numberOfLights);
    this->set_ambient_light_intensity(Ambient_Light_intesity);
    this->set_observer_postion(observer_point);
    this->set_n_lines_and_columns(n_lines, n_collumns);
    this->set_width_and_height(width, height);
    this->set_z(z);
    this->set_renderer(renderer);
}
/*
    method that run through the list of objects and take the object point
    that is near of the observer's position
*/
int Scenery::call_the_intersections_verifications(Vector *dir, Vector *P_o) {
    int numberOfObjects = this->get_Object_list_lenght();
    double nearPoint = 0;
    int indexToReturn = -1;

    for (int i = 0; i < numberOfObjects; i++) {
        returnType result = this->list_Of_Objects[i]->does_the_point_intercept(dir, P_o);
        if (result.doesIntersect && indexToReturn == -1) {
            nearPoint =  result.point_of_intersection;
            indexToReturn = i;
        }else if (result.doesIntersect && result.point_of_intersection < nearPoint) {
            nearPoint =  result.point_of_intersection;
            indexToReturn = i;
        }
    }
    return indexToReturn;
}

void Scenery::ray_tracing_algorithm() {
    Vector *dir = new Vector();
    Vector *observer = new Vector();
    double Dx = this->width/this->n_collumns;
    double Dy = this->height/this->n_lines;
    double z = this->get_z();

    for (int l = 0; l < this->n_lines; l++) {
        double Yj = this->height/2 - Dy/2 - l*Dy;
        for (int c = 0; c < this->n_collumns; c++ ) {
            double Xj = -this->width/2 + Dx/2 + c*Dx;
            if (isPerspective) {
                dir->set_x_Point(Xj);
                dir->set_y_Point(Yj);
                dir->set_z_Point(z);
                observer = this->observer_point;
            }else {
                dir->set_x_Point(0);
                dir->set_y_Point(0);
                dir->set_z_Point(-1);
                observer->set_x_Point(Xj);
                observer->set_y_Point(Yj);
                observer->set_z_Point(z);
            }

            int objePosiInList = call_the_intersections_verifications(dir, observer);
            if ( objePosiInList > -1) {

                calculateTheColor(objePosiInList, dir);
            }else{
                this->colorToDraw[0] = 0.0;
                this->colorToDraw[1] = 0.0;
                this->colorToDraw[2] = 0.0;
            }

            if (this->colorToDraw[0] > 1 || this->colorToDraw[1] > 1 || this->colorToDraw[2] > 1) {
                double maxValue = this->get_max_rgb(this->colorToDraw[0], this->colorToDraw[1], this->colorToDraw[2]);
                this->colorToDraw[0] /= maxValue;
                this->colorToDraw[1] /= maxValue;
                this->colorToDraw[2] /= maxValue;
            }

            SDL_SetRenderDrawColor(
                this->renderer,
                this->get_minimun((this->colorToDraw[0] * 255), 255.0),
                this->get_minimun((this->colorToDraw[1] * 255), 255.0),
                this->get_minimun((this->colorToDraw[2] * 255), 255.0),
                255
            );
            SDL_RenderDrawPoint(this->renderer, c, l);


        }
    }


    SDL_RenderPresent(this->renderer);
}

bool Scenery::verify_the_shadow(
    Light *light,
    Vector *dir,
    Vector *P_o,
    int indexOfObject
){
    Vector *L_vector;
    Vector *Pf_pi;
    double Pf_pi_norm;
    int numberOfObjects = this->get_Object_list_lenght();
    double nearPoint = 0;
    int indexOfInterceptedObje = -1;

    /* Vector *L_vector = this->list_Of_Objects[indexOfObject]->get_L_vector(dir, P_o, Light_source_position);
    Vector *P_i = this->list_Of_Objects[indexOfObject]->get_Pi(dir, P_o);
    Vector *Pf_pi = Light_source_position->minus_with_the_vector(P_i);
    double Pf_pi_norm = sqrt(Pf_pi->scalar_with(Pf_pi)); */

    Vector *P_i = this->list_Of_Objects[indexOfObject]->get_Pi(dir, P_o);

    if (light->getType() != 2) {
        L_vector = this->list_Of_Objects[indexOfObject]->get_L_vector(dir, P_o, ((PointLight*)light)->getPosition());
        Pf_pi = ((PointLight*)light)->getPosition()->minus_with_the_vector(P_i);
        Pf_pi_norm = sqrt(Pf_pi->scalar_with(Pf_pi));
    }else {
        L_vector = ((DirectionalLight*)light)->getDirection()->multiply_by_a_scalar(-1);
        Pf_pi_norm = L_vector->getNormOfThisVector();
    }


    for (int i = 0; i < numberOfObjects; i++) {
        if ( i != indexOfObject ) {
            returnType result = this->list_Of_Objects[i]->does_the_point_intercept(L_vector, P_i);
            if ( result.point_of_intersection >= 0) {
                if (result.doesIntersect && indexOfInterceptedObje == -1) {
                    nearPoint =  result.point_of_intersection;
                    indexOfInterceptedObje = i;
                }else if (result.doesIntersect && result.point_of_intersection < nearPoint) {
                    nearPoint =  result.point_of_intersection;
                    indexOfInterceptedObje = i;
                }
            }

            if(result.point_of_intersection > Pf_pi_norm){
                indexOfInterceptedObje = -1;
            }

        }

    }



    if ( indexOfInterceptedObje == -1 ) {
        return false;
    }else {
        return true;
    }

};


void Scenery::calculateTheColor(int indexOfObject, Vector *dir) {
    this->colorToDraw[0] = 0.0;
    this->colorToDraw[1] = 0.0;
    this->colorToDraw[2] = 0.0;
    Light *light;

    for (int i = 0; i < this->list_of_light.size(); i++) {
        /* Vector *LightIntensity = this->Light_intensity[i];
        Vector *LightPosition = this->Light_position[i]; */
        light = list_of_light[i];
        bool doesHaveShadowForThisLight = verify_the_shadow(
            light,
            dir,
            this->get_observer_position(),
            indexOfObject
        );

        if (!doesHaveShadowForThisLight) {
            this->list_Of_Objects[indexOfObject]->gime_your_color(
                this->get_observer_position(),
                dir,
                light,
                this->get_ambient_light_intensity(),
                this->colorToDraw
            );
        }else {
            this->list_Of_Objects[indexOfObject]->gimme_your_ambientColor(
                this->get_ambient_light_intensity(),
                this->colorToDraw
            );

        }
    }


};



void Scenery::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
    for (Object* obj : this->list_Of_Objects) {
        obj->applyConvertWordVectoToCanvas(P_o, P_Look, Up);
    }

    for (Light* light : this->list_of_light){
        light->applyConvertWordVectoToCanvas(P_o, P_Look, Up);
    }



}

int Scenery::verifyIfClickHitsSomeObjetc(int x, int y) {
    double Dx = this->width/this->n_lines;
    double Dy = this->height/this->n_collumns;
    double Yj = this->height/2 - Dy/2 - y*Dy;
    double Xj = -this->width/2 + Dx/2 + x*Dx;
    Vector *dir = new Vector(Xj, Yj, this->get_z());
    int indexOfObjectIntercepted = -1;

    indexOfObjectIntercepted = call_the_intersections_verifications(dir, this->observer_point);
    if ( indexOfObjectIntercepted > -1) {
        cout << this->list_Of_Objects[indexOfObjectIntercepted]->get_object_type() << '\n';
    }else{
        cout << "não atingiu um objeto\n";
    }
    return indexOfObjectIntercepted;
};

void Scenery::makeModificationOnObject(int indexOfObj) {
    Object* interceptedObject = this->list_Of_Objects[indexOfObj];
    double *newCoeficients = (double*)malloc(sizeof(double) * 3);
    int objectType = interceptedObject->get_object_type();
    int resposta;

    cout << "Digite a opção que deseja fazer: \n";
    switch (objectType) {
        case 0:
            cout << "1 - Transladar a esfera.\n";
            cout << "2 - Modificar a escala da esfera.\n";
            cout << "3 - Modificar as cores.\n";
            cin >> resposta;
            if (cin.fail() || resposta > 3 || resposta < 1)  {
                cout << "Entrada inválida";
                cin.clear();
                cin.ignore(100);
                break;
            }
            if (resposta == 1) {
                cout << "Digite o valor de x: ";
                cin >> newCoeficients[0];
                cout << "Digite o valor de y: ";
                cin >> newCoeficients[1];
                cout << "Digite o valor de z: ";
                cin >> newCoeficients[2];
                interceptedObject->applyTranslate(newCoeficients[0],newCoeficients[1],newCoeficients[2]);
            }else if (resposta == 2) {
                cout << "Digite o valor de multiplicação do raio: ";
                cin >> newCoeficients[0];
                interceptedObject->applyScale(newCoeficients[0],0,0);
            }else {
                cout << "Digite o novo valor do Kd: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_d(newCoeficients);
                cout << "Digite o novo valor do Ke: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
                cout << "Digite o novo valor do Ka: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
            }
            break;

        case 1:
            cout << "1 - Transladar o plano.\n";
            cout << "2 - Rotacionar o plano em x.\n";
            cout << "3 - Rotacionar o plano em y.\n";
            cout << "4 - Rotacionar o plano em z.\n";
            cout << "5 - Modificar as cores.\n";
            cin >> resposta;
            if (cin.fail() || resposta > 5 || resposta < 1)  {
                cout << "Entrada inválida\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }
            if (resposta == 1) {
                cout << "Digite o valor de x: ";
                cin >> newCoeficients[0];
                cout << "Digite o valor de y: ";
                cin >> newCoeficients[1];
                cout << "Digite o valor de z: ";
                cin >> newCoeficients[2];
                interceptedObject->applyTranslate(newCoeficients[0],newCoeficients[1],newCoeficients[2]);
            }else if (resposta == 2) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateX(newCoeficients[0]);
            }else if (resposta == 3) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateY(newCoeficients[0]);
            }else if (resposta == 4) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateZ(newCoeficients[0]);
            }else {
                cout << "Digite o novo valor do Kd: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_d(newCoeficients);
                cout << "Digite o novo valor do Ke: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
                cout << "Digite o novo valor do Ka: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
            }
            break;

        case 2:
            cout << "1 - Transladar o cilindro.\n";
            cout << "2 - Rotacionar o cilindro em x.\n";
            cout << "3 - Rotacionar o cilindro em y.\n";
            cout << "4 - Rotacionar o cilindro em z.\n";
            cout << "5 - Modificar a escala do cilindro.\n";
            cout << "6 - Modificar as cores.\n";

            cin >> resposta;
            if (cin.fail() || resposta > 6 || resposta < 1)  {
                cout << "Entrada inválida\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }
            if (resposta == 1) {
                cout << "Digite o valor de x: ";
                cin >> newCoeficients[0];
                cout << "Digite o valor de y: ";
                cin >> newCoeficients[1];
                cout << "Digite o valor de z: ";
                cin >> newCoeficients[2];
                interceptedObject->applyTranslate(newCoeficients[0],newCoeficients[1],newCoeficients[2]);
            }else if (resposta == 2) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateX(newCoeficients[0]);
            }else if (resposta == 3) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateY(newCoeficients[0]);
            }else if (resposta == 4) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateZ(newCoeficients[0]);
            }else if (resposta == 5) {
                cout << "Digite o valor da escala: ";
                cin >> newCoeficients[0];
                interceptedObject->applyScale(newCoeficients[0], 0, 0);
            }else {
                cout << "Digite o novo valor do Kd: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_d(newCoeficients);
                cout << "Digite o novo valor do Ke: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
                cout << "Digite o novo valor do Ka: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
            }
            break;
        case 3:
            cout << "1 - Transladar o cone.\n";
            cout << "2 - Rotacionar o cone em x.\n";
            cout << "3 - Rotacionar o cone em y.\n";
            cout << "4 - Rotacionar o cone em z.\n";
            cout << "5 - Modificar a escala do cone.\n";
            cout << "6 - Modificar as cores.\n";
            cin >> resposta;
            if (cin.fail() || resposta > 6 || resposta < 1)  {
                cout << "Entrada inválida\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }
            if (resposta == 1) {
                cout << "Digite o valor de x: ";
                cin >> newCoeficients[0];
                cout << "Digite o valor de y: ";
                cin >> newCoeficients[1];
                cout << "Digite o valor de z: ";
                cin >> newCoeficients[2];
                interceptedObject->applyTranslate(newCoeficients[0],newCoeficients[1],newCoeficients[2]);
            }else if (resposta == 2) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateX(newCoeficients[0]);
            }else if (resposta == 3) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateY(newCoeficients[0]);
            }else if (resposta == 4) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateZ(newCoeficients[0]);
            }else if (resposta == 5) {
                cout << "Digite o valor da escala: ";
                cin >> newCoeficients[0];
                interceptedObject->applyScale(newCoeficients[0], 0, 0);
            }else {
                cout << "Digite o novo valor do Kd: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_d(newCoeficients);
                cout << "Digite o novo valor do Ke: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
                cout << "Digite o novo valor do Ka: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
            }
            break;
        case 4:
            cout << "1  - Transladar a malha.\n";
            cout << "2  - Rotacionar a malha em x.\n";
            cout << "3  - Rotacionar a malha em y.\n";
            cout << "4  - Rotacionar a malha em z.\n";
            cout << "5  - Modificar a escala da malha.\n";
            cout << "6  - Modificar as cores.\n";
            cout << "7  - Aplicar Reflect XY.\n";
            cout << "8  - Aplicar Reflect XZ.\n";
            cout << "9  - Aplicar Reflect YZ.\n";
            cout << "10 - Aplicar Shear YX.\n";
            cout << "11 - Aplicar Shear XY.\n";
            cout << "12 - Aplicar Shear XZ.\n";
            cout << "13 - Aplicar Shear ZX.\n";
            cout << "14 - Aplicar Shear YZ.\n";
            cout << "15 - Aplicar Shear ZY.\n";
            cin >> resposta;
            if (cin.fail() || resposta > 15 || resposta < 1)  {
                cout << "Entrada inválida\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }
            if (resposta == 1) {
                cout << "Digite o valor de x: ";
                cin >> newCoeficients[0];
                cout << "Digite o valor de y: ";
                cin >> newCoeficients[1];
                cout << "Digite o valor de z: ";
                cin >> newCoeficients[2];
                interceptedObject->applyTranslate(newCoeficients[0],newCoeficients[1],newCoeficients[2]);
            }else if (resposta == 2) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateX(newCoeficients[0]);
            }else if (resposta == 3) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateY(newCoeficients[0]);
            }else if (resposta == 4) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyRotateZ(newCoeficients[0]);
            }else if (resposta == 5) {
                cout << "Digite o valor da escala: ";
                cin >> newCoeficients[0];
                interceptedObject->applyScale(newCoeficients[0], 0, 0);
            }else if (resposta == 6) {
                cout << "Digite o novo valor do Kd: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_d(newCoeficients);
                cout << "Digite o novo valor do Ke: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
                cout << "Digite o novo valor do Ka: ";
                scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
                interceptedObject->set_K_e(newCoeficients);
            }else if (resposta == 7) {
                interceptedObject->applyReflectXY();
            } else if (resposta == 8) {
                interceptedObject->applyReflectXZ();
            }else if (resposta == 9) {
                interceptedObject->applyReflectYZ();
            }else if (resposta == 10) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyShearYX(newCoeficients[0]);
            }else if (resposta == 11) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyShearXY(newCoeficients[0]);
            }else if (resposta == 12) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyShearXZ(newCoeficients[0]);
            }else if (resposta == 13) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyShearZX(newCoeficients[0]);
            }else if (resposta == 14) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyShearYZ(newCoeficients[0]);
            }else if (resposta == 15) {
                cout << "Digite o valor do angulo: ";
                cin >> newCoeficients[0];
                interceptedObject->applyShearZY(newCoeficients[0]);
            }
            break;
        default:
            cout << "Não atingiu nenhum objeto.";
            break;
    };

    this->ray_tracing_algorithm();
};




void Scenery::modifyScenery() {
    int resposta;
    int resposta2;
    double *newCoeficients = (double*)malloc(sizeof(double) * 3);
    cout << "Digite oque você deseja fazer: \n";
    cout << "1 - mudar o observador de lugar: \n";
    cout << "2 - mudar a intensidade da luz ambiente.\n";
    cout << "3 - mudar o número o tamanho e altura da janela.\n";
    cout << "4 - mudar a intensidade de uma luz especifica.\n";
    cout << "5 - mudar a distância d.\n";
    cout << "6 - mudar o tipo de projeção.\n";
    cin >> resposta;
    if ( cin.fail() || resposta > 6 || resposta < 1 ) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "entrada inválida.";
        return;
    }
    switch (resposta) {
        case 1:
            {
            cout << "Digite o vetor P_o arbitrario: no formato x,y,z.\n";
            scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
            Vector *P_o = new Vector(newCoeficients[0],newCoeficients[1],newCoeficients[2]);
            cout << "Digite o vetor do ponto Look at: no formato x,y,z.\n";
            scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
            Vector *P_look = new Vector(newCoeficients[0],newCoeficients[1],newCoeficients[2]);
            cout << "Digite o vetor do ponto Up: no formato x,y,z.\n";
            scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
            Vector *up = new Vector(newCoeficients[0],newCoeficients[1],newCoeficients[2]);
            this->applyConvertWordVectoToCanvas(P_o, P_look, up);
            }
            break;
        case 2:
            cout << "Digite o vetor da nova intensidade: no formato x,y,z.\n";
            scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
            this->get_ambient_light_intensity()->set_x_Point(newCoeficients[0]);
            this->get_ambient_light_intensity()->set_y_Point(newCoeficients[1]);
            this->get_ambient_light_intensity()->set_z_Point(newCoeficients[2]);
            break;
        case 3:
            cout << "Digite o número de linhas: \n";
            cin >> newCoeficients[0];
            if ( cin.fail() ) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "entrada inválida.";
                return;
            }
            cout << "Digite o número de colunas: \n";
            cin >> newCoeficients[1];
            if ( cin.fail() ) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "entrada inválida.";
                return;
            }
            this->width = newCoeficients[1];
            this->height = newCoeficients[0];
            break;
        case 4:
            cout << "Digite o indice da luz correspondente: \n";
            cin >> resposta2;
            if ( cin.fail() || resposta2 > this->list_of_light.size() || resposta2 < 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "entrada inválida.";
                return;
            }
            cout << "Digite o vetor da nova intensidade: no formato x,y,z.\n";
            scanf("%lf, %lf, %lf", &newCoeficients[0],&newCoeficients[1],&newCoeficients[2]);
            this->list_of_light[resposta2]->setIntesity(new Vector(newCoeficients[0],newCoeficients[1],newCoeficients[2]));
            break;
        case 5:
            cout << "Digite o valor do novo z (o valor será somado): \n";
            cin >> newCoeficients[0];
            if ( cin.fail() ) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "entrada inválida.";
                return;
            }
            this->set_z(this->get_z() + newCoeficients[0]);
            break;
        case 6:
            cout << "Digite 1 para projeção perspectiva e digite 2 para projeção ortográfica: ";
            cin >> resposta2;
            if ( cin.fail() || resposta2 > 2 || resposta2 < 1) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "entrada inválida.";
                return;
            }
            this->set_projection(resposta2);
            break;
        default:
            break;
    }
    this->ray_tracing_algorithm();
};




void Scenery::set_projection(int type) {
    if (type == 1) {
        this->isPerspective = true;
    }else {
        this->isPerspective = false;
    }
};

