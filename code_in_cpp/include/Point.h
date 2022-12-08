#pragma once
#include "Vector.h"

class Point {
    private:
        int indice;
        Vector *points;
        Vector *pointsIni;
    public:
        Point();
        Point(double x, double y, double z);
        Vector* gimmeTheCoordinateVector();
        Vector* getPointIni();
};
