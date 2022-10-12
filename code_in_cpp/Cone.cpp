#include "Cone.h"
#include <math.h>
#include <iostream>
using namespace std;;

Cone::Cone():Object(){

};

void Cone::set_unitary_vector(double x, double y, double z){
    this->unitary_vector = new Vector(x,y,z);
};

void Cone::set_B_vector(double x, double y, double z){
    this->B_vector = new Vector(x,y,z);
};

void Cone::set_Vertice_vector(double x, double y, double z){
    this->vertice_vector = new Vector(x,y,z);
};

void Cone::set_radius(double radius) {
    this->radius = radius;
}

void Cone::set_height(double height) {
    this->height = height;
}

void Cone::set_angle(double angle){
    this->angle = angle;
};

double Cone::get_radius() {
    return this->radius;
}

double Cone::get_height() {
    return this->height;
}

double Cone::get_angle(){
    return this->angle;
};

Vector *Cone::get_unitary_vector() {
    return this->unitary_vector;
}

Vector *Cone::get_B_vector() {
    return this->B_vector;
}

Vector* Cone::get_Vertice_vector(){
    return this->vertice_vector;
};

void Cone::gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Vector *Light_source_position,
    Vector *Light_source_intesity,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
) {
    addressToPutTheColor[0] = 240;
    addressToPutTheColor[1] = 28;
    addressToPutTheColor[2] = 28;
};

bool Cone::is_Ti_a_valid_point(Vector *P_o, Vector *Dr, double Ti){
    Vector *Dr_times_ti = Dr->multiply_by_a_scalar(Ti);
    Vector *Pi = P_o->sum_with_the_vector(Dr_times_ti);
    /* Pi_m_B = Pi_minus_B_vector  */
    Vector *Pi_m_B = Pi->minus_with_the_vector(this->get_B_vector());
    double Pi_m_b_Scalar_U = Pi_m_B->scalar_with(this->get_unitary_vector());

    /* Vector_UpB = U_times_Pi_m_b_ScalarU  */
    Vector *Vector_UpB = this->get_unitary_vector()->multiply_by_a_scalar(Pi_m_b_Scalar_U);
    double norm_of_Vector_UpB = sqrt(Vector_UpB->scalar_with(Vector_UpB));

    if ( Pi_m_b_Scalar_U > 0 && Pi_m_b_Scalar_U < this->get_height()) {
        return true;
    }else {
        return false;
    };
};

double Cone::does_the_point_intercept(Vector *dir, Vector *P_o){
    double nearPoint;
    Vector *little_v_vector = vertice_vector->minus_with_the_vector(P_o);
    double square_of_cos = pow(cos(this->get_angle()), 2);

    /* A */
    double square_of_dir_scalar_unit_vector = pow(dir->scalar_with(this->get_unitary_vector()), 2);
    double Dir_scalar_dir_times_square_of_cos = dir->scalar_with(dir) * square_of_cos;
    double a = square_of_dir_scalar_unit_vector - Dir_scalar_dir_times_square_of_cos;

    /* B */
    double v_scalar_dr_times_square_of_cos = little_v_vector->scalar_with(dir) * square_of_cos;
    /* (v scalar n) x (dir scalar n ) = v_sc_n_times_dir_sc_n */
    double v_sc_n_times_dir_sc_n = little_v_vector->scalar_with(this->get_unitary_vector()) * dir->scalar_with(this->get_unitary_vector());
    double b = v_scalar_dr_times_square_of_cos - v_sc_n_times_dir_sc_n;

    /* C */
    double v_scalar_unitary_vector = pow(little_v_vector->scalar_with(this->get_unitary_vector()), 2);
    double v_scalar_v_times_square_of_cos = little_v_vector->scalar_with(little_v_vector) * square_of_cos;
    double c = v_scalar_unitary_vector - v_scalar_v_times_square_of_cos;

    double delta = pow(b, 2) - 4*a*c;

    if (delta > 0) {
        double Ti_1 = (-b + sqrt(delta))/(2*a);
        double Ti_2 = (-b - sqrt(delta))/(2*a);
        
        cout << "valor Ti1: " << Ti_1 << '\n';
        cout << "Valor Ti2: " << Ti_2 << '\n';

        
        bool Ti_1_verification = is_Ti_a_valid_point(P_o, dir, Ti_1);
        bool Ti_2_verification = is_Ti_a_valid_point(P_o, dir, Ti_2);

        cout << "verificação Ti1: " << Ti_1_verification << '\n';
        cout << "Verificação Ti2: " << Ti_2_verification << '\n';
        

        if ( Ti_1 < Ti_2 ) {
            nearPoint = Ti_1;
        }else {
            nearPoint = Ti_2;
        }



        if (Ti_1_verification) {
            cout << "asdasdd\n";
            if (Ti_2_verification) {
                return nearPoint;
            }
            return Ti_1;
        }else if (Ti_2_verification){
            cout << "abbbbbbbd\n";
            return Ti_2;
        }else {

            return (-1.0);
        }
    }else {
        cout << delta << '\n';
        return (-1.0);
    }
};