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
            Light *light,
            Vector *Ambient_light_intensity,
            double *addressToPutTheColor
        );

        returnType does_the_point_intercept(Vector *dir, Vector *P_o);

        void applyRotateX(double angle);
        void applyRotateY(double angle);
        void applyRotateZ(double angle);

        void applyTranslate(double x, double y, double z);
        void applyScale(double sx, double sy, double sz);

        void applyReflectXY();
        void applyReflectXZ();
        void applyReflectYZ();

        void applyShearYX(double angle);
        void applyShearXY(double angle);
        void applyShearXZ(double angle);
        void applyShearZX(double angle);
        void applyShearYZ(double angle);
        void applyShearZY(double angle);

        void applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up);
};
