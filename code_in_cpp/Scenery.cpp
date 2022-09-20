#include "scenery.h"
#include "Vector.h"

Vector* Scenery::get_light_position(){
    return this->Light_position;
};


Vector* Scenery::get_ambient_light_intensity() {
    return this->Ambient_Light_intesity;
};


Vector* Scenery::get_light_intensity(){
    return this->Light_intensity;
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

void Scenery::addObjectToTheScene(Object *object) {
    this->list_Of_Objects.push_back(object);
};

/* 
    method that run through the list of objects and take the object point 
    that is near of the observer's position
*/
int Scenery::call_the_intersections_verifications(Vector *dir, Vector *P_o) {
    int numberOfObjects = this->list_Of_Objects.size();
    double minimunPont = 0.0;
    int indexOfTheObject;
    for (int i = 0; i < numberOfObjects; i++) {
        returnType thisPoint = this->list_Of_Objects[i]->does_the_point_intercept(dir, P_o);
        if ( thisPoint.doesIntersect && i == 0 ) {
            minimunPont = thisPoint.point_of_intersection;
            indexOfTheObject = i;
        }else if ( thisPoint.doesIntersect ) {
            minimunPont = thisPoint.point_of_intersection;
            indexOfTheObject = i;
        }
    }

    return indexOfTheObject;
}

void Scenery::ray_tracing_algorithm() {
    for (int l = 0; l < this->n_lines; l++) {
        double Yj = this->height/2 - Dy/2 - l*Dy;
        for (int c = 0; c < this->n_collumns; c++ ) {
            double Xj = - this->width/2 + Dx/2 + c*Dx;
            Vector *dir = new Vector(Xj, Yj, this->z);
            int objePosiInList = call_the_intersections_verifications(dir, this->observer_point);
            double *color = this->list_Of_Objects[objePosiInList]->gime_your_color();
        }
    }
}