#pragma once
#include "Edge.h"

class Face {
    private:
        int idEdgeOne;
        int idEdgeTwo;
        int idEdgeThree;

    public:
        Face(int idedgeone, int idedgetwo, int idedgethree);
        int gimmeIdEdgeOne();
        int gimmeIdEdgeTwo();
        int gimmeIdEdgeThree();
        int gimmeIndice();


};
