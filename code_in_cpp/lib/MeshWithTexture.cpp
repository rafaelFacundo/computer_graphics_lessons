#include "../include/MeshWithTexture.h"

#include <iostream>
using namespace std;


MeshWithTexture::MeshWithTexture(Vector *baseVector, double width, double height) {
    this->insertApoint( new Point(
        baseVector->get_x_Point(),
        baseVector->get_y_Point(),
        baseVector->get_z_Point()
    ));

    this->insertApoint( new Point(
        baseVector->get_x_Point(),
        baseVector->get_y_Point(),
        (baseVector->get_z_Point() + height)
    ));

    this->insertApoint( new Point(
        baseVector->get_x_Point() + width,
        baseVector->get_y_Point(),
        (baseVector->get_z_Point() + height)
    ));


    this->insertApoint( new Point(
        baseVector->get_x_Point() + width,
        baseVector->get_y_Point(),
        baseVector->get_z_Point()
    ));

    this->insertAEdge(new Edge(0,1));
    this->insertAEdge(new Edge(1,2));
    this->insertAEdge(new Edge(2,3));
    this->insertAEdge(new Edge(3,0));
    this->insertAEdge(new Edge(1,3));

    this->insertAFace(new Face(3,4,0));
    this->insertAFace(new Face(1,4,2));






};

int MeshWithTexture::getSizeOfFacesList(){
    return this->listOfFaces.size();
};

void MeshWithTexture::setNormal(Vector *normal){
    this->normal = normal;
};

Vector* MeshWithTexture::get_N_vector(){
    return this->normal;
};


void MeshWithTexture::insertApoint(Point *point){
    this->listOfPoints.push_back(point);
};
void MeshWithTexture::insertAEdge(Edge *edge){
    this->listOfEdges.push_back(edge);
};
void MeshWithTexture::insertAFace(Face *face){
    this->listOfFaces.push_back(face);
};


returnType MeshWithTexture::calculateIntersectionForEachFace(Vector *dir, Vector *P_o) {

    double C1, C2, C3;
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

        int idVertice11 = this->listOfEdges[idEdgeOne]->gimmeIdverticeOne();
        int idVertice21 = this->listOfEdges[idEdgeTwo]->gimmeIdverticeOne();

        int idVertice12 = this->listOfEdges[idEdgeOne]->gimmeIdverticeTwo();
        int idVertice22 = this->listOfEdges[idEdgeTwo]->gimmeIdverticeTwo();

        int n1 = (idVertice11 + 1) * (idVertice12 + 1);
        double n = ((double)n1) / ((double)idVertice21 + 1);
        if ( n == (idVertice11 + 1)  || n == (idVertice12 + 1)  ) {
            v1 = idVertice21;
            v2 = idVertice22;
            v3 = n - 1;
        }else {
            v1 = idVertice22;
            v2 = idVertice21;
            v3 = (n1/ (v1+1)) - 1;
        };

        Vector *P1_vector = this->listOfPoints[v1]->gimmeTheCoordinateVector();
        Vector *P2_vector = this->listOfPoints[v2]->gimmeTheCoordinateVector();
        Vector *P3_vector = this->listOfPoints[v3]->gimmeTheCoordinateVector();

        Vector *R1_vector = P2_vector->minus_with_the_vector(P1_vector);

        Vector *R2_vector = P3_vector->minus_with_the_vector(P1_vector);

        Vector *normal = R1_vector->vectorProductWith(R2_vector);

        Vector *normalUnitary = normal->get_this_vector_unitary();

        Vector *w = P_o->minus_with_the_vector(P1_vector);

        //double Po_minus_P1_scalar_normal = (P_o->minus_with_the_vector(P1_vector))->scalar_with(normal);

        double Dir_scalar_normal = dir->scalar_with(normalUnitary);
        double Ti_point = (-w->scalar_with(normalUnitary)) / Dir_scalar_normal;

        if ( Dir_scalar_normal != 0 && Ti_point > 0 ) {
            /* Pi point */
            Vector *Pi = P_o->sum_with_the_vector(dir->multiply_by_a_scalar(Ti_point));

            Vector *distance_vector = Pi->minus_with_the_vector(P_o);

            double distanceFromP_o = distance_vector->getNormOfThisVector();

            Vector *V = Pi->minus_with_the_vector(P_o);

            /* Calculating the C1, C2 e C3 */
            double R1_vetorial_R2_scalar_normal = (R1_vector->vectorProductWith(R2_vector))->scalar_with(normal);

            /* C1 */
            double P3_Pi_vetorial_P1_Pi_scalarNormal = ( (P3_vector->minus_with_the_vector(Pi))->vectorProductWith( P1_vector->minus_with_the_vector(Pi) ) )->scalar_with(normal);
            C1 = P3_Pi_vetorial_P1_Pi_scalarNormal / R1_vetorial_R2_scalar_normal;

            /* C2 */
            double P1_Pi_vetorial_P2_Pi_scalarNormal = ( (P1_vector->minus_with_the_vector(Pi))->vectorProductWith(P2_vector->minus_with_the_vector(Pi)) )->scalar_with(normal);
            C2 = P1_Pi_vetorial_P2_Pi_scalarNormal / R1_vetorial_R2_scalar_normal;

            /* C3 */
            //double P2_Pi_vetorial_P3_Pi_scalarNormal = ( (P2_vector->minus_with_the_vector(Pi))->vectorProductWith(P3_vector->minus_with_the_vector(Pi)) )->scalar_with(normal);
            C3 = 1 - C1 - C2;

            if ( result.point_of_intersection == -1 && (C1 >= 0 && C2 >= 0 && C3 >= 0) && ((C1 + C2 + C3) == 1)) {
                result.doesIntersect = true;
                result.point_of_intersection = Ti_point;
                this->set_T_i(Ti_point);
                this->setNormal(normalUnitary);
            }else if ( (C1 >= 0 && C2 >= 0 && C3 >= 0) && ((C1 + C2 + C3) == 1) && Ti_point < result.point_of_intersection ) {
                result.doesIntersect = true;
                result.point_of_intersection = Ti_point;
                this->set_T_i(Ti_point);
                this->setNormal(normalUnitary);
            }

        }

    }

    return result;
};


returnType MeshWithTexture::does_the_point_intercept(Vector *dir, Vector *P_o) {
    return this->calculateIntersectionForEachFace(dir, P_o);
};


void MeshWithTexture::gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Light *light,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
) {


    Vector *Pf_Pi;
    Vector *Light_source_position;
    Vector *intensity;
    double clds;
    Vector *Dir_times_t = Direction->multiply_by_a_scalar(this->T_i);

    Vector *P_i = Eye_position->sum_with_the_vector(Dir_times_t);

    if (light->getType() == 0 ) {
        Light_source_position = ((PointLight*)light)->getPosition();
        Pf_Pi = new Vector(
            Light_source_position->get_x_Point() - P_i->get_x_Point(),
            Light_source_position->get_y_Point() - P_i->get_y_Point(),
            Light_source_position->get_z_Point() - P_i->get_z_Point()
        );
    }else if (light->getType() == 2) {
        Pf_Pi = ((DirectionalLight*)light)->getDirection()->multiply_by_a_scalar(-1);
    } else {
        Pf_Pi = ((SpotLight*)light)->getPosition()->minus_with_the_vector(P_i);
    }

    double Pf_pi_norm = sqrt(Pf_Pi->scalar_with(Pf_Pi));

    if(this->imageLoaded){
        Pixel color;
        if(this->planHorizontalAxis){
            color = this->texture->getPixel(P_i->get_x_Point(), P_i->get_z_Point());
        }
        else{
            color = this->texture->getPixel(P_i->get_x_Point(), P_i->get_y_Point());
        }

        double newColor[3] = {
            ((double)color.r)/255,
            ((double)color.g)/255,
            ((double)color.b)/255
        };

        this->set_K_a(newColor);
        this->set_K_d(newColor);
        this->set_K_e(newColor);
    }

    Vector *l_vector = new Vector(
        (Pf_Pi->get_x_Point())/Pf_pi_norm,
        (Pf_Pi->get_y_Point())/Pf_pi_norm,
        (Pf_Pi->get_z_Point())/Pf_pi_norm
    );

    if (light->getType() == 1) {
        clds = l_vector->scalar_with(((SpotLight*)light)->getDirection()->multiply_by_a_scalar(-1));
        if (clds < cos(((SpotLight*)light)->getAngle())) {
            intensity = new Vector(0.0,0.0,0.0);
        }else {
            intensity = ((SpotLight*)light)->getIntensity()->multiply_by_a_scalar(clds);
        }
    }else {
        intensity = light->getIntensity();
    };

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

    Vector *I_eye_e = intensity->at_sign_with(this->get_K_e());
    I_eye_e = I_eye_e->multiply_by_a_scalar(F_e);

    Vector *I_eye_d = intensity->at_sign_with(this->get_K_d());
    I_eye_d = I_eye_d->multiply_by_a_scalar(F_d);

    Vector *vectorWithColors = I_eye_d->sum_with_the_vector(I_eye_e);
    vectorWithColors = vectorWithColors->sum_with_the_vector(Ambient_light_intensity->at_sign_with(this->get_K_a()));


    addressToPutTheColor[0] += vectorWithColors->get_x_Point();
    addressToPutTheColor[1] += vectorWithColors->get_y_Point();
    addressToPutTheColor[2] += vectorWithColors->get_z_Point();
};

/* Matrix transformations application */

void MeshWithTexture::applyRotateX(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisRotateX(angle);
    };

};
void MeshWithTexture::applyRotateY(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisRotateY(angle);
    };
};
void MeshWithTexture::applyRotateZ(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisRotateZ(angle);
    };
};

void MeshWithTexture::applyTranslate(double x, double y, double z){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisTranslate(x,y,z);
    };
};
void MeshWithTexture::applyScale(double sx, double sy, double sz){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisScale(sx,sy,sz);
    };
};

void MeshWithTexture::applyReflectXY(){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisReflectXY();
    };
};
void MeshWithTexture::applyReflectXZ(){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisReflectXZ();
    };
};
void MeshWithTexture::applyReflectYZ(){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisReflectYZ();
    };
};

void MeshWithTexture::applyShearYX(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearYX(angle);
    };
};
void MeshWithTexture::applyShearXY(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearXY(angle);
    };
};
void MeshWithTexture::applyShearXZ(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearXZ(angle);
    };
};
void MeshWithTexture::applyShearZX(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearZX(angle);
    };
};
void MeshWithTexture::applyShearYZ(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearYZ(angle);
    };
};
void MeshWithTexture::applyShearZY(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearZY(angle);
    };
};


void MeshWithTexture::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));


    for (Point* point : this->listOfPoints) {
        Vector *pointInitial = point->getPointIni();
        double x = pointInitial->get_x_Point();
        double y = pointInitial->get_y_Point();
        double z = pointInitial->get_z_Point();

        double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
        double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
        double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

        point->gimmeTheCoordinateVector()->set_x_Point(newX);
        point->gimmeTheCoordinateVector()->set_y_Point(newY);
        point->gimmeTheCoordinateVector()->set_z_Point(newZ);
    };
};


void MeshWithTexture::set_TextureImage(string filename, bool horizontalAxis){
    this->texture = new Image();
    this->imageLoaded = texture->loadImage(filename);
    this->planHorizontalAxis = horizontalAxis;
};
