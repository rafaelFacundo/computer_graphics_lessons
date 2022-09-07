#include "biblioteca.h"

double prod_Esc(double vector1[3], double vector2[3]) { 
    double result = vector1[0]*vector2[0] + vector1[1]*vector2[1] + vector1[2]*vector2[2]; 
    return result; 
}


/* Function that return a new sphere */
esphere newEsphere(
    double x,
    double y,
    double z,
    double radius
) {
    esphere theNewEsphere;
    theNewEsphere.center_esphere[0] = x;
    theNewEsphere.center_esphere[1] = y;
    theNewEsphere.center_esphere[2] = z;
    theNewEsphere.radius_Of_esphere = radius;
    return theNewEsphere;
};

/* function that checks if the point intersects the esphere */

double doesThePointIntersecEsphere(
    double direction[3], 
    double W_vector[3],
    esphere esphereToCheck
) {
    double a = prod_Esc(direction, direction); 
    double b = 2 * prod_Esc(W_vector, direction); 
    double cx = prod_Esc(W_vector, W_vector) - pow(esphereToCheck.radius_Of_esphere, 2); 
    double delta = pow(b,2) - 4*a*cx;

    return delta;
};
