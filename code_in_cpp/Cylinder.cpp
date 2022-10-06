#include "Cylinder.h"
#include <math.h>

void Cylinder::set_unitary_vector(double x, double y, double z){
    this->unitary_vector = new Vector(x,y,z);
};

void Cylinder::set_B_vector(double x, double y, double z){
    this->B_vector = new Vector(x,y,z);
};

void Cylinder::set_radius(double radius) {
    this->radius = radius;
}

double Cylinder::get_radius() {
    return this->radius;
}

Vector *Cylinder::get_unitary_vector() {
    return this->unitary_vector;
}

Vector *Cylinder::get_B_vector() {
    return this->B_vector;
}

void Cylinder::gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Vector *Light_source_position,
    Vector *Light_source_intesity,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
){

};

double Cylinder::does_the_point_intercept(Vector *dir, Vector *P_o){
    Vector *d_scalar_u = this->get_unitary_vector()->multiply_by_a_scalar(dir->scalar_with(this->get_unitary_vector()));
    Vector *w_vector = dir->minus_with_the_vector(d_scalar_u);
    Vector *Po_minus_B = P_o->minus_with_the_vector(this->get_B_vector());
    Vector *Po_minus_B_scalar_u = this->get_unitary_vector()->multiply_by_a_scalar(Po_minus_B->scalar_with(this->get_unitary_vector()));
    Vector *v_vector = Po_minus_B->minus_with_the_vector(Po_minus_B_scalar_u);


    double a = w_vector->scalar_with(w_vector);
    double b = 2 * (v_vector->scalar_with(w_vector));
    double c = v_vector->scalar_with(v_vector) - pow(this->get_radius(), 2);
};