#pragma once
#include "Objects.h"
#include <iostream>
using namespace std;
#include <vector>

class Scenery {
    std::vector<sf::Object> list_Of_Objects;
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