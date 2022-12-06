#pragma once
#include "Objects.h"
#include "Vector.h"

class Sphere : public Object {
    private:
        double Sphere_radius;
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

        Vector* get_center_vector();
        returnType does_the_point_intercept( Vector *dir, Vector *w);

        void applyRotateX(double angle);
        void applyRotateY(double angle);
        void applyRotateZ(double angle);

        void applyTranslate(double x, double y, double z);
        void applyScale(double sx, double sy, double sz);

        void applyReflectXY();
        void applyReflectXZ();
        void applyReflectYZ();

        void applyShearYX(double angle);
        void applyShearXY(double angle);
        void applyShearXZ(double angle);
        void applyShearZX(double angle);
        void applyShearYZ(double angle);
        void applyShearZY(double angle);


};
