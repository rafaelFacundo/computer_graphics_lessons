#pragma once
#include "Objects.h"
#include "SdlFunction.h"
#include <iostream>
#include <SDL2/SDL.h>
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
    SDL_Renderer *renderer;

    public:
        int call_the_intersections_verifications(Vector *dir, Vector *P_o);
        void ray_tracing_algorithm();
        void draw_pixel();

        void set_Light_position(Vector *light);
        void set_Light_intensity(Vector *intensityOfLight);
        void set_ambient_light_intensity(Vector *light);
        void set_observer_postion(Vector *observer);
        void addObjectToTheScene(Object *object);
        void set_n_lines_and_columns(int lines, int column);
        void set_width_and_height(int width, int height);
        void set_Dx_and_Dy(double dx, double dy);
        void set_z(int z);
        void set_renderer(SDL_Renderer *renderer);

        Vector* get_light_position();
        Vector* get_ambient_light_intensity();
        Vector* get_light_intensity();
        Vector* get_observer_position();

        Scenery();

        Scenery(
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
        );
};