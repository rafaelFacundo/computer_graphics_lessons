#pragma once
#include "Objects.h"
#include "Point.h"
#include "Edge.h"
#include "Face.h"
#include <iostream>
#include <vector>
using namespace std;

class Mesh : public Object {
    private:
        int typeOfThisObject = 4;
        vector<Point*> listOfPoints;
        vector<Edge*> listOfEdges;
        vector<Face*> listOfFaces;

    public:

        int getSizeOfFacesList();

        returnType calculateIntersectionForEachFace(Vector *dir, Vector *P_o);
        Vector *calculateTheComunPointe(Face *faceToCalculate);

        void gime_your_color(
            Vector *Eye_position,
            Vector *Direction,
            Vector *Light_source_position,
            Vector *Light_source_intesity,
            Vector *Ambient_light_intensity,
            double *addressToPutTheColor
        );

        returnType does_the_point_intercept(Vector *dir, Vector *P_o);
};
