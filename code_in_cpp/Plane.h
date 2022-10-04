#pragma once
#include "Objects.h"
#include "Vector.h"

class Plane : public Object {
    private:
        Vector* Ppi_Point;
        Vector* N_vector;
    public:

    Plane();

    void set_PI_Point(double x, double y, double z);
    void set_N_vector(double x, double y, double z);


    Vector* get_PI_Point();
    Vector* get_N_vector();

    void gime_your_color(
        Vector *Eye_position,
        Vector *Direction,
        Vector *Light_source_position,
        Vector *Light_source_intesity,
        Vector *Ambient_light_intensity,
        double *addressToPutTheColor
    );

    double does_the_point_intercept(Vector *dir, Vector *P_o) ;
    
};