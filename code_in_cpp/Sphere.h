#pragma once
#include "Objects.h"

class Sphere : public Object {
    private:
        double Sphere_radius;
        double T_i;
    public:
        void set_radius(double radius);
        void set_T_i(double point);

        double get_radius();


        Sphere();

        Sphere(
            double center[3],
            double K_e[3],
            double K_d[3],
            double shine,
            double radius
        );

        double* gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Vector *Light_source,
            Vector *Light_source_intesity,
            Vector *Ambient_light_intensity
        );

        virtual returnType does_the_point_intercept( Vector *dir, Vector *w);



        
};