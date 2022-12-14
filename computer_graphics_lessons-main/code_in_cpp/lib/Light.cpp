#include "../include/Light.h"

Light::Light(){};
void Light::setIntesity(Vector *intesity){
    this->intesity = intesity;
};
void Light::setType(int type){
    this->type = type;
};
void Light::turnOnOrTurnOff(bool switcher){
    this->isActive = switcher;
};
Vector* Light::getIntensity(){
    return this->intesity;
};
int Light::getType(){
    return this->type;
};
bool Light::active(){
    return this->isActive;
};

Vector *Light::calculateWordToCanvas(Vector *P_o, Vector *P_Look, Vector *Up, Vector *worldVector){
    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    double x = worldVector->get_x_Point();
    double y = worldVector->get_y_Point();
    double z = worldVector->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    return new Vector(newX, newY, newZ);
};


/* Direcional */

void DirectionalLight::setDirection(Vector *direction){
    this->direction = direction->get_this_vector_unitary();
    this->directionIni = new Vector(
        this->direction->get_x_Point(),
        this->direction->get_y_Point(),
        this->direction->get_z_Point()
    );
};
Vector* DirectionalLight::getDirection(){
    return this->direction;
};

void DirectionalLight::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
    Vector *zero = this->calculateWordToCanvas(P_o, P_Look, Up, new Vector(0,0,0));

    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    double x = this->directionIni->get_x_Point();
    double y = this->directionIni->get_y_Point();
    double z = this->directionIni->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->direction->set_x_Point(newX);
    this->direction->set_y_Point(newY);
    this->direction->set_z_Point(newZ);

    this->direction = (this->direction->minus_with_the_vector(zero))->get_this_vector_unitary();
};



/* point */

PointLight::PointLight(){};

void PointLight::setPostion(Vector *position){
    this->position = position;
    this->positionIni = new Vector(
        position->get_x_Point(),
        position->get_y_Point(),
        position->get_z_Point()
    );
};
Vector *PointLight::getPosition(){
    return this->position;
};
Vector *PointLight::getPositionIni(){
    return this->positionIni;
};

void PointLight::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up){
    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    Vector *worldVector = this->getPositionIni();
    double x = worldVector->get_x_Point();
    double y = worldVector->get_y_Point();
    double z = worldVector->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->getPosition()->set_x_Point(newX);
    this->getPosition()->set_y_Point(newY);
    this->getPosition()->set_z_Point(newZ);
};


/* SPOT LIGHT */

void SpotLight::setDirection(Vector *direction) {
    this->direction = direction->get_this_vector_unitary();
    this->directionIni = new Vector(
        this->direction->get_x_Point(),
        this->direction->get_y_Point(),
        this->direction->get_z_Point()
    );
};

Vector* SpotLight::getDirection(){
    return this->direction;
};

void SpotLight::setPostion(Vector *position) {
    this->position = position;
    this->positionIni = new Vector(
        this->position->get_x_Point(),
        this->position->get_y_Point(),
        this->position->get_z_Point()
    );
};

Vector* SpotLight::getPosition(){
    return this->position;
};

void SpotLight::setAngle(double angle){
    this->angle = angle;
};
double SpotLight::getAngle(){
    return this->angle;
};

void SpotLight::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
    Vector *zero = this->calculateWordToCanvas(P_o, P_Look, Up, new Vector(0,0,0));

    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    double x = this->directionIni->get_x_Point();
    double y = this->directionIni->get_y_Point();
    double z = this->directionIni->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->direction->set_x_Point(newX);
    this->direction->set_y_Point(newY);
    this->direction->set_z_Point(newZ);

    this->direction = (this->direction->minus_with_the_vector(zero))->get_this_vector_unitary();

    x = this->positionIni->get_x_Point();
    y = this->positionIni->get_y_Point();
    z = this->positionIni->get_z_Point();

    newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->position->set_x_Point(newX);
    this->position->set_y_Point(newY);
    this->position->set_z_Point(newZ);

};
