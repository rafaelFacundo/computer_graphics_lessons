#include "Vector.h"
#include <math.h>

void Vector::setPoints(double x, double y, double z) {
    this->points[0] = x;
    this->points[1] = y;
    this->points[2] = z;
}

void Vector::set_x_Point(double x){
    this->points[0] = x;
};

void Vector::set_y_Point(double y){
    this->points[1] = y;
};

void Vector::set_z_Point(double z){
    this->points[2] = z;
};

double Vector::get_x_Point(){
    return this->points[0];
};

double Vector::get_y_Point(){
    return this->points[1];
};

double Vector::get_z_Point(){
    return this->points[2];
};

double* Vector::getPoint_s() {
    return this->points;
};

/*
    a[1] * b[2] - a[2] * b[1],
    a[2] * b[0] - a[0] * b[2],
    a[0] * b[1] - a[1] * b[0]
 */

Vector* Vector::vectorProductWith(Vector *vector) {
    Vector *result = new Vector(
        this->get_y_Point()*vector->get_z_Point() - this->get_z_Point()*vector->get_y_Point(),
        this->get_z_Point()*vector->get_x_Point() - this->get_x_Point()*vector->get_z_Point(),
        this->get_x_Point()*vector->get_y_Point() - this->get_y_Point()*vector->get_x_Point()
    );

    return result;
};

double Vector::getNormOfThisVector(){
    double scalar = this->scalar_with(this);
    return sqrt(scalar);
};

Vector* Vector::get_this_vector_unitary(){
    double norm = this->getNormOfThisVector();
    return this->multiply_by_a_scalar(1/norm);

    /* if (module->get_x_Point() != 0){
        result->set_x_Point(this->get_x_Point() / module->get_x_Point());
    }
    else{
        result->set_x_Point(0);
    }

    if (module->get_y_Point() != 0){
        result->set_y_Point(this->get_y_Point() / module->get_y_Point());
    }
    else{
        result->set_y_Point(0);
    }

    if (module->get_z_Point() != 0){
        result->set_z_Point(this->get_z_Point() / module->get_z_Point());
    }
    else{
        result->set_z_Point(0);
    }
    return result; */
};

Vector* Vector::get_module_this_vector(){
    Vector* result = new Vector();
    /* Vector* squared = this->at_sign_with(this);
    result->set_x_Point(sqrt(squared->get_x_Point()));
    result->set_y_Point(sqrt(squared->get_y_Point()));
    result->set_z_Point(sqrt(squared->get_z_Point())); */
    double scalar = result->scalar_with(result);
    return result;
};



double Vector::scalar_with(Vector *vector) {
    double* vectorPoints = vector->getPoint_s();
    double result = (this->points[0] * vectorPoints[0]) + (this->points[1] * vectorPoints[1]) + (this->points[2] * vectorPoints[2]);
    return result;
};

Vector* Vector::at_sign_with(Vector *vector){
    Vector* result = new Vector();
    result->set_x_Point(this->get_x_Point() * vector->get_x_Point());
    result->set_y_Point(this->get_y_Point() * vector->get_y_Point());
    result->set_z_Point(this->get_z_Point() * vector->get_z_Point());
    return result;
};

Vector* Vector::multiply_by_a_scalar(double scalar) {
    Vector* result = new Vector();
    result->set_x_Point(this->get_x_Point() * scalar);
    result->set_y_Point(this->get_y_Point() * scalar);
    result->set_z_Point(this->get_z_Point() * scalar);
    return result;
};

Vector* Vector::sum_with_the_vector(Vector *vector){
    Vector* result = new Vector();
    result->set_x_Point(this->get_x_Point() + vector->get_x_Point());
    result->set_y_Point(this->get_y_Point() + vector->get_y_Point());
    result->set_z_Point(this->get_z_Point() + vector->get_z_Point());
    return result;
};

Vector* Vector::minus_with_the_vector(Vector *vector){
    Vector* result = new Vector();
    result->set_x_Point(this->get_x_Point() - vector->get_x_Point());
    result->set_y_Point(this->get_y_Point() - vector->get_y_Point());
    result->set_z_Point(this->get_z_Point() - vector->get_z_Point());
    return result;
};

Vector::Vector( double x, double y, double z ) {
    this->setPoints(x,y,z);
};

Vector::Vector() {
    this->setPoints(0.0,0.0,0.0);
}
