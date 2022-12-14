#pragma once
#include "Objects.h"
#include "Vector.h"

class Cylinder : public Object {
    Vector *unitary_vector;
    Vector *B_vector;
    Vector *B_vectorIni;
    Vector *top_ini;

    double height;
    double radius;
    bool haveLid = false;
    bool intercepted = false;
    bool intercepBase = false;
    bool intercepLid = false;


    public:
        void set_B_vector(double x, double y, double z);
        void set_unitary_vector(double x, double y, double z);
        void set_radius(double radius);
        void set_height(double height);
        void putOrRemoveLid(bool put);
        void setInterception(bool intercept);
        void setIntercBase(bool interc);
        void setIntercLid(bool interc);
        double get_radius();
        double get_height();
        Vector* get_unitary_vector();
        Vector* get_B_vector();
        Vector* get_center_top_vector();
        returnType didThePointIntercepted(Vector *dir, Vector *P_o, Vector *base);
        Cylinder();


        bool is_Ti_a_valid_point(Vector *P_o, Vector *Dr, double Ti);

        void gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Light *light,
            Vector *Ambient_light_intensity,
            double *addressToPutTheColor
        );

        returnType does_the_point_intercept(Vector *dir, Vector *P_o);

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

        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);

};
