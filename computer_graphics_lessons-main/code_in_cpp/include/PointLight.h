#pragma once
#include "Light.h"

class PointLight : public Light {
    private:
        Vector* position;
    public:
        PointLight();
        void setPostion(Vector *position);
        Vector *getPosition();

        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);
};


