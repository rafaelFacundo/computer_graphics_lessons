#pragma once
#include "Objects.h"
#include <iostream>
#include <vector>
using namespace std;

class Scenery {
    vector<Object*> list_Of_Objects;
    Vector* Light_position;
    Vector* Light_intensity;
    Vector* Ambient_Light_intesity;
    Vector* observer_point;
    int n_lines;
    int n_collumns;
    int height;
    int width;
    int Dy;
    int Dx;
    double z;


    public:
        int call_the_intersections_verifications(Vector *dir, Vector *P_o);
        void ray_tracing_algorithm();
        void draw_pixel();

        void set_Light_position(Vector *light);
        void set_Light_intensity(Vector *intensityOfLight);
        void set_ambient_light_intensity(Vector *light);
        void addObjectToTheScene(Object *object);

        Vector* get_light_position();
        Vector* get_ambient_light_intensity();
        Vector* get_light_intensity();

};