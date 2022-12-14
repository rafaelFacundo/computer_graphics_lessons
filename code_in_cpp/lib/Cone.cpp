#include "../include/Cone.h"

#include <math.h>
#include <iostream>
using namespace std;;

Cone::Cone():Object(){
    this->typeOfThisObject = 3;
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
    this->B_vectorIni = new Vector(x,y,z);
    this->vertice_vectorIni = this->vertice_vector;
};

void Cone::set_B_vector(Vector *B){
    this->B_vector = B;
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
    Light *light,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
){
    Vector *Light_source_position;
    Vector *intensity;
    double clds;
    Vector *Pf_Pi;
    Vector *normal;

    Vector *Dir_times_t = Direction->multiply_by_a_scalar(this->T_i);

    Vector *P_i = Eye_position->sum_with_the_vector(Dir_times_t);


    if (light->getType() == 0) {
        Pf_Pi = ((PointLight*)light)->getPosition()->minus_with_the_vector(P_i);
    }else if (light->getType() == 2) {
        Pf_Pi = ((DirectionalLight*)light)->getDirection()->multiply_by_a_scalar(-1);
    }else {
        Pf_Pi = ((SpotLight*)light)->getPosition()->minus_with_the_vector(P_i);
    }


    double Pf_pi_norm = sqrt(Pf_Pi->scalar_with(Pf_Pi));

     Vector *l_vector = new Vector(
        (Pf_Pi->get_x_Point())/Pf_pi_norm,
        (Pf_Pi->get_y_Point())/Pf_pi_norm,
        (Pf_Pi->get_z_Point())/Pf_pi_norm
    );

    if (light->getType() == 1) {
        clds = l_vector->scalar_with(((SpotLight*)light)->getDirection()->multiply_by_a_scalar(-1));
        if (clds < cos(((SpotLight*)light)->getAngle())) {
            intensity = new Vector(0.0,0.0,0.0);
        }else {
            intensity = ((SpotLight*)light)->getIntensity()->multiply_by_a_scalar(clds);
        }
    }else {
        intensity = light->getIntensity();
    };

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


    Vector* R_vector = normal->multiply_by_a_scalar(2.0 * l_vector->scalar_with(normal))->minus_with_the_vector(l_vector);


    double F_d = l_vector->scalar_with(normal);



    if (F_d < 0) {
        F_d = 0.0;
    }



    Vector *I_eye_d = intensity->at_sign_with(this->get_K_d());


    I_eye_d = I_eye_d->multiply_by_a_scalar(F_d);

    double F_e = R_vector->scalar_with(vector_v);

    if (F_e < 0) {
        F_e = 0;
    };

    F_e = pow(F_e, this->get_shiness());

    Vector *I_eye_e = intensity->at_sign_with(this->get_K_e());
    I_eye_e = I_eye_e->multiply_by_a_scalar(F_e);

    Vector *vectorWithColors = I_eye_d->sum_with_the_vector(I_eye_e);
    vectorWithColors = vectorWithColors->sum_with_the_vector(Ambient_light_intensity->at_sign_with(this->get_K_a()));

    addressToPutTheColor[0] += vectorWithColors->get_x_Point();
    addressToPutTheColor[1] += vectorWithColors->get_y_Point();
    addressToPutTheColor[2] += vectorWithColors->get_z_Point();
};

bool Cone::is_Ti_a_valid_point(Vector *P_o, Vector *Dr, double Ti){
    Vector *Dr_times_ti = Dr->multiply_by_a_scalar(Ti);
    Vector *Pi = P_o->sum_with_the_vector(Dr_times_ti);
    /* Pi_m_B = Pi_minus_B_vector  */
    Vector *Pi_m_B = Pi->minus_with_the_vector(this->get_B_vector());
    double Pi_m_b_Scalar_U = Pi_m_B->scalar_with(this->get_unitary_vector());
    //cout << Pi_m_b_Scalar_U << '\n';
    /* Vector_UpB = U_times_Pi_m_b_ScalarU  */
    Vector *Vector_UpB = this->get_unitary_vector()->multiply_by_a_scalar(Pi_m_b_Scalar_U);
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
            if (T2_lid_verif.doesIntersect && (T2_lid_verif.point_of_intersection < Ti_1)) {
                this->set_T_i(T2_lid_verif.point_of_intersection);
                result.point_of_intersection = T2_lid_verif.point_of_intersection;
                result.doesIntersect = true;
                this->setInterception(true);
            }else {
                this->set_T_i(Ti_1);
                result.point_of_intersection = Ti_1;
                result.doesIntersect = true;
                this->setInterception(false);
            }
        }else if (Ti2_verification) {
            returnType T1_lid_verif = didThePointIntercepted(dir, P_o);
            if (T1_lid_verif.doesIntersect && (T1_lid_verif.point_of_intersection < Ti_2)) {
                this->set_T_i(T1_lid_verif.point_of_intersection);
                result.point_of_intersection = T1_lid_verif.point_of_intersection;
                result.doesIntersect = true;
                this->setInterception(true);
            }else {
                this->set_T_i(Ti_2);
                result.point_of_intersection = Ti_2;
                result.doesIntersect = true;
                this->setInterception(false);
            }
        }
    }

    return result;
};

void Cone::applyRotateX(double angle){
    this->get_unitary_vector()->ThisRotateX(angle);
    Vector *newVertice = (this->get_unitary_vector()->multiply_by_a_scalar(this->get_height()))->sum_with_the_vector(this->B_vector);
    this->set_Vertice_vector(
        newVertice->get_x_Point(),
        newVertice->get_y_Point(),
        newVertice->get_z_Point()
    );
};

void Cone::applyRotateY(double angle){
    this->get_unitary_vector()->ThisRotateY(angle);
};

void Cone::applyRotateZ(double angle){
    this->get_unitary_vector()->ThisRotateZ(angle);
};

void Cone::applyTranslate(double x, double y, double z){
    this->get_Vertice_vector()->ThisTranslate(x,y,z);
    this->get_B_vector()->ThisTranslate(x,y,z);
    this->vertice_vectorIni->ThisTranslate(x,y,z);
    this->B_vectorIni->ThisTranslate(x,y,z);
};

void Cone::applyScale(double sx, double sy, double sz){
    this->set_radius(this->get_radius() * sx);
    this->set_height(this->get_height() * sx);
    Vector *newVertice = (this->get_unitary_vector()->multiply_by_a_scalar(this->get_height()))->sum_with_the_vector(this->B_vector);
    this->set_Vertice_vector(
        newVertice->get_x_Point(),
        newVertice->get_y_Point(),
        newVertice->get_z_Point()
    );
};

void Cone::applyReflectXY(){};
void Cone::applyReflectXZ(){};
void Cone::applyReflectYZ(){};

void Cone::applyShearYX(double angle){};
void Cone::applyShearXY(double angle){};
void Cone::applyShearXZ(double angle){};
void Cone::applyShearZX(double angle){};
void Cone::applyShearYZ(double angle){};
void Cone::applyShearZY(double angle){};












void Cone::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    double x = this->vertice_vectorIni->get_x_Point();
    double y = this->vertice_vectorIni->get_y_Point();
    double z = this->vertice_vectorIni->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->get_Vertice_vector()->set_x_Point(newX);
    this->get_Vertice_vector()->set_y_Point(newY);
    this->get_Vertice_vector()->set_z_Point(newZ);

    x = this->B_vectorIni->get_x_Point();
    y = this->B_vectorIni->get_y_Point();
    z = this->B_vectorIni->get_z_Point();

    newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->get_B_vector()->set_x_Point(newX);
    this->get_B_vector()->set_y_Point(newY);
    this->get_B_vector()->set_z_Point(newZ);

    Vector *newDirection = this->get_Vertice_vector()->minus_with_the_vector(this->get_B_vector());
    newDirection = newDirection->get_this_vector_unitary();
    this->unitary_vector = newDirection;

};
