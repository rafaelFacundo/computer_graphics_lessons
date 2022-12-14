#include "../include/Mesh.h"

#include <iostream>
using namespace std;


/* WRAPPER */

Wrapper::Wrapper(){

}

void Wrapper::set_unitary_vector(double x, double y, double z){
    this->unitary_vector = new Vector(x,y,z);
    this->unitary_vector = new Vector(x,y,z);
    Vector *topToInsert = this->get_center_top_vector();
    this->top_ini = new Vector(
        topToInsert->get_x_Point(),
        topToInsert->get_y_Point(),
        topToInsert->get_z_Point()
    );
};

void Wrapper::set_B_vector(double x, double y, double z){
    this->B_vector = new Vector(x,y,z);
    this->B_vectorIni = new Vector(x,y,z);
};

void Wrapper::set_radius(double radius) {
    this->radius = radius;
}

void Wrapper::set_height(double height) {
    this->height = height;
}

double Wrapper::get_radius() {
    return this->radius;
}

double Wrapper::get_height() {
    return this->height;
}

Vector *Wrapper::get_unitary_vector() {
    return this->unitary_vector;
}

Vector *Wrapper::get_B_vector() {
    return this->B_vector;
}

Vector *Wrapper::get_center_top_vector() {
    Vector *unitary_vector = (this->get_unitary_vector())->get_this_vector_unitary();
    return B_vector->sum_with_the_vector(unitary_vector->multiply_by_a_scalar(this->height));
}



returnType Wrapper::didThePointIntercepted(Vector *dir, Vector *P_o, Vector *base){
    returnType result;
    double D_scalar_n;
    Vector* Pi_minus_base;
    Vector *Ppi_minus_P_o = base->minus_with_the_vector(P_o);
    double Ppi_mns_Po_scalar_N = Ppi_minus_P_o->scalar_with(this->get_unitary_vector()->multiply_by_a_scalar(-1.0));

    if (base == this->get_B_vector()) {
        D_scalar_n = dir->scalar_with(this->get_unitary_vector()->multiply_by_a_scalar(-1.0));
    }else {
        D_scalar_n = dir->scalar_with(this->get_unitary_vector());
    }


    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = 1;

    if ( D_scalar_n == 0) {
        return result;
    }

    double T_i = Ppi_mns_Po_scalar_N / D_scalar_n;
    Vector* Pi = P_o->sum_with_the_vector(dir->multiply_by_a_scalar(T_i));

    if(base == this->get_B_vector()) {
        Pi_minus_base = Pi->minus_with_the_vector(this->get_B_vector());
    }else {
        Pi_minus_base = Pi->minus_with_the_vector(this->get_center_top_vector());
    }

    double norm = Pi_minus_base->getNormOfThisVector();

    if ( T_i > 0 && norm <= this->get_radius()) {
        result.point_of_intersection = T_i;
        result.doesIntersect = true;
        return result;
    }
    return result;
};

void Wrapper::putOrRemoveLid(bool put){
    this->haveLid = put;
};
void Wrapper::setInterception(bool intercept){
    this->intercepted = intercept;
};

void Wrapper::setIntercBase(bool interc){
    this->intercepBase = interc;
};
void Wrapper::setIntercLid(bool interc){
    this->intercepLid = interc;
};


bool Wrapper::is_Ti_a_valid_point(Vector *P_o, Vector *Dr, double Ti) {
    Vector *Dr_times_ti = Dr->multiply_by_a_scalar(Ti);
    Vector *Pi = P_o->sum_with_the_vector(Dr_times_ti);

    /* Pi_m_B = Pi_minus_B_vector  */
    Vector *Pi_m_B = Pi->minus_with_the_vector(this->get_B_vector());
    double Pi_m_b_Scalar_U = Pi_m_B->scalar_with(this->get_unitary_vector());

    /* Vector_UpB = U_times_Pi_m_b_ScalarU  */
    Vector *Vector_UpB = this->get_unitary_vector()->multiply_by_a_scalar(Pi_m_b_Scalar_U);
    double norm_of_Vector_UpB = sqrt(Vector_UpB->scalar_with(Vector_UpB));

    if ( Pi_m_b_Scalar_U > 0 && Pi_m_b_Scalar_U <= this->get_height()) {
        return true;
    }else {
        return false;
    };
};

returnType Wrapper::does_the_point_intercept(Vector *dir, Vector *P_o){
    returnType result;
    Vector *d_scalar_u = this->get_unitary_vector()->multiply_by_a_scalar(dir->scalar_with(this->get_unitary_vector()));
    Vector *w_vector = dir->minus_with_the_vector(d_scalar_u);
    Vector *Po_minus_B = P_o->minus_with_the_vector(this->get_B_vector());
    Vector *Po_minus_B_scalar_u = this->get_unitary_vector()->multiply_by_a_scalar(Po_minus_B->scalar_with(this->get_unitary_vector()));
    Vector *v_vector = Po_minus_B->minus_with_the_vector(Po_minus_B_scalar_u);

    double a = w_vector->scalar_with(w_vector);
    double b = 2 * (v_vector->scalar_with(w_vector));
    double c = v_vector->scalar_with(v_vector) - pow(this->get_radius(), 2);
    double delta = pow(b,2) - 4*a*c;

    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = 1;

    if ( delta > 0 ) {

        /* calculo os dois ti */
        double Ti_1 = (-b + sqrt(delta))/(2*a);
        double Ti_2 = (-b - sqrt(delta))/(2*a);



        bool Ti_1_verification = this->is_Ti_a_valid_point(P_o, dir, Ti_1);
        bool Ti_2_verification = this->is_Ti_a_valid_point(P_o, dir, Ti_2);

        if (Ti_1_verification && Ti_2_verification && (Ti_1 < Ti_2)) {
            result.point_of_intersection = Ti_1;
            result.doesIntersect = true;
            this->setInterception(false);
            this->setIntercBase(false);
            this->setIntercLid(false);
        }else if (Ti_1_verification && Ti_2_verification && (Ti_1 >= Ti_2)) {
            result.point_of_intersection = Ti_2;
            result.doesIntersect = true;
            this->setInterception(false);
            this->setIntercBase(false);
            this->setIntercLid(false);

        }else if (Ti_1_verification) {
            returnType T2_base = didThePointIntercepted(dir, P_o, this->get_B_vector());
            returnType T2_top = didThePointIntercepted(dir, P_o, this->get_center_top_vector());

            if (T2_base.doesIntersect && T2_base.point_of_intersection < Ti_1) {
                result.point_of_intersection = Ti_2;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(true);
                this->setIntercLid(false);
            }else if (T2_top.doesIntersect && (T2_top.point_of_intersection < Ti_1)) {
                result.point_of_intersection = Ti_2;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(false);
                this->setIntercLid(true);
            }else {
                result.point_of_intersection = Ti_1;
                result.doesIntersect = true;
                this->setInterception(false);
                this->setIntercBase(false);
                this->setIntercLid(false);
            }
        }else if (Ti_2_verification) {
            returnType T1_base = didThePointIntercepted(dir, P_o, this->get_B_vector());
            returnType T1_top = didThePointIntercepted(dir, P_o, this->get_center_top_vector());
            if (T1_base.doesIntersect && (T1_base.point_of_intersection < Ti_2)) {
                result.point_of_intersection = Ti_1;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(true);
                this->setIntercLid(false);
            }else if (T1_top.doesIntersect && (T1_top.point_of_intersection < Ti_2)) {
                result.point_of_intersection = Ti_1;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(false);
                this->setIntercLid(true);
            }else {
                result.point_of_intersection = Ti_2;
                result.doesIntersect = true;
                this->setInterception(false);
                this->setIntercBase(false);
                this->setIntercLid(false);
            }
        } else {
            returnType bse = didThePointIntercepted(dir, P_o, this->get_B_vector());
            returnType tp = didThePointIntercepted(dir, P_o, this->get_center_top_vector());
            if(bse.doesIntersect && tp.doesIntersect && (bse.point_of_intersection <= tp.point_of_intersection)) {
                result.point_of_intersection = bse.point_of_intersection;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(true);
                this->setIntercLid(false);
            }else if(bse.doesIntersect && tp.doesIntersect && (bse.point_of_intersection > tp.point_of_intersection)){
                result.point_of_intersection = tp.point_of_intersection;
                result.doesIntersect = true;
                this->setInterception(true);
                this->setIntercBase(false);
                this->setIntercLid(true);
            }
        }
    }

    return result;
};


void Wrapper::applyRotateX(double angle){
    this->get_unitary_vector()->ThisRotateX(angle);
};
void Wrapper::applyRotateY(double angle){
    this->get_unitary_vector()->ThisRotateY(angle);
};
void Wrapper::applyRotateZ(double angle){
    this->get_unitary_vector()->ThisRotateZ(angle);
};

void Wrapper::applyTranslate(double x, double y, double z){
    this->get_B_vector()->ThisTranslate(x,y,z);
    this->B_vectorIni->ThisTranslate(x,y,z);
};

void Wrapper::applyScale(double sx, double sy, double sz){
    this->set_radius(this->get_radius() * sx);
    this->set_height(this->get_height() * sx);
};

void Wrapper::applyReflectXY(){};
void Wrapper::applyReflectXZ(){};
void Wrapper::applyReflectYZ(){};

void Wrapper::applyShearYX(double angle){};
void Wrapper::applyShearXY(double angle){};
void Wrapper::applyShearXZ(double angle){};
void Wrapper::applyShearZX(double angle){};
void Wrapper::applyShearYZ(double angle){};
void Wrapper::applyShearZY(double angle){};



void Wrapper::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
    Vector *top_vector = new Vector(this->top_ini->get_x_Point(), this->top_ini->get_y_Point(), this->top_ini->get_z_Point());

    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    double x = this->B_vectorIni->get_x_Point();
    double y = this->B_vectorIni->get_y_Point();
    double z = this->B_vectorIni->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->get_B_vector()->set_x_Point(newX);
    this->get_B_vector()->set_y_Point(newY);
    this->get_B_vector()->set_z_Point(newZ);

    x = top_ini->get_x_Point();
    y = top_ini->get_y_Point();
    z = top_ini->get_z_Point();

    newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    top_vector->set_x_Point(newX);
    top_vector->set_y_Point(newY);
    top_vector->set_z_Point(newZ);

    Vector *newUni = top_vector->minus_with_the_vector(this->get_B_vector());
    newUni = newUni->get_this_vector_unitary();
    this->unitary_vector = newUni;


};





Mesh::Mesh() {
    this->typeOfThisObject = 4;
}

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
    Vector *P1_vector;
    Vector *P2_vector;
    Vector *P3_vector;
    Vector *R1_vector;
    Vector *R2_vector;
    Vector *normal;
    Vector *w;
    Vector *normalUnitary;
    Vector *Pi;
    Vector *distance_vector;
    Vector *V;
    double C1, C2, C3;
    returnType wrapperResult;
    wrapperResult.doesIntersect = true;
    int numberOfFaces = this->getSizeOfFacesList();
    returnType result;
    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = this->getTypeOfThisObject();

    if (this->wrapper != NULL) {
        wrapperResult = this->wrapper->does_the_point_intercept(dir, P_o);
    }

    if ( !(wrapperResult.doesIntersect) ) {

        return result;
    }


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

        P1_vector = this->listOfPoints[v1]->gimmeTheCoordinateVector();
        P2_vector = this->listOfPoints[v2]->gimmeTheCoordinateVector();
        P3_vector = this->listOfPoints[v3]->gimmeTheCoordinateVector();

        R1_vector = P2_vector->minus_with_the_vector(P1_vector);

        R2_vector = P3_vector->minus_with_the_vector(P1_vector);

        normal = R1_vector->vectorProductWith(R2_vector);

        normalUnitary = normal->get_this_vector_unitary();

        w = P_o->minus_with_the_vector(P1_vector);

        //double Po_minus_P1_scalar_normal = (P_o->minus_with_the_vector(P1_vector))->scalar_with(normal);

        double Dir_scalar_normal = dir->scalar_with(normalUnitary);
        double Ti_point = (-w->scalar_with(normalUnitary)) / Dir_scalar_normal;

        if ( Dir_scalar_normal != 0 && Ti_point > 0 ) {
            /* Pi point */
            Pi = P_o->sum_with_the_vector(dir->multiply_by_a_scalar(Ti_point));

            distance_vector = Pi->minus_with_the_vector(P_o);

            double distanceFromP_o = distance_vector->getNormOfThisVector();

            V = Pi->minus_with_the_vector(P_o);

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

            if ( result.point_of_intersection == -1 && (C1 >= 0 && C2 >= 0 && C3 >= 0) ) {
                result.doesIntersect = true;
                result.point_of_intersection = Ti_point;
                this->set_T_i(Ti_point);
                this->setNormal(normalUnitary);
            }else if ( (C1 >= 0 && C2 >= 0 && C3 >= 0) && Ti_point < result.point_of_intersection ) {
                result.doesIntersect = true;
                result.point_of_intersection = Ti_point;
                this->set_T_i(Ti_point);
                this->setNormal(normalUnitary);
            }

        }

    }




    delete R1_vector;
    delete R2_vector;
    delete normal;
    delete w;
    delete normalUnitary;
    delete Pi;
    delete distance_vector;
    delete V;

    return result;
};


returnType Mesh::does_the_point_intercept(Vector *dir, Vector *P_o) {
    return this->calculateIntersectionForEachFace(dir, P_o);
};


void Mesh::gime_your_color(
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


    Vector *P_i = Eye_position->sum_with_the_vector(Direction->multiply_by_a_scalar(this->T_i));

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

    delete I_eye_d;
    delete I_eye_e;
    delete vectorWithColors;
};

/* Matrix transformations application */

void Mesh::applyRotateX(double angle){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisRotateX(angle);
        //point->gimmeTheCoordinateVector()->ThisRotateX(angle);
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyRotateX(angle);
    }

};
void Mesh::applyRotateY(double angle){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisRotateY(angle);
        //point->gimmeTheCoordinateVector()->ThisRotateY(angle);

    };
    if (this->wrapper != NULL) {
        this->wrapper->applyRotateY(angle);
    }
};
void Mesh::applyRotateZ(double angle){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisRotateZ(angle);
        //point->gimmeTheCoordinateVector()->ThisRotateZ(angle);

    };
    if (this->wrapper != NULL) {
        this->wrapper->applyRotateZ(angle);
    }
};

void Mesh::applyTranslate(double x, double y, double z){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisTranslate(x,y,z);
        point->gimmeTheCoordinateVector()->ThisTranslate(x,y,z);

    };

    if (this->wrapper != NULL) {
        this->wrapper->applyTranslate(x,y,z);
    }
};
void Mesh::applyScale(double sx, double sy, double sz){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisScale(sx,sy,sz);
        //point->gimmeTheCoordinateVector()->ThisScale(sx,sy,sz);
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyScale(sx,sy,sz);
    }
};

void Mesh::applyReflectXY(){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisReflectXY();
        point->gimmeTheCoordinateVector()->ThisReflectXY();
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyReflectXY();
    }
};
void Mesh::applyReflectXZ(){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisReflectXZ();
        point->gimmeTheCoordinateVector()->ThisReflectXZ();
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyReflectXZ();
    }
};
void Mesh::applyReflectYZ(){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisReflectYZ();
        point->gimmeTheCoordinateVector()->ThisReflectYZ();
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyReflectYZ();
    }
};

void Mesh::applyShearYX(double angle){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisShearYX(angle);
        point->gimmeTheCoordinateVector()->ThisShearYX(angle);
    };
    this->wrapper = NULL;
};
void Mesh::applyShearXY(double angle){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisShearXY(angle);
        point->gimmeTheCoordinateVector()->ThisShearXY(angle);
    };
    this->wrapper = NULL;
};
void Mesh::applyShearXZ(double angle){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisShearXZ(angle);
        point->gimmeTheCoordinateVector()->ThisShearXZ(angle);
    };
    this->wrapper = NULL;
};
void Mesh::applyShearZX(double angle){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisShearZX(angle);
        point->gimmeTheCoordinateVector()->ThisShearZX(angle);
    };
    this->wrapper = NULL;
};
void Mesh::applyShearYZ(double angle){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisShearYZ(angle);
        point->gimmeTheCoordinateVector()->ThisShearYZ(angle);
    };
    this->wrapper = NULL;
};
void Mesh::applyShearZY(double angle){
    for (Point* point : this->listOfPoints) {
        point->getPointIni()->ThisShearZY(angle);
        point->gimmeTheCoordinateVector()->ThisShearZY(angle);
    };
    this->wrapper = NULL;
};


void Mesh::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
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

        point->updatePoints(newX, newY, newZ);
    };

    if (this->wrapper != NULL) {
        this->wrapper->applyConvertWordVectoToCanvas(P_o,P_Look,Up);
    }

    delete K;
    delete Kc;
    delete Vup;
    delete I;
    delete Ic;
    delete Jc;

};





void Mesh::addWrapper(
    Vector *B_vector,
    double height,
    double radius,
    Vector *unitaryVector
) {
    Wrapper *newWrapper = new Wrapper();
    newWrapper->set_B_vector(
        B_vector->get_x_Point(),
        B_vector->get_y_Point(),
        B_vector->get_z_Point()
    );

    newWrapper->set_height(height);
    newWrapper->set_radius(radius);
    newWrapper->set_unitary_vector(
        unitaryVector->get_x_Point(),
        unitaryVector->get_y_Point(),
        unitaryVector->get_z_Point()
    );
    this->wrapper = newWrapper;
};
