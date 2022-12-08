#include "../include/Cylinder.h"
#include <math.h>
#include <iostream>
using namespace std;

Cylinder::Cylinder():Object(){
    this->typeOfThisObject = 2;
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

Vector *Cylinder::get_center_top_vector() {
    Vector *unitary_vector = (this->get_unitary_vector())->get_this_vector_unitary();
    return B_vector->sum_with_the_vector(unitary_vector->multiply_by_a_scalar(this->height));
}


returnType Cylinder::didThePointIntercepted(Vector *dir, Vector *P_o, Vector *base){
    returnType result;
    double D_scalar_n;
    Vector* Pi_minus_base;
    Vector *Ppi_minus_P_o = base->minus_with_the_vector(P_o);
    double Ppi_mns_Po_scalar_N = Ppi_minus_P_o->scalar_with(this->get_unitary_vector()->multiply_by_a_scalar(-1.0));

    if (base == this->get_B_vector()) {
        D_scalar_n = dir->scalar_with(this->get_unitary_vector()->multiply_by_a_scalar(-1.0));
    }else {
        D_scalar_n = dir->scalar_with(this->get_unitary_vector());
    }


    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = this->getTypeOfThisObject();

    if ( D_scalar_n == 0) {
        return result;
    }

    double T_i = Ppi_mns_Po_scalar_N / D_scalar_n;
    Vector* Pi = P_o->sum_with_the_vector(dir->multiply_by_a_scalar(T_i));

    if(base == this->get_B_vector()) {
        Pi_minus_base = Pi->minus_with_the_vector(this->get_B_vector());
    }else {
        Pi_minus_base = Pi->minus_with_the_vector(this->get_center_top_vector());
    }

    double norm = Pi_minus_base->getNormOfThisVector();

    if ( T_i > 0 && norm <= this->get_radius()) {
        this->set_T_i(T_i);
        result.point_of_intersection = T_i;
        result.doesIntersect = true;
        return result;
    }
    return result;
};

void Cylinder::putOrRemoveLid(bool put){
    this->haveLid = put;
};
void Cylinder::setInterception(bool intercept){
    this->intercepted = intercept;
};

void Cylinder::setIntercBase(bool interc){
    this->intercepBase = interc;
};
void Cylinder::setIntercLid(bool interc){
    this->intercepLid = interc;
};

void Cylinder::gime_your_color(
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

    if (this->intercepted && this->intercepBase) {
        normal = this->get_unitary_vector()->multiply_by_a_scalar(-1);
    }else if (this->intercepted && this->intercepLid) {
        normal = this->get_unitary_vector();
    }else {
        Vector *Vector_UpB = this->get_unitary_vector()->multiply_by_a_scalar(Pi_m_b_Scalar_U);

        Vector *Pi_minus_Vector_UpB = P_i->minus_with_the_vector(Vector_UpB);

        double norm_of_Pi_minus_Vector_UpB = sqrt(Pi_minus_Vector_UpB->scalar_with(Pi_minus_Vector_UpB));

        normal = Pi_minus_Vector_UpB->multiply_by_a_scalar(1/norm_of_Pi_minus_Vector_UpB);
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

    addressToPutTheColor[0] += vectorWithColors->get_x_Point();
    addressToPutTheColor[1] += vectorWithColors->get_y_Point();
    addressToPutTheColor[2] += vectorWithColors->get_z_Point();

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

    if ( Pi_m_b_Scalar_U > 0 && Pi_m_b_Scalar_U <= this->get_height()) {
        return true;
    }else {
        return false;
    };
};

returnType Cylinder::does_the_point_intercept(Vector *dir, Vector *P_o){
    returnType result;
    Vector *d_scalar_u = this->get_unitary_vector()->multiply_by_a_scalar(dir->scalar_with(this->get_unitary_vector()));
    Vector *w_vector = dir->minus_with_the_vector(d_scalar_u);
    Vector *Po_minus_B = P_o->minus_with_the_vector(this->get_B_vector());
    Vector *Po_minus_B_scalar_u = this->get_unitary_vector()->multiply_by_a_scalar(Po_minus_B->scalar_with(this->get_unitary_vector()));
    Vector *v_vector = Po_minus_B->minus_with_the_vector(Po_minus_B_scalar_u);

    double a = w_vector->scalar_with(w_vector);
    double b = 2 * (v_vector->scalar_with(w_vector));
    double c = v_vector->scalar_with(v_vector) - pow(this->get_radius(), 2);
    double delta = pow(b,2) - 4*a*c;

    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = this->getTypeOfThisObject();

    if ( delta > 0 ) {

        /* calculo os dois ti */
        double Ti_1 = (-b + sqrt(delta))/(2*a);
        double Ti_2 = (-b - sqrt(delta))/(2*a);



        bool Ti_1_verification = this->is_Ti_a_valid_point(P_o, dir, Ti_1);
        bool Ti_2_verification = this->is_Ti_a_valid_point(P_o, dir, Ti_2);

        if (Ti_1_verification && Ti_2_verification && (Ti_1 < Ti_2)) {
            result.point_of_intersection = Ti_1;
            result.doesIntersect = true;
            this->setInterception(false);
            this->setIntercBase(false);
            this->setIntercLid(false);
        }else if (Ti_1_verification && Ti_2_verification && (Ti_1 >= Ti_2)) {
            result.point_of_intersection = Ti_2;
            result.doesIntersect = true;
            this->setInterception(false);
            this->setIntercBase(false);
            this->setIntercLid(false);

        }else if (Ti_1_verification) {
            returnType T2_base = didThePointIntercepted(dir, P_o, this->get_B_vector());
            returnType T2_top = didThePointIntercepted(dir, P_o, this->get_center_top_vector());

            if (T2_base.doesIntersect && T2_base.point_of_intersection < Ti_1) {
                result.point_of_intersection = Ti_2;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(true);
                this->setIntercLid(false);
            }else if (T2_top.doesIntersect && (T2_top.point_of_intersection < Ti_1)) {
                result.point_of_intersection = Ti_2;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(false);
                this->setIntercLid(true);
            }else {
                result.point_of_intersection = Ti_1;
                result.doesIntersect = true;
                this->setInterception(false);
                this->setIntercBase(false);
                this->setIntercLid(false);
            }
        }else if (Ti_2_verification) {
            returnType T1_base = didThePointIntercepted(dir, P_o, this->get_B_vector());
            returnType T1_top = didThePointIntercepted(dir, P_o, this->get_center_top_vector());
            if (T1_base.doesIntersect && (T1_base.point_of_intersection < Ti_2)) {
                result.point_of_intersection = Ti_1;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(true);
                this->setIntercLid(false);
            }else if (T1_top.doesIntersect && (T1_top.point_of_intersection < Ti_2)) {
                result.point_of_intersection = Ti_1;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(false);
                this->setIntercLid(true);
            }else {
                result.point_of_intersection = Ti_2;
                result.doesIntersect = true;
                this->setInterception(false);
                this->setIntercBase(false);
                this->setIntercLid(false);
            }
        } else {
            returnType bse = didThePointIntercepted(dir, P_o, this->get_B_vector());
            returnType tp = didThePointIntercepted(dir, P_o, this->get_center_top_vector());
            if(bse.doesIntersect && tp.doesIntersect && (bse.point_of_intersection <= tp.point_of_intersection)) {
                result.point_of_intersection = bse.point_of_intersection;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(true);
                this->setIntercLid(false);
            }else if(bse.doesIntersect && tp.doesIntersect && (bse.point_of_intersection > tp.point_of_intersection)){
                result.point_of_intersection = tp.point_of_intersection;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(false);
                this->setIntercLid(true);
            }
        }
    }

    return result;
};


void Cylinder::applyRotateX(double angle){
    this->get_unitary_vector()->ThisRotateX(angle);
};
void Cylinder::applyRotateY(double angle){
    this->get_unitary_vector()->ThisRotateY(angle);
};
void Cylinder::applyRotateZ(double angle){
    this->get_unitary_vector()->ThisRotateZ(angle);
};

void Cylinder::applyTranslate(double x, double y, double z){
    this->get_B_vector()->ThisTranslate(x,y,z);

};

void Cylinder::applyScale(double sx, double sy, double sz){
    this->set_radius(this->get_radius() * sx);
    this->set_height(this->get_height() * sx);
};

void Cylinder::applyReflectXY(){};
void Cylinder::applyReflectXZ(){};
void Cylinder::applyReflectYZ(){};

void Cylinder::applyShearYX(double angle){};
void Cylinder::applyShearXY(double angle){};
void Cylinder::applyShearXZ(double angle){};
void Cylinder::applyShearZX(double angle){};
void Cylinder::applyShearYZ(double angle){};
void Cylinder::applyShearZY(double angle){};



void Cylinder::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
    Vector *top_vector = this->get_center_top_vector();

    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    double x = this->get_B_vector()->get_x_Point();
    double y = this->get_B_vector()->get_y_Point();
    double z = this->get_B_vector()->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->get_B_vector()->set_x_Point(newX);
    this->get_B_vector()->set_y_Point(newY);
    this->get_B_vector()->set_z_Point(newZ);

    x = top_vector-> get_x_Point();
    y = top_vector-> get_y_Point();
    z = top_vector-> get_z_Point();

    newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    top_vector->set_x_Point(newX);
    top_vector->set_y_Point(newY);
    top_vector->set_z_Point(newZ);

    Vector *newUni = top_vector->minus_with_the_vector(this->get_B_vector());
    newUni = newUni->get_this_vector_unitary();
    this->unitary_vector = newUni;


};
