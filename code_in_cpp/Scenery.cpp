#include "scenery.h"

template <int NUMBER_OF_OBJECTS>
void Scenery<NUMBER_OF_OBJECTS>::set_Light_position(Vector *light){
    this->Light_position = light;
};
template <int NUMBER_OF_OBJECTS>
void Scenery<NUMBER_OF_OBJECTS>::set_Light_intensity(Vector *intensityOfLight){
    this->Light_intensity = intensityOfLight;
};

template <int NUMBER_OF_OBJECTS>
void Scenery<NUMBER_OF_OBJECTS>::set_ambient_light_intensity(Vector *light){
    this->Ambient_Light_intesity = light;
};

template <int NUMBER_OF_OBJECTS>
Vector* Scenery<NUMBER_OF_OBJECTS>::get_light_position(){
    return this->Light_position;
};

template <int NUMBER_OF_OBJECTS>
Vector* Scenery<NUMBER_OF_OBJECTS>::get_ambient_light_intensity() {
    return this->Ambient_Light_intesity;
};

template <int NUMBER_OF_OBJECTS>
Vector* Scenery<NUMBER_OF_OBJECTS>::get_light_intensity(){
    return this->Light_intensity;
};