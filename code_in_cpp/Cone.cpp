#include "Cone.h"
#include <math.h>
#include <iostream>
using namespace std;;

Cone::Cone():Object(){

};

void Cone::putOrRemoveLid(bool put){
    this->haveLid = put;
};
void Cone::setInterception(bool intercept){
    this->intercepted = intercept;
};

void Cone::set_direction_vector(double x, double y, double z){
    this->direction_vector = new Vector(x,y,z);
    this->unitary_vector = direction_vector->get_this_vector_unitary();
};

void Cone::set_B_vector(double x, double y, double z){
    this->B_vector = new Vector(x,y,z);
    this->vertice_vector = B_vector->sum_with_the_vector(unitary_vector->multiply_by_a_scalar(this->height));
};

void Cone::set_B_vector(Vector *B){
    this->B_vector = B;

    //cout  << (this->B_vector)->get_x_Point() << '\n';
    //cout  << (this->B_vector)->get_y_Point() << '\n';
    //cout  << (this->B_vector)->get_z_Point() << '\n';

    this->vertice_vector = B_vector->sum_with_the_vector(unitary_vector->multiply_by_a_scalar(this->height));
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

double Cone::get_radius() {
    return this->radius;
}

double Cone::get_height() {
    return this->height;
}

Vector *Cone::get_direction_vector() {
    return this->direction_vector;
}

Vector *Cone::get_unitary_vector() {
    return this->unitary_vector;
}

Vector *Cone::get_B_vector() {
    return this->B_vector;
}

Vector* Cone::get_Vertice_vector(){
    return this->vertice_vector;
};

Vector* Cone::getTop(){
    return (this->get_unitary_vector()->multiply_by_a_scalar(this->get_height()))->sum_with_the_vector(this->B_vector);
};

void Cone::gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Vector *Light_source_position,
    Vector *Light_source_intesity,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
){
    Vector *normal;

    Vector *Dir_times_t = Direction->multiply_by_a_scalar(this->T_i);

    Vector *P_i = Eye_position->sum_with_the_vector(Dir_times_t);

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

    Vector *Pi_m_B = P_i->minus_with_the_vector(this->get_B_vector());
    double Pi_m_b_Scalar_U = Pi_m_B->scalar_with(this->get_unitary_vector());
    /* ================================================================================= */
    /* Vector_UpB = U_times_Pi_m_b_ScalarU  */

    Vector *Vector_UpB = this->get_unitary_vector()->multiply_by_a_scalar(Pi_m_b_Scalar_U);

    Vector *Pi_minus_Vector_UpB = P_i->minus_with_the_vector(Vector_UpB);

    double norm_of_Pi_minus_Vector_UpB = sqrt(Pi_minus_Vector_UpB->scalar_with(Pi_minus_Vector_UpB));



    if (this->intercepted) {
        normal = this->get_unitary_vector()->multiply_by_a_scalar(-1);
        
    }else {
        Vector *top_minus_pi = this->getTop()->minus_with_the_vector(P_i);
        Vector *Top_minus_pi_vecProd_Direc = top_minus_pi->vectorProductWith(this->get_unitary_vector());
        normal = (Top_minus_pi_vecProd_Direc->vectorProductWith(top_minus_pi))->get_this_vector_unitary();
    }



    double dr_nom = sqrt(Direction->scalar_with(Direction));
    Vector *vector_v = new Vector(
        -(Direction->get_x_Point())/dr_nom,
        -(Direction->get_y_Point())/dr_nom,
        -(Direction->get_z_Point())/dr_nom
    );


    Vector* R_vector = normal->multiply_by_a_scalar(2.0);
    R_vector = R_vector->multiply_by_a_scalar(l_vector->scalar_with(normal));
    R_vector = R_vector->minus_with_the_vector(l_vector);

    double F_d = l_vector->scalar_with(normal);

    if (F_d < 0 ) {
        F_d = 0.0;
    }

    Vector *I_eye_d = Light_source_intesity->at_sign_with(this->get_K_d());
    I_eye_d = I_eye_d->multiply_by_a_scalar(F_d);

    double F_e = R_vector->scalar_with(vector_v);

    if (F_e <0 ) {
        F_e = 0;
    };

    F_e = pow(F_e, this->get_shiness());

    Vector *I_eye_e = Light_source_intesity->at_sign_with(this->get_K_e());
    I_eye_e = I_eye_e->multiply_by_a_scalar(F_e);

    Vector *vectorWithColors = I_eye_d->sum_with_the_vector(I_eye_e);
    vectorWithColors = vectorWithColors->sum_with_the_vector(Ambient_light_intensity->at_sign_with(this->get_K_a()));

    addressToPutTheColor[0] = vectorWithColors->get_x_Point() * 255;
    addressToPutTheColor[1] = vectorWithColors->get_y_Point() * 255;
    addressToPutTheColor[2] = vectorWithColors->get_z_Point() * 255;
};

bool Cone::is_Ti_a_valid_point(Vector *P_o, Vector *Dr, double Ti){
    Vector *Dr_times_ti = Dr->multiply_by_a_scalar(Ti);
    Vector *Pi = P_o->sum_with_the_vector(Dr_times_ti);
    /* Pi_m_B = Pi_minus_B_vector  */
    Vector *Pi_m_B = Pi->minus_with_the_vector(this->get_B_vector());
    double Pi_m_b_Scalar_U = Pi_m_B->scalar_with(this->get_direction_vector());
    //cout << Pi_m_b_Scalar_U << '\n';
    /* Vector_UpB = U_times_Pi_m_b_ScalarU  */
    Vector *Vector_UpB = this->get_direction_vector()->multiply_by_a_scalar(Pi_m_b_Scalar_U);
    if ( Pi_m_b_Scalar_U >= 0 && Pi_m_b_Scalar_U <= this->get_height()) {

        return true;
    }else {
        return false;
    };
};

returnType Cone::didThePointIntercepted(Vector *dir, Vector *P_o) {
    returnType result;
    Vector *Ppi_minus_P_o = this->get_B_vector()->minus_with_the_vector(P_o);
    double Ppi_mns_Po_scalar_N = Ppi_minus_P_o->scalar_with(this->get_unitary_vector()->multiply_by_a_scalar(-1.0));
    double D_scalar_n = dir->scalar_with(this->get_unitary_vector()->multiply_by_a_scalar(-1.0));

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

returnType Cone::does_the_point_intercept(Vector *dir, Vector *P_o){
    returnType result;
    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = this->getTypeOfThisObject();


    this->cos_angle = pow(this->height,2)/(pow(this->height,2) + pow(this->radius,2));
    double nearPoint;
    bool Ti_verification = false;
    Vector *little_v_vector = this->vertice_vector->minus_with_the_vector(P_o);
    double square_of_cos = this->cos_angle;

    //cout << cos(this->get_angle()) << '\n';

    /* A */
    double square_of_dir_scalar_unit_vector = pow(dir->scalar_with(this->get_unitary_vector()), 2);
    double Dir_scalar_dir_times_square_of_cos = dir->scalar_with(dir) * this->cos_angle;
    double a = square_of_dir_scalar_unit_vector - Dir_scalar_dir_times_square_of_cos;

    /* B */
    double v_scalar_dr_times_square_of_cos = little_v_vector->scalar_with(dir) * this->cos_angle;
    /* (v scalar n) x (dir scalar n ) = v_sc_n_times_dir_sc_n */
    double v_sc_n_times_dir_sc_n = little_v_vector->scalar_with(this->get_unitary_vector()) * dir->scalar_with(this->get_unitary_vector());
    double b = 2*(v_scalar_dr_times_square_of_cos - v_sc_n_times_dir_sc_n);

    /* C */
    double v_scalar_unitary_vector = pow(little_v_vector->scalar_with(this->get_unitary_vector()), 2);
    double v_scalar_v_times_square_of_cos = little_v_vector->scalar_with(little_v_vector) * this->cos_angle;
    double c = v_scalar_unitary_vector - v_scalar_v_times_square_of_cos;

    double delta = pow(b, 2) - 4*a*c;

    if (delta > 0) {
        double Ti_1 = (-b + sqrt(delta))/ (2*a);
        double Ti_2 = (-b - sqrt(delta))/ (2*a);

        bool Ti1_verification = is_Ti_a_valid_point(P_o, dir, Ti_1);
        bool Ti2_verification = is_Ti_a_valid_point(P_o, dir, Ti_2);

        if ( Ti1_verification && Ti2_verification && Ti_1 < Ti_2 ) {
            this->set_T_i(Ti_1);
            result.point_of_intersection = Ti_1;
            result.doesIntersect = true;
            this->setInterception(false);
        }else if ( Ti1_verification && Ti2_verification && Ti_1 >= Ti_2 ) {
            this->set_T_i(Ti_2);
            result.point_of_intersection = Ti_2;
            result.doesIntersect = true;
            this->setInterception(false);
        } else if ( Ti1_verification) {
            returnType T2_lid_verif = didThePointIntercepted(dir, P_o);
            if (T2_lid_verif.doesIntersect && (T2_lid_verif.point_of_intersection <= Ti_1)) {
                result.point_of_intersection = Ti_2;
                result.doesIntersect = true;
                this->setInterception(true);
            }else {
                result.point_of_intersection = Ti_1;
                result.doesIntersect = true;
                this->setInterception(false);
            }
        }else if (Ti2_verification) {
            returnType T1_lid_verif = didThePointIntercepted(dir, P_o);
            if (T1_lid_verif.doesIntersect && (T1_lid_verif.point_of_intersection <= Ti_2)) {
                result.point_of_intersection = Ti_1;
                result.doesIntersect = true;
                this->setInterception(true);
            }else {
                result.point_of_intersection = Ti_2;
                result.doesIntersect = true;
                this->setInterception(false);
            }
        }




    }
    return result;
};
