#pragma once
#include "Point.h"
#include "Vector.h"

class Edge {
    private:
        Point *pointOne;
        Point *pointTwo;
    public:
        Edge(Point *pointone, Point *pointtwo);
        Point* gimmePointOne();
        Point* gimmePointTwo();
        Vector* gimmeCoordiPointOne();
        Vector* gimmeCoordiPointTwo();
};
