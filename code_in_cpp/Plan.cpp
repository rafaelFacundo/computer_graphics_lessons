#include "Plan.h"
#include <math.h>
#include <iostream>
using namespace std;

Plan::Plan() {

};

void Plan::set_PI_Point(double x, double y, double z){
    this->Ppi_Point = new Vector(x,y,z);
};

void Plan::set_N_vector(double x, double y, double z){
    this->N_vector = new Vector(x,y,z);
};

Vector* Plan::get_PI_Point() {
    return this->Ppi_Point;
};

Vector* Plan::get_N_vector() {
    return this->N_vector;
};

void Plan::gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Vector *Light_source_position,
    Vector *Light_source_intesity,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
) {
    Vector *Dir_times_t = Direction->multiply_by_a_scalar(this->T_i);

    Vector *P_i = Eye_position->sum_with_the_vector(Dir_times_t);

    Vector *Pf_Pi = Light_source_position->minus_with_the_vector(P_i);

    double Pf_pi_norm = sqrt(Pf_Pi->scalar_with(Pf_Pi));
                
    Vector *l_vector = new Vector( 
        (Pf_Pi->get_x_Point())/Pf_pi_norm, 
        (Pf_Pi->get_y_Point())/Pf_pi_norm, 
        (Pf_Pi->get_z_Point())/Pf_pi_norm 
    );

    double Dr_magnitude = sqrt(Direction->scalar_with(Direction));
    Vector *vector_v = new Vector( 
        -(Direction->get_x_Point())/Dr_magnitude, 
        -(Direction->get_y_Point())/Dr_magnitude, 
        -(Direction->get_z_Point())/Dr_magnitude 
    );

    double l_scalar_normal = 2 * (l_vector->scalar_with(this->get_N_vector()));
    Vector *nomal_scalar_with_above = this->get_N_vector()->multiply_by_a_scalar(l_scalar_normal);
    Vector *R_vector = nomal_scalar_with_above->minus_with_the_vector(l_vector);

    double F_d = l_vector->scalar_with(this->get_N_vector()); 
                
    if (F_d < 0 ) {
        F_d = 0;
    }

    double F_e = R_vector->scalar_with(vector_v);

    if (F_e < 0 ) {
        F_e = 0;
    };

    F_e = pow(F_e, this->get_shiness());

    Vector *I_eye_e = Light_source_intesity->at_sign_with(this->get_K_e());
    I_eye_e = I_eye_e->multiply_by_a_scalar(F_e);

    Vector *I_eye_d = Light_source_intesity->at_sign_with(this->get_K_d());
    I_eye_d = I_eye_d->multiply_by_a_scalar(F_d);

    Vector *vectorWithColors = I_eye_d->sum_with_the_vector(I_eye_e);
    vectorWithColors = vectorWithColors->sum_with_the_vector(Ambient_light_intensity->at_sign_with(this->get_K_a()));


    addressToPutTheColor[0] = vectorWithColors->get_x_Point() * 255;
    addressToPutTheColor[1] = vectorWithColors->get_y_Point() * 255;
    addressToPutTheColor[2] = vectorWithColors->get_z_Point() * 255;


};

returnType Plan::does_the_point_intercept(Vector *dir, Vector *P_o) {
    returnType result;
    Vector* Ppi_minus_P_o = this->Ppi_Point->minus_with_the_vector(P_o);
    double Ppi_mns_Po_scalar_N = Ppi_minus_P_o->scalar_with(this->get_N_vector());
    double D_scalar_n = dir->scalar_with(this->get_N_vector());
    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = this->getTypeOfThisObject();
    if ( D_scalar_n == 0 ) {
        return result;
    }
    double T_i = Ppi_mns_Po_scalar_N / D_scalar_n;
    if ( T_i > 0 ) {
        this->set_T_i(T_i);
        result.point_of_intersection = T_i;
        result.doesIntersect = true;
        return result;
    }
    return result;
};