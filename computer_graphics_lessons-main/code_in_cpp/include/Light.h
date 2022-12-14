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

        Vector *calculateWordToCanvas(Vector *P_o, Vector *P_Look, Vector *Up, Vector *worldVector);

        virtual void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) = 0;
};

class PointLight : public Light {
    private:
        Vector* position;
        Vector* positionIni;
    public:
        PointLight();
        void setPostion(Vector *position);
        Vector *getPosition();
        Vector *getPositionIni();

        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);
};

class DirectionalLight : public Light{
    private:
        Vector *direction;
        Vector *directionIni;
    public:
        void setDirection(Vector *direction);
        Vector* getDirection();

        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);

};

class SpotLight : public Light {
    private:
        Vector *direction;
        Vector *position;
        Vector *positionIni;
        Vector *directionIni;
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
