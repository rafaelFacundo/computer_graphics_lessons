#pragma once
#include "Objects.h"
#include "sdlFunctionsToPaint.h"
#include "Light.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
using namespace std;

class Scenery {
    vector<Object*> list_Of_Objects;
    vector<Light*> list_of_light;
    Vector* Ambient_Light_intesity;
    Vector* observer_point;
    double n_lines;
    double n_collumns;
    double height;
    double width;
    double z;
    double* colorToDraw = (double*)malloc(sizeof(double)*3);
    SDL_Renderer *renderer;
    bool isPerspective = true;

    public:
        Scenery();

        Scenery(
            Light** lights,
            int numberOfLights,
            Vector* Ambient_Light_intesity,
            Vector* observer_point,
            double n_lines,
            double n_collumns,
            double height,
            double width,
            double z,
            SDL_Renderer *renderer
        );

        int  call_the_intersections_verifications(Vector *dir, Vector *P_o);
        void ray_tracing_algorithm();
        void draw_pixel();
        bool verify_the_shadow(
            Light *light,
            Vector *dir,
            Vector *P_o,
            int indexOfObject
        );

        /* void set_Light_position(Vector *light, Vector *intensityOfLight);
        void set_Light_intensity(Vector *intensityOfLight); */

        void addLight(Light *light);
        void addLights(Light **lights, int lenght);
        void set_ambient_light_intensity(Vector *light);
        void set_observer_postion(Vector *observer);
        void addObjectToTheScene(Object *object);
        void set_n_lines_and_columns(double lines, double column);
        void set_width_and_height(double width, double height);
        void set_z(int z);
        void set_renderer(SDL_Renderer *renderer);
        void set_projection(int type);


        void calculateTheColor(int indexOfObject, Vector *dir);
        double get_minimun(double num1, double num2);
        double get_max_rgb(double num1, double num2, double num3);
        double get_z();
        // Vector* get_light_position(int index);
        Vector* get_ambient_light_intensity();
        Vector* get_light_intensity(int index);
        Vector* get_observer_position();
        int get_Object_list_lenght();
        SDL_Renderer* get_sceneryRender();



        int verifyIfClickHitsSomeObjetc(int x, int y);
        void makeModificationOnObject(int indexOfObj);

        void modifyScenery();
        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);
};
