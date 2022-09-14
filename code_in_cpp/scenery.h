#pragma once
#include "Objects.h"

template <int NUMBER_OF_OBJECTS>
class Scenery {
    Object list_Of_Objects[NUMBER_OF_OBJECTS];
    Vector* Light_position;
    Vector* Light_intensity;
    Vector* Ambient_Light_intesity;


    public:
        void call_the_intersections_verifications();
        void ray_tracing_algorithm();
        void draw_pixel();

        void set_Light_position(Vector *light);
        void set_Light_intensity(Vector *intensityOfLight);
        void set_ambient_light_intensity(Vector *light);

        Vector* get_light_position();
        Vector* get_ambient_light_intensity();
        Vector* get_light_intensity();

};