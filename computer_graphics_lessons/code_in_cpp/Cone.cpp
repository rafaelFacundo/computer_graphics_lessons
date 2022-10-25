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

bool Cone::thisConeHaveLid(){
    return this->doesHaveLid;
};

bool Cone::thisConeHaveLid(){
    return this->doesHaveLid;
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

returnType Cone::does_the_point_intercept(Vector *dir, Vector *P_o){
    returnType result;
    double nearPoint;

    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = this->getTypeOfThisObject();

    double square_of_cosAng = pow(this->get_radius(), 2) / (pow(this->get_height(),2) + pow(this->get_radius(), 2));

    double square_of_Dir_scalar_n = pow(dir->scalar_with(this->get_unitary_vector()), 2);
    double Dir_scalar_dir_times_cosAng = (dir->scalar_with(dir)) * square_of_cosAng;
    double a = square_of_Dir_scalar_n - Dir_scalar_dir_times_cosAng;

    double vertc_scalar_dir_times_cosAng = (this->get_Vertice_vector()->scalar_with(dir)) * square_of_cosAng;
    double v_scalar_n_times_d_scalar_n = (this->get_Vertice_vector()->scalar_with(this->get_unitary_vector())) * (dir->scalar_with(this->get_unitary_vector()));
    double b = vertc_scalar_dir_times_cosAng - v_scalar_n_times_d_scalar_n;

    double square_of_vertc_scalar_unit_vec = pow(this->get_Vertice_vector()->scalar_with(this->get_unitary_vector()),2);
    double v_scalar_v_times_cosAng = (this->get_Vertice_vector()->scalar_with(this->get_Vertice_vector())) * square_of_cosAng;
    double c = square_of_vertc_scalar_unit_vec - v_scalar_v_times_cosAng;

    double delta = pow(b,2) - a*c;

    if ( a != 0 && delta >= 0 ) {
        double Ti_1 = (-b + sqrt(delta))/2*a;
        double Ti_2 = (-b - sqrt(delta))/2*a;
        bool Ti_1_verification = is_Ti_a_valid_point(P_o, dir, Ti_1);
        bool Ti_2_verification = is_Ti_a_valid_point(P_o, dir, Ti_2);
        
        if (Ti_2_verification){
            result.point_of_intersection = Ti_2;
            result.doesIntersect = false;
        }else if (Ti_1_verification && Ti_2_verification && Ti_1 > Ti_2) {
            result.point_of_intersection = Ti_2;
            result.doesIntersect = false;
        }
    }else if (delta == 0) {
        double Ti_1 = (-b + sqrt(delta))/2*a;
        result.point_of_intersection = Ti_1;
        result.doesIntersect = false;
    }

    return result;

    
};