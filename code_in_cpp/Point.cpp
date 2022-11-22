#include "Point.h"

Point::Point(){

}

Point::Point(double x, double y, double z){
    this->points = new Vector(x, y, z);
};

Vector* Point::gimmeTheCoordinateVector(){
    return this->points;
};
