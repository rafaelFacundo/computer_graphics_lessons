#pragma once
#include "Objects.h"
#include "Vector.h"

class Sphere : public Object {
    private:
        double Sphere_radius;
        int typeOfThisObject = 0;        
    public:
        void set_radius(double radius);
        double get_radius();

        Sphere();

        Sphere(
            double center[3],
            double K_e[3],
            double K_d[3],
            double shine,
            double radius
        );

        void gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Vector *Light_source,
            Vector *Light_source_intesity,
            Vector *Ambient_light_intensity,
            double *addressToPutTheColor
        );

        returnType does_the_point_intercept( Vector *dir, Vector *w);



        
};