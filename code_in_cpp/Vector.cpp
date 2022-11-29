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


Vector* Vector::rotateX(Vector *vector, double angle) {
    return new Vector(
        vector->get_x_Point(),
        vector->get_y_Point() * cos(angle) - vector->get_z_Point() * sin(angle),
        vector->get_y_Point() * sin(angle) + vector->get_z_Point() * cos(angle)
    );
};

Vector* Vector::rotateY(Vector *vector, double angle) {
    return new Vector(
        vector->get_x_Point() * cos(angle) + vector->get_z_Point() * sin(angle),
        vector->get_y_Point(),
        -(vector->get_x_Point()) * sin(angle) + vector->get_z_Point() * cos(angle)
    );
};

Vector* Vector::rotateZ(Vector *vector, double angle) {
    return new Vector(
        vector->get_x_Point() * cos(angle) - vector->get_y_Point() * sin(angle),
        vector->get_x_Point() * sin(angle) + vector->get_y_Point() * cos(angle),
        vector->get_z_Point()
    );
};

Vector* Vector::translate(Vector *vector, double x, double y, double z) {
    return new Vector(
        vector->get_x_Point() + x,
        vector->get_y_Point() + y,
        vector->get_z_Point() + z
    );
};

Vector* Vector::scale(Vector *vector, double sx, double sy, double sz) {
    return new Vector(
        vector->get_x_Point() * sx,
        vector->get_y_Point() * sy,
        vector->get_z_Point() * sz
    );
};

Vector* Vector::reflectXY(Vector *vector){
    return new Vector(
        vector->get_x_Point(),
        vector->get_y_Point(),
        -(vector->get_z_Point())
    );
};

Vector* Vector::reflectXZ(Vector *vector){
    return new Vector(
        vector->get_x_Point(),
        -(vector->get_y_Point()),
        vector->get_z_Point()
    );
};

Vector* Vector::reflectYZ(Vector *vector){
    return new Vector(
        -(vector->get_x_Point()),
        vector->get_y_Point(),
        vector->get_z_Point()
    );
};


Vector* Vector::shearYX(Vector *vector, double angle){
    return new Vector(
        vector->get_x_Point() + vector->get_y_Point() * tan(angle),
        vector->get_y_Point(),
        vector->get_z_Point()
    );
};

Vector* Vector::shearXY(Vector *vector, double angle){
    return new Vector(
        vector->get_x_Point(),
        vector->get_y_Point() + vector->get_x_Point() * tan(angle),
        vector->get_z_Point()
    );
};

Vector* Vector::shearXZ(Vector *vector, double angle){
    return new Vector(
        vector->get_x_Point(),
        vector->get_y_Point(),
        vector->get_z_Point() + vector->get_x_Point() * tan(angle)
    );
};

Vector* Vector::shearZX(Vector *vector, double angle){
    return new Vector(
        vector->get_x_Point()  + vector->get_z_Point() * tan(angle),
        vector->get_y_Point(),
        vector->get_z_Point()
    );
};

Vector* Vector::shearYZ(Vector *vector, double angle){
    return new Vector(
        vector->get_x_Point(),
        vector->get_y_Point(),
        vector->get_z_Point() + vector->get_y_Point() * tan(angle)
    );
};

Vector* Vector::shearZY(Vector *vector, double angle){
    return new Vector(
        vector->get_x_Point(),
        vector->get_y_Point() + vector->get_z_Point() * tan(angle),
        vector->get_z_Point()
    );
};

/* Methods that modifies the values of the own vector, without return */

void Vector::rotateX(double angle){
    //this->get_x_Point(),
    this->set_y_Point(this->get_y_Point() * cos(angle) - this->get_z_Point() * sin(angle));
    this->set_z_Point(this->get_y_Point() * sin(angle) + this->get_z_Point() * cos(angle));
};
void Vector::rotateY(double angle){
    this->set_x_Point(this->get_x_Point() * cos(angle) + this->get_z_Point() * sin(angle));
    //this->get_y_Point(),
    this->set_z_Point(-(this->get_x_Point()) * sin(angle) + this->get_z_Point() * cos(angle));
};
void Vector::rotateZ(double angle){
    this->set_x_Point(this->get_x_Point() * cos(angle) - this->get_y_Point() * sin(angle));
    this->set_y_Point(this->get_x_Point() * sin(angle) + this->get_y_Point() * cos(angle));
    //vector->get_z_Point()
};
void Vector::translate(double x, double y, double z) {
    this->set_x_Point(get_x_Point() + x);
    this->set_y_Point(get_y_Point() + y);
    this->set_z_Point(get_z_Point() + z);
};
void Vector::scale(double sx, double sy, double sz){
    this->set_x_Point(get_x_Point() * sx);
    this->set_y_Point(get_y_Point() * sy);
    this->set_z_Point(get_z_Point() * sz);
};

void Vector::reflectXY(){
    //this->get_x_Point(),
    //this->get_y_Point(),
    this->set_z_Point(-(this->get_z_Point()));
};
void Vector::reflectXZ(){
    //vector->get_x_Point(),
    this->set_y_Point(-(this->get_y_Point()));
    //vector->get_z_Point()
};
void Vector::reflectYZ(){
    this->set_x_Point(-(this->get_x_Point()));
    //this->get_y_Point();
    //this->get_z_Point();
};

void Vector::shearYX(double angle){
    this->set_x_Point(this->get_x_Point() + this->get_y_Point() * tan(angle));
    //this->get_y_Point();
    //this->get_z_Point();
};
void Vector::shearXY(double angle){
    //this->get_x_Point(),
    this->set_y_Point(this->get_y_Point() + this->get_x_Point() * tan(angle));
    //this->get_z_Point()
};
void Vector::shearXZ(double angle){
    //this->get_x_Point(),
    //this->get_y_Point(),
    this->set_z_Point(this->get_z_Point() + this->get_x_Point() * tan(angle));
};
void Vector::shearZX(double angle){
    this->set_x_Point(this->get_x_Point()  + this->get_z_Point() * tan(angle));
    //this->get_y_Point(),
    //this->get_z_Point()
};
void Vector::shearYZ(double angle){
    //this->get_x_Point();
    //this->get_y_Point();
    this->set_z_Point(this->get_z_Point() + this->get_y_Point() * tan(angle));
};
void Vector::shearZY(double angle){
    //this->get_x_Point(),
    this->set_y_Point(this->get_y_Point() + this->get_z_Point() * tan(angle));
    //this->get_z_Point()
};
