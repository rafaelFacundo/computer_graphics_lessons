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

void Scenery::set_n_lines_and_columns(int lines, int column) {
    this->n_lines = lines;
    this->n_collumns = column;
};
void Scenery::set_width_and_height(int width, int height) {
    this->width = width;
    this->height = height;
};
void Scenery::set_z(int z) {
    this->z = z;
};

void Scenery::set_renderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
};

void Scenery::set_Dx_and_Dy(double dx, double dy) {
    this->Dx = dx;
    this->Dy = dy;
}

Scenery::Scenery() {
    
}

Scenery::Scenery(
    Vector* Light_position,
    Vector* Light_intensity,
    Vector* Ambient_Light_intesity,
    Vector* observer_point,
    int n_lines,
    int n_collumns,
    int height,
    int width,
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
};

/* 
    method that run through the list of objects and take the object point 
    that is near of the observer's position
*/
int Scenery::call_the_intersections_verifications(Vector *dir, Vector *P_o) {
    int numberOfObjects = this->list_Of_Objects.size();
    double minimunPont = 0.0;
    int *indexOfTheObject;
    
    for (int i = 0; i < numberOfObjects; i++) {
        /* cout << "o i é: " << i ; */
        returnType thisPoint = this->list_Of_Objects[i]->does_the_point_intercept(dir, P_o);
        if ( thisPoint.doesIntersect && i == 0 ) {
            minimunPont = thisPoint.point_of_intersection;
            *indexOfTheObject = i;
           
        }else if ( thisPoint.doesIntersect && (thisPoint.point_of_intersection < minimunPont) ) {
            minimunPont = thisPoint.point_of_intersection;
            *indexOfTheObject = i;
        }
    }

    int value = 0;
     
    return value;
}

void Scenery::ray_tracing_algorithm() {
    
    for (int l = 0; l < this->n_lines; l++) {
        double Yj = this->height/2 - Dy/2 - l*Dy;
        for (int c = 0; c < this->n_collumns; c++ ) {
            double Xj = - this->width/2 + Dx/2 + c*Dx;
            Vector *dir = new Vector(Xj, Yj, this->z);
            int objePosiInList = call_the_intersections_verifications(dir, this->observer_point);
            
            if ( objePosiInList > -1) {
                /* this->list_Of_Objects[objePosiInList]->gime_your_color(
                    this->get_observer_position(),
                    dir,
                    this->get_light_position(),
                    this->get_light_intensity(),
                    this->get_ambient_light_intensity(), 
                    this->colorToDraw
                ); */
                /* cout << this->list_Of_Objects[objePosiInList]->teste() << '\n'; */
            }else{
                this->colorToDraw[0] = 0.0;
                this->colorToDraw[1] = 0.0;
                this->colorToDraw[2] = 0.0;
            }
            /*
            set_sdl_draw_color(this->renderer, color[0], color[1], color[3], 255);
            paint_the_point(this->renderer, c, l); */
            
            
        }
    }
}