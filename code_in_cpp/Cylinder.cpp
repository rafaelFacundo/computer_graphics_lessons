#include "Cylinder.h"
#include <math.h>
#include <iostream>
using namespace std;

Cylinder::Cylinder():Object(){

}

void Cylinder::set_unitary_vector(double x, double y, double z){
    this->unitary_vector = new Vector(x,y,z);
};

void Cylinder::set_B_vector(double x, double y, double z){
    this->B_vector = new Vector(x,y,z);
};

void Cylinder::set_radius(double radius) {
    this->radius = radius;
}

void Cylinder::set_height(double height) {
    this->height = height;
}

double Cylinder::get_radius() {
    return this->radius;
}

double Cylinder::get_height() {
    return this->height;
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

    addressToPutTheColor[0] = 250.0;
    addressToPutTheColor[1] = 109.0;
    addressToPutTheColor[2] = 253.0;
    

};

bool Cylinder::is_Ti_a_valid_point(Vector *P_o, Vector *Dr, double Ti) {
    Vector *Dr_times_ti = Dr->multiply_by_a_scalar(Ti);
    Vector *Pi = P_o->sum_with_the_vector(Dr_times_ti);

    /* Pi_m_B = Pi_minus_B_vector  */
    Vector *Pi_m_B = Pi->minus_with_the_vector(this->get_B_vector());
    double Pi_m_b_Scalar_U = Pi_m_B->scalar_with(this->get_unitary_vector());

    /* Vector_UpB = U_times_Pi_m_b_ScalarU  */
    Vector *Vector_UpB = this->get_unitary_vector()->multiply_by_a_scalar(Pi_m_b_Scalar_U);
    double norm_of_Vector_UpB = sqrt(Vector_UpB->scalar_with(Vector_UpB));

    if ( norm_of_Vector_UpB > 0 && norm_of_Vector_UpB < this->get_height()) {
        return true;
    }else {
        return false;
    };
};

double Cylinder::does_the_point_intercept(Vector *dir, Vector *P_o){
    Vector *d_scalar_u = this->get_unitary_vector()->multiply_by_a_scalar(dir->scalar_with(this->get_unitary_vector()));
    Vector *w_vector = dir->minus_with_the_vector(d_scalar_u);
    Vector *Po_minus_B = P_o->minus_with_the_vector(this->get_B_vector());
    Vector *Po_minus_B_scalar_u = this->get_unitary_vector()->multiply_by_a_scalar(Po_minus_B->scalar_with(this->get_unitary_vector()));
    Vector *v_vector = Po_minus_B->minus_with_the_vector(Po_minus_B_scalar_u);
    double nearPoint;

    double a = w_vector->scalar_with(w_vector);
    double b = 2 * (v_vector->scalar_with(w_vector));
    double c = v_vector->scalar_with(v_vector) - pow(this->get_radius(), 2);
    double delta = pow(b,2) - 4*a*c;

    if ( delta > 0 ) {

        /* calculo os dois ti */
        double Ti_1 = (-b + sqrt(delta))/(2*a);
        double Ti_2 = (-b - sqrt(delta))/(2*a);
        
        if ( Ti_1 < Ti_2 ) {
            nearPoint = Ti_1;
        }else {
            nearPoint = Ti_2;
        }

        

        bool Ti_1_verification = this->is_Ti_a_valid_point(P_o, dir, Ti_1);
        bool Ti_2_verification = this->is_Ti_a_valid_point(P_o, dir, Ti_2);
        
        if (Ti_1_verification == true && Ti_2_verification == false) {
                return Ti_1;
        }else if (Ti_1_verification == false && Ti_2_verification == true) {
                return Ti_2;
        }else if (Ti_1_verification == true && Ti_2_verification == true) {
                return nearPoint;
        }else {
                return (-1.0);
        };
    
    }else {
        return (-1.0);
    };
};