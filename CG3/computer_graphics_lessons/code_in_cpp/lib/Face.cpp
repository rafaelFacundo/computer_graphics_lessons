#include "../include/Face.h"

int Face::gimmeIdEdgeOne() {
    return this->idEdgeOne;
};
int Face::gimmeIdEdgeTwo(){
    return this->idEdgeTwo;
};
int Face::gimmeIdEdgeThree(){
    return this->idEdgeThree;
};

Face::Face(int idedgeone, int idedgetwo, int idedgethree) {
    this->idEdgeOne = idedgeone;
    this->idEdgeTwo = idedgetwo;
    this->idEdgeThree = idedgethree;
};
