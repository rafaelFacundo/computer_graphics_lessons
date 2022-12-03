#pragma once
#include "Point.h"
#include "Vector.h"

class Edge {
    private:
        int idVerticeOne;
        int idVerticeTwo;
    public:

        Edge(int idverticeone, int idverticetwo);
        int gimmeIdverticeOne();
        int gimmeIdverticeTwo();
        Vector* gimmeCoordiPointOne();
        Vector* gimmeCoordiPointTwo();
};
