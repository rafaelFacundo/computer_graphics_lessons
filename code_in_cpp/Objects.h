#pragma once
#include "Vector.h"
#include "returnType.h"

class Object {
    protected:
        Vector *center_Of_Object;
        Vector *K_d_of_object;
        Vector *K_e_of_object;
        double shineness_of_object;
        double T_i;
    public:
        /* sets and gets of the object atributtes */
        void set_Center_of_Object(double center[3]);
        void set_K_e(double K_e[3]);
        void set_K_d(double K_d[3]);
        void set_shine(double shine);
        void set_T_i(double point);
        Vector *get_K_e();
        Vector *get_K_d();
        double* get_center();

        /* Constructor of the class */
        Object();

        virtual double* gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Vector *Light_source_position,
            Vector *Light_source_intesity,
            Vector *Ambient_light_intensity
        ) = 0;

        virtual returnType does_the_point_intercept(Vector *dir, Vector *P_o);
};
