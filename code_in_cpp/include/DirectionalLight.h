#pragma once
#include "Light.h"


class DirectionalLight : public Light{
    private:
        Vector *direction;
    public:
        void setDirection(Vector *direction);
        Vector* getDirection();

        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);

};


