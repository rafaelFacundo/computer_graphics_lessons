#include "../include/Point.h"

Point::Point(){

}

Point::Point(double x, double y, double z){
    this->points = new Vector(x, y, z);
    this->pointsIni = new Vector(x, y, z);
};

Vector* Point::gimmeTheCoordinateVector(){
    return this->points;
};


Vector* Point::getPointIni() {
    return this->pointsIni;
};

void Point::updatePoints(double x, double y, double z){
    Vector *actual = this->points;
    delete actual;
    this->points = new Vector(x,y,z);
};
