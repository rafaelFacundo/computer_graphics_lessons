#include "../include/scenery.h"
#include "../include/Vector.h"
#include <iostream>
using namespace std;


Scenery::Scenery() {

}


Vector* Scenery::get_light_position(int index){
    return this->Light_position[index];
};


Vector* Scenery::get_ambient_light_intensity() {
    return this->Ambient_Light_intesity;
};


Vector* Scenery::get_light_intensity(int index){
    return this->Light_intensity[index];
};

Vector* Scenery::get_observer_position(){
    return this->observer_point;
};

int Scenery::get_Object_list_lenght() {
    return this->list_Of_Objects.size();
};

void Scenery::set_Light_position(Vector *light, Vector *intensityOfLight){
    this->Light_position.push_back(light);
    this->set_Light_intensity(intensityOfLight);
};

void Scenery::set_Light_intensity(Vector *intensityOfLight){
    this->Light_intensity.push_back(intensityOfLight);

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
    Vector* Light_position,
    Vector* Light_intensity,
    Vector* Ambient_Light_intesity,
    Vector* observer_point,
    double n_lines,
    double n_collumns,
    double height,
    double width,
    double z,
    SDL_Renderer *renderer
) {
    this->set_Light_position(Light_position, Light_intensity);
    //this->set_Light_intensity(Light_intensity);
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
    double Dx = this->width/this->n_lines;
    double Dy = this->height/this->n_collumns;

    for (int l = 0; l < this->n_lines; l++) {
        double Yj = this->height/2 - Dy/2 - l*Dy;
        for (int c = 0; c < this->n_collumns; c++ ) {
            double Xj = -this->width/2 + Dx/2 + c*Dx;
            Vector *dir = new Vector(Xj, Yj, this->get_z());

            int objePosiInList = call_the_intersections_verifications(dir, this->observer_point);
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
    Vector *Light_source_position,
    Vector *dir,
    Vector *P_o,
    int indexOfObject
){
    int numberOfObjects = this->get_Object_list_lenght();
    double nearPoint = 0;
    int indexOfInterceptedObje = -1;
    Vector *L_vector = this->list_Of_Objects[indexOfObject]->get_L_vector(dir, P_o, Light_source_position);
    Vector *P_i = this->list_Of_Objects[indexOfObject]->get_Pi(dir, P_o);
    Vector *Pf_pi = Light_source_position->minus_with_the_vector(P_i);
    double Pf_pi_norm = sqrt(Pf_pi->scalar_with(Pf_pi));

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

    for (int i = 0; i < this->Light_intensity.size(); i++) {
        Vector *LightIntensity = this->Light_intensity[i];
        Vector *LightPosition = this->Light_position[i];

        bool doesHaveShadowForThisLight = verify_the_shadow(
            LightPosition,
            dir,
            this->get_observer_position(),
            indexOfObject
        );

        if (!doesHaveShadowForThisLight) {
            this->list_Of_Objects[indexOfObject]->gime_your_color(
                this->get_observer_position(),
                dir,
                LightPosition,
                LightIntensity,
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
    Vector* Ka = interceptedObject->get_K_a();
    Vector* Kd = interceptedObject->get_K_d();
    Vector* Ke = interceptedObject->get_K_e();
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
            break;
        default:
            cout << "blalalbalb\n";
            break;
    };

    this->ray_tracing_algorithm();
};
