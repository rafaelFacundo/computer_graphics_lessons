#pragma once
#include "Objects.h"
#include "Vector.h"

class Cylinder : public Object {
    Vector *unitary_vector;
    Vector *B_vector;

    public:
        void set_B_vector(double x, double y, double z);
        void set_unitary_vector(double x, double y, double z);
        void set_radius(double radius);
        double get_radius();
        Vector* get_unitary_vector();
        Vector* get_B_vector();
        double radius;


        void gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Vector *Light_source_position,
            Vector *Light_source_intesity,
            Vector *Ambient_light_intensity,
            double *addressToPutTheColor
        ) = 0;

        double does_the_point_intercept(Vector *dir, Vector *P_o) = 0;
        
};