#include "Plane.h"
#include <math.h>
#include <iostream>
using namespace std;

Plane::Plane() {

};

void Plane::set_PI_Point(double x, double y, double z){
    this->Ppi_Point = new Vector(x,y,z);
};

void Plane::set_N_vector(double x, double y, double z){
    this->N_vector = new Vector(x,y,z);
};

Vector* Plane::get_PI_Point() {
    return this->Ppi_Point;
};

Vector* Plane::get_N_vector() {
    return this->N_vector;
};

void Plane::gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Vector *Light_source_position,
    Vector *Light_source_intesity,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
) {
    double Dr_magnitude = sqrt(Direction->scalar_with(Direction));

    Vector *P_o_plus_Dir = Eye_position->sum_with_the_vector(Direction);

    Vector *P_i = P_o_plus_Dir->multiply_by_a_scalar(this->T_i);  

    Vector *Pf_Pi = new Vector(
        Light_source_position->get_x_Point() - P_i->get_x_Point(), 
        Light_source_position->get_y_Point() - P_i->get_y_Point(), 
        Light_source_position->get_z_Point() - P_i->get_z_Point() 
    );

    double Pf_pi_norm = sqrt(Pf_Pi->scalar_with(Pf_Pi));
                
    Vector *l_vector = new Vector( 
        (Pf_Pi->get_x_Point())/Pf_pi_norm, 
        (Pf_Pi->get_y_Point())/Pf_pi_norm, 
        (Pf_Pi->get_z_Point())/Pf_pi_norm 
    );

    Vector *vector_v = new Vector( 
        -(Direction->get_x_Point())/Dr_magnitude, 
        -(Direction->get_y_Point())/Dr_magnitude, 
        -(Direction->get_z_Point())/Dr_magnitude 
    );

    double F_d = l_vector->scalar_with(this->get_N_vector()); 
                
    if (F_d < 0 ) {
        F_d = 0;
    }

    Vector *I_eye_d = Light_source_intesity->at_sign_with(this->get_K_d());
    I_eye_d = I_eye_d->multiply_by_a_scalar(F_d);

    Vector* R_vector = this->get_N_vector()->multiply_by_a_scalar(2.0);
    R_vector = R_vector->multiply_by_a_scalar(F_d);
    R_vector = R_vector->minus_with_the_vector(l_vector);

    double F_e = R_vector->scalar_with(vector_v);

    if (F_e <0 ) {
        F_e = 0;
    };

    Vector *I_eye_e = Light_source_intesity->at_sign_with(this->get_K_e());
    I_eye_e = I_eye_e->multiply_by_a_scalar(F_e);

    Vector *vectorWithColors = I_eye_d->sum_with_the_vector(I_eye_e);
    vectorWithColors = vectorWithColors->sum_with_the_vector(Ambient_light_intensity);

    addressToPutTheColor[0] = vectorWithColors->get_x_Point();
    addressToPutTheColor[1] = vectorWithColors->get_y_Point();
    addressToPutTheColor[2] = vectorWithColors->get_z_Point();
    


};

double Plane::does_the_point_intercept(Vector *dir, Vector *P_o) {
    Vector* Ppi_minus_P_o = this->Ppi_Point->minus_with_the_vector(P_o);
    double Ppi_mns_Po_scalar_N = Ppi_minus_P_o->scalar_with(this->get_N_vector());
    double D_scalar_n = dir->scalar_with(this->get_N_vector());
    double T_i = Ppi_mns_Po_scalar_N / D_scalar_n;

    if ( T_i > 0 ) {
        
        this->set_T_i(T_i);
        return T_i;
    }

    return (-1.0);
};