#include "scenery.h"

void Scenery::set_Light_position(Vector *light){
    this->Light_position = light;
};

void Scenery::set_Light_intensity(Vector *intensityOfLight){
    this->Light_intensity = intensityOfLight;
};


void Scenery::set_ambient_light_intensity(Vector *light){
    this->Ambient_Light_intesity = light;
};


Vector* Scenery::get_light_position(){
    return this->Light_position;
};


Vector* Scenery::get_ambient_light_intensity() {
    return this->Ambient_Light_intesity;
};


Vector* Scenery::get_light_intensity(){
    return this->Light_intensity;
};