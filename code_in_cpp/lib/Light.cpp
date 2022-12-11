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


/* Direcional */

void DirectionalLight::setDirection(Vector *direction){
    this->direction = direction->get_this_vector_unitary();
};
Vector* DirectionalLight::getDirection(){
    return this->direction;
};

void DirectionalLight::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {

};


/* point */

PointLight::PointLight(){};

void PointLight::setPostion(Vector *position){
    this->position = position;
};
Vector *PointLight::getPosition(){
    return this->position;
};

void PointLight::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up){

};


void SpotLight::setDirection(Vector *direction) {
    this->direction = direction->get_this_vector_unitary();
};

Vector* SpotLight::getDirection(){
    return this->direction;
};

void SpotLight::setPostion(Vector *position) {
    this->position = position;
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

void SpotLight::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {};
