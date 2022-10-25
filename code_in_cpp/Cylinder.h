#pragma once
#include "Objects.h"
#include "Vector.h"

class Cylinder : public Object {
    Vector *unitary_vector;
    Vector *B_vector;
    double height;
    double radius;
    int typeOfThisObject = 2;

    public:
        void set_B_vector(double x, double y, double z);
        void set_unitary_vector(double x, double y, double z);
        void set_radius(double radius);
        void set_height(double height);
        double get_radius();
        double get_height();
        Vector* get_unitary_vector();
        Vector* get_B_vector();
        Cylinder();
        

        bool is_Ti_a_valid_point(Vector *P_o, Vector *Dr, double Ti);

        void gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Vector *Light_source_position,
            Vector *Light_source_intesity,
            Vector *Ambient_light_intensity,
            double *addressToPutTheColor
        );

        returnType does_the_point_intercept(Vector *dir, Vector *P_o);
        
};