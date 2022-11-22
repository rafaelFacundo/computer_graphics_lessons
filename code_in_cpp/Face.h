#pragma once
#include "Edge.h"

class Face {
    private:
        int indice;
        Edge *edgeOne;
        Edge *edgeTwo;
        Edge *edgeThree;

    public:
        Edge *gimeeEdgeOne();
        Edge *gimeeEdgeTwo();
        Edge *gimeeEdgeThree();
        int gimmeIndice();


};
