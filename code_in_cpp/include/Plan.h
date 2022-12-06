#pragma once
#include "Objects.h"
#include "Vector.h"
#include "TextureImage.h"
#include <string>
#include <iostream>
using namespace std;

class Plan : public Object {
    private:
        string TextureImg = NULL;
        Vector* Ppi_Point;
        Vector* N_vector;
    public:

    Plan();

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

    returnType does_the_point_intercept(Vector *dir, Vector *P_o) ;

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

    void set_TextureImage(string filename);

};
