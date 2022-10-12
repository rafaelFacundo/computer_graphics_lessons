#pragma once
#include "Objects.h"

class Cone : public Object {
    private:
        Vector *vertice_vector;
        Vector *unitary_vector;
        Vector *B_vector;
        double height;
        double radius;
        double angle;
    
    public:
        void set_B_vector(double x, double y, double z);
        void set_unitary_vector(double x, double y, double z);
        void set_Vertice_vector(double x, double y, double z);
        void set_radius(double radius);
        void set_height(double height);
        void set_angle(double angle);
        double get_radius();
        double get_height();
        double get_angle();
        Vector* get_unitary_vector();
        Vector* get_B_vector();
        Vector* get_Vertice_vector();
        Cone();

        bool is_Ti_a_valid_point(Vector *P_o, Vector *Dr, double Ti);

        void gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Vector *Light_source_position,
            Vector *Light_source_intesity,
            Vector *Ambient_light_intensity,
            double *addressToPutTheColor
        );

        double does_the_point_intercept(Vector *dir, Vector *P_o);
};