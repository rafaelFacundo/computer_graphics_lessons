#include "Objects.h"

void Object::set_Center_of_Object(double center[3]) {
    this->center_Of_Object->setPoints(center[0], center[1], center[2]);
};

void Object::set_K_e(double K_e[3]) { 
    this->K_e_of_object->setPoints(K_e[0], K_e[1], K_e[2]);
};

void Object::set_K_d(double K_d[3]) {
    this->K_d_of_object->setPoints(K_d[0], K_d[1], K_d[2]);
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

Object::Object(){
    
}

/* get methods */

double* Object::get_center() {
    return this->center_Of_Object->getPoint_s();
}
/* 
    Method that checks if the point intercept the object
    this method it's diferent in each type of object
*/
