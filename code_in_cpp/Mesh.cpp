#include "Mesh.h"
















int Mesh::getSizeOfFacesList(){
    return this->listOfFaces.size();
};


returnType Mesh::calculateIntersectionForEachFace(Vector *dir, Vector *P_o) {
    int numberOfFaces = this->getSizeOfFacesList();
    returnType result;
    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = this->getTypeOfThisObject();

    double v1, v2, v3;
    for (int i = 0; i < numberOfFaces; i++ ) {
        int idEdgeOne = this->listOfFaces[i]->gimmeIdEdgeOne();
        int idEdgeTwo = this->listOfFaces[i]->gimmeIdEdgeTwo();
        int idEdgeThree = this->listOfFaces[i]->gimmeIdEdgeThree();

        int idVerticeOne_edg1 = this->listOfEdges[idEdgeOne]->gimmeIdverticeOne();
        int idVerticeTwo_edg1 = this->listOfEdges[idEdgeOne]->gimmeIdverticeTwo();

        int idVerticeOne_edg2 = this->listOfEdges[idEdgeTwo]->gimmeIdverticeOne();
        int idVerticeTwo_edg2 = this->listOfEdges[idEdgeTwo]->gimmeIdverticeTwo();

        int n1 = idVerticeOne_edg1 * idVerticeOne_edg2;
        double n = n1 / idVerticeTwo_edg1;
        if ( n == idVerticeOne_edg1 || n == idVerticeOne_edg2 ) {
            v1 = idVerticeTwo_edg1;
            v2 = idVerticeTwo_edg2;
            v3 = n;
        }else {
            v1 = idVerticeTwo_edg2;
            v2 = idVerticeTwo_edg1;
            v3 = n1/ v1;
        }

        Vector *P1_vector = this->listOfPoints[v1]->gimmeTheCoordinateVector();
        Vector *P2_vector = this->listOfPoints[v2]->gimmeTheCoordinateVector();
        Vector *P3_vector = this->listOfPoints[v3]->gimmeTheCoordinateVector();


        Vector *R1_vector = P2_vector->minus_with_the_vector(P1_vector);
        Vector *R2_vector = P3_vector->minus_with_the_vector(P1_vector);

        Vector *normal = R1_vector->vectorProductWith(R2_vector);

        double Po_minus_P1_scalar_normal = (P_o->minus_with_the_vector(P1_vector))->scalar_with(normal);
        double Dir_scalar_normal = dir->scalar_with(normal);
        double Ti_point = -Po_minus_P1_scalar_normal / Dir_scalar_normal;

        /* Pi point */
        Vector *Pi = P_o->sum_with_the_vector(dir->multiply_by_a_scalar(Ti_point));

        /* Calculating the C1, C2 e C3 */
        double R1_vetorial_R2_scalar_normal = (R1_vector->vectorProductWith(R2_vector))->scalar_with(normal);

        /* C1 */
        double P3_Pi_vetorial_P1_Pi_scalarNormal = ( (P3_vector->minus_with_the_vector(Pi))->vectorProductWith( P1_vector->minus_with_the_vector(Pi) ) )->scalar_with(normal);
        double C1 = P3_Pi_vetorial_P1_Pi_scalarNormal / R1_vetorial_R2_scalar_normal;

        /* C2 */
        double P1_Pi_vetorial_P2_Pi_scalarNormal = ( (P1_vector->minus_with_the_vector(Pi))->vectorProductWith(P2_vector->minus_with_the_vector(Pi)) )->scalar_with(normal);
        double C2 = P1_Pi_vetorial_P2_Pi_scalarNormal / R1_vetorial_R2_scalar_normal;

        /* C3 */
        double P2_Pi_vetorial_P3_Pi_scalarNormal = ( (P2_vector->minus_with_the_vector(Pi))->vectorProductWith(P3_vector->minus_with_the_vector(Pi)) )->scalar_with(normal);
        double C3 = P2_Pi_vetorial_P3_Pi_scalarNormal / R1_vetorial_R2_scalar_normal;

        if ((C1 + C2 + C3) == 1) {
            result.doesIntersect = true;
            result.point_of_intersection = Ti_point;
        }

        return result;

    }
};


Vector *Mesh::calculateTheComunPointe(Face *faceToCalculate) {
    int indice = faceToCalculate->gimmeIndice();

};


returnType Mesh::does_the_point_intercept(Vector *dir, Vector *P_o) {
    return this->calculateIntersectionForEachFace(dir, P_o);
};


void gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Vector *Light_source_position,
    Vector *Light_source_intesity,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
) {
    
};