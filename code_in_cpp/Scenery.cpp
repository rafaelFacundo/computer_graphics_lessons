#include "scenery.h"
#include "Vector.h"
#include <iostream>
using namespace std; 


Vector* Scenery::get_light_position(){
    return this->Light_position;
};


Vector* Scenery::get_ambient_light_intensity() {
    return this->Ambient_Light_intesity;
};


Vector* Scenery::get_light_intensity(){
    return this->Light_intensity;
};

Vector* Scenery::get_observer_position(){
    return this->observer_point;
};

int Scenery::get_Object_list_lenght() {
    return this->list_Of_Objects.size();
};

void Scenery::set_Light_position(Vector *light){
    this->Light_position = light;
};

void Scenery::set_Light_intensity(Vector *intensityOfLight){
    this->Light_intensity = intensityOfLight;
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

Scenery::Scenery() {
    
}

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
    this->set_Light_position(Light_position);
    this->set_Light_intensity(Light_intensity);
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
        /* if ( i == 0 && thisPoint == -1 ) {
            nearPoint = thisPoint;
            indexToReturn = -1;
        }else if ( i == 0 && thisPoint != -1 ) {
            nearPoint = thisPoint;
            indexToReturn = i;
        }else if (thisPoint > -1  && nearPoint == -1) {
            nearPoint = thisPoint;
            indexToReturn = i;
        }else if (nearPoint > -1 && thisPoint > -1 && nearPoint > thisPoint){
            nearPoint = thisPoint;
            indexToReturn = i;
        } */
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
                bool doesHaveShadow = verify_the_shadow(
                    this->get_light_position(),
                    dir,
                    this->get_observer_position(),
                    objePosiInList
                );
                if ( !doesHaveShadow ) {
                    this->list_Of_Objects[objePosiInList]->gime_your_color(
                        this->get_observer_position(),
                        dir,
                        this->get_light_position(),
                        this->get_light_intensity(),
                        this->get_ambient_light_intensity(), 
                        this->colorToDraw
                    );
                }else {
                    this->list_Of_Objects[objePosiInList]->gimme_your_ambientColor(
                        this->get_ambient_light_intensity(),
                        this->colorToDraw
                    );
                };
            }else{
                this->colorToDraw[0] = 0.0;
                this->colorToDraw[1] = 0.0;
                this->colorToDraw[2] = 0.0;
            }

            /* if (this->colorToDraw[0] == 241.0) {
                cout << this->colorToDraw[0] << '\n';
            } */
            
            /* this->colorToDraw[0] */
            SDL_SetRenderDrawColor(
                this->renderer,
                this->get_minimun(this->colorToDraw[0], 255.0),
                this->get_minimun(this->colorToDraw[1], 255.0),
                this->get_minimun(this->colorToDraw[2], 255.0),
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
    Vector *Pf_pi = this->get_light_position()->minus_with_the_vector(P_i);
    double Pf_pi_norm = sqrt(Pf_pi->scalar_with(Pf_pi));

    for (int i = 0; i < numberOfObjects; i++) {
        if ( i != indexOfObject ) {
            returnType result = this->list_Of_Objects[i]->does_the_point_intercept(L_vector, P_i);
            if (result.doesIntersect && indexOfInterceptedObje == -1) {
                nearPoint =  result.point_of_intersection;
                indexOfInterceptedObje = i;
            }else if (result.doesIntersect && result.point_of_intersection < nearPoint) {
                nearPoint =  result.point_of_intersection;
                indexOfInterceptedObje = i;
            }
            /* if ( i == 0 && thisPoint == -1 ) {
                nearPoint = thisPoint;
                indexOfInterceptedObje = -1;
            }else if ( i == 0 && thisPoint != -1 ) {
                nearPoint = thisPoint;
                indexOfInterceptedObje = i;
            }else if (thisPoint > -1  && nearPoint == -1) {
                nearPoint = thisPoint;
                indexOfInterceptedObje = i;
            }else if (nearPoint > -1 && thisPoint > -1 && nearPoint > thisPoint){
                nearPoint = thisPoint;
                indexOfInterceptedObje = i;
            } */

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