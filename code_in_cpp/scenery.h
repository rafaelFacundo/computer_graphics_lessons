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
    double n_lines;
    double n_collumns;
    double height;
    double width;
    double z;
    double* colorToDraw = (double*)malloc(sizeof(double)*3);
    SDL_Renderer *renderer;

    public:
        int  call_the_intersections_verifications(Vector *dir, Vector *P_o);
        void ray_tracing_algorithm();
        void draw_pixel();
        bool verify_the_shadow(
            Vector *Light_source_position,
            Vector *dir,
            Vector *P_o,
            int indexOfObject
        );

        void set_Light_position(Vector *light);
        void set_Light_intensity(Vector *intensityOfLight);
        void set_ambient_light_intensity(Vector *light);
        void set_observer_postion(Vector *observer);
        void addObjectToTheScene(Object *object);
        void set_n_lines_and_columns(double lines, double column);
        void set_width_and_height(double width, double height);
        void set_z(int z);
        void set_renderer(SDL_Renderer *renderer);

        double get_minimun(double num1, double num2);
        double get_z();
        Vector* get_light_position();
        Vector* get_ambient_light_intensity();
        Vector* get_light_intensity();
        Vector* get_observer_position();
        int get_Object_list_lenght();
        SDL_Renderer* get_sceneryRender();

        Scenery();

        Scenery(
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
        );
};