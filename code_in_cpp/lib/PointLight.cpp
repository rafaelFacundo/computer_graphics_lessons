#include "../include/PointLight.h"


PointLight::PointLight(){};

void PointLight::setPostion(Vector *position){
    this->position = position;
};
Vector *PointLight::getPosition(){
    return this->position;
};

void PointLight::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up){

};
