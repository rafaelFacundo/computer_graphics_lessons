#include "../include/MeshWithTexture.h"

#include <iostream>
using namespace std;

WrapperTexture::WrapperTexture(){

}

void WrapperTexture::set_unitary_vector(double x, double y, double z){
    this->unitary_vector = new Vector(x,y,z);
    this->top_ini = this->get_center_top_vector();
};

void WrapperTexture::set_B_vector(double x, double y, double z){
    this->B_vector = new Vector(x,y,z);
    this->B_vectorIni = this->B_vector;
};

void WrapperTexture::set_radius(double radius) {
    this->radius = radius;
}

void WrapperTexture::set_height(double height) {
    this->height = height;
}

double WrapperTexture::get_radius() {
    return this->radius;
}

double WrapperTexture::get_height() {
    return this->height;
}

Vector *WrapperTexture::get_unitary_vector() {
    return this->unitary_vector;
}

Vector *WrapperTexture::get_B_vector() {
    return this->B_vector;
}

Vector *WrapperTexture::get_center_top_vector() {
    Vector *unitary_vector = (this->get_unitary_vector())->get_this_vector_unitary();
    return B_vector->sum_with_the_vector(unitary_vector->multiply_by_a_scalar(this->height));
}



returnType WrapperTexture::didThePointIntercepted(Vector *dir, Vector *P_o, Vector *base){
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

void WrapperTexture::putOrRemoveLid(bool put){
    this->haveLid = put;
};
void WrapperTexture::setInterception(bool intercept){
    this->intercepted = intercept;
};

void WrapperTexture::setIntercBase(bool interc){
    this->intercepBase = interc;
};
void WrapperTexture::setIntercLid(bool interc){
    this->intercepLid = interc;
};


bool WrapperTexture::is_Ti_a_valid_point(Vector *P_o, Vector *Dr, double Ti) {
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

returnType WrapperTexture::does_the_point_intercept(Vector *dir, Vector *P_o){
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


void WrapperTexture::applyRotateX(double angle){
    this->get_unitary_vector()->ThisRotateX(angle);
};
void WrapperTexture::applyRotateY(double angle){
    this->get_unitary_vector()->ThisRotateY(angle);
};
void WrapperTexture::applyRotateZ(double angle){
    this->get_unitary_vector()->ThisRotateZ(angle);
};

void WrapperTexture::applyTranslate(double x, double y, double z){
    this->get_B_vector()->ThisTranslate(x,y,z);

};

void WrapperTexture::applyScale(double sx, double sy, double sz){
    this->set_radius(this->get_radius() * sx);
    this->set_height(this->get_height() * sx);
};

void WrapperTexture::applyReflectXY(){};
void WrapperTexture::applyReflectXZ(){};
void WrapperTexture::applyReflectYZ(){};

void WrapperTexture::applyShearYX(double angle){};
void WrapperTexture::applyShearXY(double angle){};
void WrapperTexture::applyShearXZ(double angle){};
void WrapperTexture::applyShearZX(double angle){};
void WrapperTexture::applyShearYZ(double angle){};
void WrapperTexture::applyShearZY(double angle){};



void WrapperTexture::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
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

    x = top_vector-> get_x_Point();
    y = top_vector-> get_y_Point();
    z = top_vector-> get_z_Point();

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





MeshWithTexture::MeshWithTexture(Vector *baseVector, double width, double height) {
    this->typeOfThisObject = 4;
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
    if (this->wrapper != NULL) {
        this->wrapper->applyRotateX(angle);
    }

};
void MeshWithTexture::applyRotateY(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisRotateY(angle);
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyRotateY(angle);
    }
};
void MeshWithTexture::applyRotateZ(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisRotateZ(angle);
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyRotateZ(angle);
    }
};

void MeshWithTexture::applyTranslate(double x, double y, double z){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisTranslate(x,y,z);
    };

    if (this->wrapper != NULL) {
        this->wrapper->applyTranslate(x,y,z);
    }
};
void MeshWithTexture::applyScale(double sx, double sy, double sz){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisScale(sx,sy,sz);
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyScale(sx,sy,sz);
    }
};

void MeshWithTexture::applyReflectXY(){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisReflectXY();
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyReflectXY();
    }
};
void MeshWithTexture::applyReflectXZ(){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisReflectXZ();
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyReflectXZ();
    }
};
void MeshWithTexture::applyReflectYZ(){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisReflectYZ();
    };
    if (this->wrapper != NULL) {
        this->wrapper->applyReflectYZ();
    }
};

void MeshWithTexture::applyShearYX(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearYX(angle);
    };
    this->wrapper = NULL;
};
void MeshWithTexture::applyShearXY(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearXY(angle);
    };
    this->wrapper = NULL;
};
void MeshWithTexture::applyShearXZ(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearXZ(angle);
    };
    this->wrapper = NULL;
};
void MeshWithTexture::applyShearZX(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearZX(angle);
    };
    this->wrapper = NULL;
};
void MeshWithTexture::applyShearYZ(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearYZ(angle);
    };
    this->wrapper = NULL;
};
void MeshWithTexture::applyShearZY(double angle){
    for (Point* point : this->listOfPoints) {
        point->gimmeTheCoordinateVector()->ThisShearZY(angle);
    };
    this->wrapper = NULL;
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

        point->updatePoints(newX, newY, newZ);
    };

    if (this->wrapper != NULL) {
        this->wrapper->applyConvertWordVectoToCanvas(P_o,P_Look,Up);
    }

};





void MeshWithTexture::addWrapper(
    Vector *B_vector,
    double height,
    double radius,
    Vector *unitaryVector
) {
    WrapperTexture *newWrapper = new WrapperTexture();
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


void MeshWithTexture::set_TextureImage(string filename, bool horizontalAxis){
    this->texture = new Image();
    this->imageLoaded = texture->loadImage(filename);
    this->planHorizontalAxis = horizontalAxis;
};


