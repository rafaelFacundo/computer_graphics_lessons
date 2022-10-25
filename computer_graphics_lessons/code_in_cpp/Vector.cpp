#include "Vector.h"

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