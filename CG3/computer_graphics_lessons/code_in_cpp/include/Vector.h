#pragma once
#include "Vector.h"

class Vector {
    private:
        double points[3];

    public:

        Vector();

        Vector(
            double x,
            double y,
            double z
        );

        void setPoints(double x, double y, double z);
        void set_x_Point(double x);
        void set_y_Point(double y);
        void set_z_Point(double z);

        double* getPoint_s();
        double get_x_Point();
        double get_y_Point();
        double get_z_Point();
        Vector* get_this_vector_unitary();
        Vector* get_module_this_vector();
        double getNormOfThisVector();

        double scalar_with(Vector *vector);
        Vector* at_sign_with(Vector *vector);
        Vector* multiply_by_a_scalar(double scalar);
        Vector* sum_with_the_vector(Vector *vector);
        Vector* minus_with_the_vector(Vector *vector);
        Vector* vectorProductWith(Vector *vector);

        /* Methods that receive a vector and return a vector */

        Vector* rotateX(Vector *vector, double angle);
        Vector* rotateY(Vector *vector, double angle);
        Vector* rotateZ(Vector *vector, double angle);

        Vector* translate(Vector *vector, double x, double y, double z);
        Vector* scale(Vector *vector, double sx, double sy, double sz);

        Vector* reflectXY(Vector *vector);
        Vector* reflectXZ(Vector *vector);
        Vector* reflectYZ(Vector *vector);

        Vector* shearYX(Vector *vector, double angle);
        Vector* shearXY(Vector *vector, double angle);
        Vector* shearXZ(Vector *vector, double angle);
        Vector* shearZX(Vector *vector, double angle);
        Vector* shearYZ(Vector *vector, double angle);
        Vector* shearZY(Vector *vector, double angle);

        /* Methods that modifies the values of the own vector, without return */

        void ThisRotateX(double angle);
        void ThisRotateY(double angle);
        void ThisRotateZ(double angle);

        void ThisTranslate(double x, double y, double z);
        void ThisScale(double sx, double sy, double sz);

        void ThisReflectXY();
        void ThisReflectXZ();
        void ThisReflectYZ();

        void ThisShearYX(double angle);
        void ThisShearXY(double angle);
        void ThisShearXZ(double angle);
        void ThisShearZX(double angle);
        void ThisShearYZ(double angle);
        void ThisShearZY(double angle);



};
