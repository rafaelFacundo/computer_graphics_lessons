#include "Objects.h"

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