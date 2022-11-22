#include "Edge.h"

Edge::Edge(Point *pointone, Point *pointtwo) {
    this->pointOne = pointone;
    this->pointTwo = pointTwo;
};
Point* Edge::gimmePointOne(){
    return this->pointOne;
};
Point* Edge::gimmePointTwo(){
    return this->pointTwo;
};
Vector* Edge::gimmeCoordiPointOne(){
    return this->pointOne->gimmeTheCoordinateVector();
};
Vector* Edge::gimmeCoordiPointTwo(){
    return this->pointTwo->gimmeTheCoordinateVector();
};
