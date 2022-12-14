#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

typedef struct {
    double center_esphere[3];
    double radius_Of_esphere;
} esphere;

double prod_Esc(double vector1[3], double vector2[3]);

esphere newEsphere(
    double x,
    double y,
    double z,
    double radius
);

double doesThePointIntersecEsphere(
    double direction[3], 
    double W_vector[3],
    esphere esphereToCheck
);




#endif 