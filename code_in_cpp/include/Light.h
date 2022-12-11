#pragma once
#include "Vector.h"


class Light {
    private:
        Vector *intesity;
        int type;
        bool isActive;

    public:
        Light();
        void setIntesity(Vector *intesity);
        void setType(int type);
        void turnOnOrTurnOff(bool switcher);
        Vector* getIntensity();
        int getType();
        bool active();

        virtual void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) = 0;
};

class PointLight : public Light {
    private:
        Vector* position;
    public:
        PointLight();
        void setPostion(Vector *position);
        Vector *getPosition();

        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);
};

class DirectionalLight : public Light{
    private:
        Vector *direction;
    public:
        void setDirection(Vector *direction);
        Vector* getDirection();

        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);

};

class SpotLight : public Light {
    private:
        Vector *direction;
        Vector *position;
        double angle;


    public:
        void setDirection(Vector *direction);
        Vector* getDirection();

        void setPostion(Vector *position);
        Vector *getPosition();

        void setAngle(double angle);
        double getAngle();

        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);
};
