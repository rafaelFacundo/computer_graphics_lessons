#pragma once
#include "Objects.h"
#include "Point.h"
#include "Edge.h"
#include "Face.h"

class Mesh : public Object {
    private:
        Point *listOfPoints;
        Edge *listOfEdges;
        Face *listOfFaces;

    public:

        returnType calculateIntersectionForFaces();
        Vector *calculateTheComunPointe(Face *faceToCalculate);

        void gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Vector *Light_source_position,
            Vector *Light_source_intesity,
            Vector *Ambient_light_intensity,
            double *addressToPutTheColor
        );

        virtual returnType does_the_point_intercept(Vector *dir, Vector *P_o);
};
