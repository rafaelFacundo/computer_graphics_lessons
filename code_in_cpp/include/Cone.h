#pragma once
#include "Objects.h"

class Cone : public Object {
    private:
        Vector *vertice_vector;
        Vector *direction_vector;
        Vector *B_vectorIni;
        Vector *vertice_vectorIni;
        Vector *unitary_vector;

        Vector *B_vector;

        double height;
        double radius;
        double cos_angle;
        bool haveLid = false;
        bool intercepted = false;

    public:
        void set_B_vector(double x, double y, double z);
        void set_B_vector(Vector *B);
        void set_direction_vector(double x, double y, double z);
        void set_Vertice_vector(double x, double y, double z);
        void set_radius(double radius);
        void set_height(double height);
        void set_angle(double angle);
        double get_radius();
        double get_height();
        double get_angle();
        Vector* getTop();
        Vector* get_direction_vector();
        Vector* get_unitary_vector();
        Vector* get_B_vector();
        Vector* get_Vertice_vector();
        returnType didThePointIntercepted(Vector *dir, Vector *P_o);
        void putOrRemoveLid(bool put);
        void setInterception(bool intercept);
        Cone();

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
