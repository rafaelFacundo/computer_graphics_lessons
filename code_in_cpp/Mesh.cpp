#include "Mesh.h"


int Mesh::getSizeOfFacesList(){
    return this->listOfFaces.size();
};

void Mesh::setNormal(Vector *normal){
    this->normal = normal;
};

Vector* Mesh::get_N_vector(){
    return this->normal;
};


void Mesh::insertApoint(Point *point){
    this->listOfPoints.push_back(point);
};
void Mesh::insertAEdge(Edge *edge){
    this->listOfEdges.push_back(edge);
};
void Mesh::insertAFace(Face *face){
    this->listOfFaces.push_back(face);
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

        int n1 = (idVerticeOne_edg1 + 1) * (idVerticeOne_edg2 + 1);
        double n = n1 / (idVerticeTwo_edg1 + 1);
        if ( n == (idVerticeOne_edg1 + 1) || n == (idVerticeOne_edg2 + 1) ) {
            v1 = idVerticeTwo_edg1;
            v2 = idVerticeTwo_edg2;
            v3 = n - 1;
        }else {
            v1 = idVerticeTwo_edg2;
            v2 = idVerticeTwo_edg1;
            v3 = (n1/ (v1+1)) - 1;
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
            this->set_T_i(Ti_point);
            this->setNormal(normal);
        }



    }

    return result;
};


returnType Mesh::does_the_point_intercept(Vector *dir, Vector *P_o) {
    return this->calculateIntersectionForEachFace(dir, P_o);
};


void Mesh::gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Vector *Light_source_position,
    Vector *Light_source_intesity,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
) {
    Vector *Dir_times_t = Direction->multiply_by_a_scalar(this->T_i);

    Vector *P_i = Eye_position->sum_with_the_vector(Dir_times_t);

    Vector *Pf_Pi = Light_source_position->minus_with_the_vector(P_i);

    double Pf_pi_norm = sqrt(Pf_Pi->scalar_with(Pf_Pi));

    Vector *l_vector = new Vector(
        (Pf_Pi->get_x_Point())/Pf_pi_norm,
        (Pf_Pi->get_y_Point())/Pf_pi_norm,
        (Pf_Pi->get_z_Point())/Pf_pi_norm
    );

    double Dr_magnitude = sqrt(Direction->scalar_with(Direction));
    Vector *vector_v = new Vector(
        -(Direction->get_x_Point())/Dr_magnitude,
        -(Direction->get_y_Point())/Dr_magnitude,
        -(Direction->get_z_Point())/Dr_magnitude
    );

    double l_scalar_normal = 2 * (l_vector->scalar_with(this->get_N_vector()));
    Vector *nomal_scalar_with_above = this->get_N_vector()->multiply_by_a_scalar(l_scalar_normal);
    Vector *R_vector = nomal_scalar_with_above->minus_with_the_vector(l_vector);

    double F_d = l_vector->scalar_with(this->get_N_vector());

    if (F_d < 0 ) {
        F_d = 0;
    }

    double F_e = R_vector->scalar_with(vector_v);

    if (F_e < 0 ) {
        F_e = 0;
    };

    F_e = pow(F_e, this->get_shiness());

    Vector *I_eye_e = Light_source_intesity->at_sign_with(this->get_K_e());
    I_eye_e = I_eye_e->multiply_by_a_scalar(F_e);

    Vector *I_eye_d = Light_source_intesity->at_sign_with(this->get_K_d());
    I_eye_d = I_eye_d->multiply_by_a_scalar(F_d);

    Vector *vectorWithColors = I_eye_d->sum_with_the_vector(I_eye_e);
    vectorWithColors = vectorWithColors->sum_with_the_vector(Ambient_light_intensity->at_sign_with(this->get_K_a()));


    addressToPutTheColor[0] = vectorWithColors->get_x_Point() * 255;
    addressToPutTheColor[1] = vectorWithColors->get_y_Point() * 255;
    addressToPutTheColor[2] = vectorWithColors->get_z_Point() * 255;
};
