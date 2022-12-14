#include "../include/DirectionalLight.h"

void DirectionalLight::setDirection(Vector *direction){
    this->direction = direction->get_this_vector_unitary();
};
Vector* DirectionalLight::getDirection(){
    return this->direction;
};

void DirectionalLight::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {

};
