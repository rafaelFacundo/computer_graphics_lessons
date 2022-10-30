#pragma once
#include "Vector.h"

class Vector {
    private:
        double points[3];

    public:
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

        double scalar_with(Vector *vector);

        Vector* at_sign_with(Vector *vector);

        Vector* multiply_by_a_scalar(double scalar);

        Vector* sum_with_the_vector(Vector *vector);

        Vector* minus_with_the_vector(Vector *vector);

        Vector* vectorProductWith(Vector *vector);

        double getNormOfThisVector();

        Vector();

        Vector(
            double x,
            double y,
            double z
        );
};
