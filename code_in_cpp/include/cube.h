#pragma once
#include "Mesh.h"

class Cube {
    public:
        static Mesh* create(Vector* baseCenter, double edgeSize, Vector* reflectivity, double shininness);
};