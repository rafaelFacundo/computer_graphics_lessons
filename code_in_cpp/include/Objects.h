#pragma once
#include "Vector.h"
#include "returnType.h"

class Object {
    protected:
        Vector *center_Of_Object;
        Vector *K_d_of_object;
        Vector *K_e_of_object;
        Vector *K_a_Of_object;
        double shineness_of_object;
        double T_i;
        int typeOfThisObject;

    public:
        /* Constructor of the class */
        Object();

        Object(
            double center[3],
            double K_e[3],
            double K_d[3],
            double shine,
            double radius
        );

        /* sets and gets of the object atributtes */
        void set_Center_of_Object(double center[3]);
        void set_K_e(double K_e[3]);
        void set_K_d(double K_d[3]);
        void set_K_a(double K_d[3]);
        void set_shine(double shine);
        void set_T_i(double point);

        int get_object_type();
        Vector *get_K_e();
        Vector *get_K_d();
        Vector *get_K_a();
        double* get_center();
        double get_shiness();
        int getTypeOfThisObject();
        Vector *get_L_vector(Vector *Direction, Vector *Eye_position, Vector *Light_source_position);
        Vector *get_Pi(Vector *Direction, Vector *Eye_position);
        void gimme_your_ambientColor(Vector *Ambient_light_intensity, double *addressToPutTheColor);

        int teste ();



        virtual void gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Vector *Light_source_position,
            Vector *Light_source_intesity,
            Vector *Ambient_light_intensity,
            double *addressToPutTheColor
        ) = 0;

        virtual returnType does_the_point_intercept(Vector *dir, Vector *P_o) = 0;

        /* Methods to aplly the transformations */
        virtual void applyRotateX(double angle) = 0;
        virtual void applyRotateY(double angle) = 0;
        virtual void applyRotateZ(double angle) = 0;

        virtual void applyTranslate(double x, double y, double z) = 0;
        virtual void applyScale(double sx, double sy, double sz) = 0;

        virtual void applyReflectXY() = 0;
        virtual void applyReflectXZ() = 0;
        virtual void applyReflectYZ() = 0;

        virtual void applyShearYX(double angle) = 0;
        virtual void applyShearXY(double angle) = 0;
        virtual void applyShearXZ(double angle) = 0;
        virtual void applyShearZX(double angle) = 0;
        virtual void applyShearYZ(double angle) = 0;
        virtual void applyShearZY(double angle) = 0;
};
