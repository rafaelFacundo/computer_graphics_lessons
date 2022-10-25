#include "Objects.h"
#include <math.h>

void Object::set_Center_of_Object(double center[3]) {
    this->center_Of_Object = new Vector(center[0], center[1], center[2]);
    /* this->center_Of_Object->setPoints(center[0], center[1], center[2]); */
};

void Object::set_K_e(double K_e[3]) { 
    this->K_e_of_object = new Vector(K_e[0], K_e[1], K_e[2]);
    /* this->K_e_of_object->setPoints(K_e[0], K_e[1], K_e[2]); */
};

void Object::set_K_d(double K_d[3]) {
    this->K_d_of_object = new Vector(K_d[0], K_d[1], K_d[2]);
};

void Object::set_K_a(double K_a[3]) {
    this->K_a_Of_object = new Vector(K_a[0], K_a[1], K_a[2]);
    /* this->K_d_of_object->setPoints(K_d[0], K_d[1], K_d[2]); */
};

void Object::set_shine(double shine) {
    this->shineness_of_object = shine;
};

void Object::set_T_i(double point) {
    this->T_i = point;
};

Vector* Object::get_K_e(){
    return this->K_e_of_object;
};

Vector* Object::get_K_d(){
    return this->K_e_of_object;
};

Vector* Object::get_K_a() {
    return this->K_a_Of_object;
};

double Object::get_shiness(){
    return this->shineness_of_object;
};

int Object::getTypeOfThisObject(){
    return this->typeOfThisObject;
};

Object::Object(){
    
}

Object::Object(
    double center[3],
    double K_e[3],
    double K_d[3],
    double shine,
    double radius
) {};

/* get methods */

double* Object::get_center() {
    return this->center_Of_Object->getPoint_s();
}
/* 
    Method that checks if the point intercept the object
    this method it's diferent in each type of object
*/

int Object::teste () {
    return 2;
};

Vector *Object::get_Pi(Vector *Direction, Vector *Eye_position) {
    Vector *Dir_times_t = Direction->multiply_by_a_scalar(this->T_i);
    Vector *P_i = Eye_position->sum_with_the_vector(Dir_times_t);
    return P_i;
}

Vector *Object::get_L_vector(
    Vector *Direction,
    Vector *Eye_position,
    Vector *Light_source_position
){
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
    return l_vector;
};

void Object::gimme_your_ambientColor(Vector *Ambient_light_intensity, double *addressToPutTheColor){
    Vector *vectorWithColors = Ambient_light_intensity->at_sign_with(this->get_K_a());
    addressToPutTheColor[0] = vectorWithColors->get_x_Point() * 255;
    addressToPutTheColor[1] = vectorWithColors->get_y_Point() * 255;
    addressToPutTheColor[2] = vectorWithColors->get_z_Point() * 255;
};