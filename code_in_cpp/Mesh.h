#pragma once
#include "Objects.h"
#include "Point.h"
#include "Edge.h"
#include "Face.h"
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

class Mesh : public Object {
    private:
        Vector *normal;
        int typeOfThisObject = 4;
        vector<Point*> listOfPoints;
        vector<Edge*> listOfEdges;
        vector<Face*> listOfFaces;

    public:
        void setNormal(Vector *normal);
        Vector* get_N_vector();
        int getSizeOfFacesList();

        void insertApoint(Point *point);
        void insertAEdge(Edge *edge);
        void insertAFace(Face *face);
        returnType calculateIntersectionForEachFace(Vector *dir, Vector *P_o);

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
