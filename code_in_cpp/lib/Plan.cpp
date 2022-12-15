#include "../include/Plan.h"

#include <math.h>

Plan::Plan() {
    this->typeOfThisObject = 1;
};

void Plan::set_PI_Point(double x, double y, double z){
    this->Ppi_Point = new Vector(x,y,z);
    this->Ppi_PointIni = new Vector(x,y,z);
};

void Plan::set_N_vector(double x, double y, double z){
    this->N_vector = new Vector(x,y,z);
    this->N_vectorIni = new Vector(x,y,z);
};

Vector* Plan::get_PI_Point() {
    return this->Ppi_Point;
};

Vector* Plan::get_N_vector() {
    return this->N_vector;
};

void Plan::gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Light *light,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
) {
    Vector *Pf_Pi;
    Vector *intensity;
    double clds;

    Vector *P_i = Eye_position->sum_with_the_vector(Direction->multiply_by_a_scalar(this->T_i));

    if (light->getType() == 0) {
        Pf_Pi = ((PointLight*)light)->getPosition()->minus_with_the_vector(P_i);
    }else if (light->getType() == 2) {
        Pf_Pi = ((DirectionalLight*)light)->getDirection()->multiply_by_a_scalar(-1);
    }else {
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

    //Vector *l_vector = Pf_Pi->get_this_vector_unitary();

    if (light->getType() == 1) {
        clds = (Pf_Pi->get_this_vector_unitary())->scalar_with(((SpotLight*)light)->getDirection()->multiply_by_a_scalar(-1));
        if (clds < cos(((SpotLight*)light)->getAngle())) {
            intensity = new Vector(0.0,0.0,0.0);
        }else {
            intensity = ((SpotLight*)light)->getIntensity()->multiply_by_a_scalar(clds);
        }
    }else {
        intensity = light->getIntensity();
    };

    double Dr_magnitude = sqrt(Direction->scalar_with(Direction));
    /* Vector *vector_v = new Vector(
        -(Direction->get_x_Point())/Dr_magnitude,
        -(Direction->get_y_Point())/Dr_magnitude,
        -(Direction->get_z_Point())/Dr_magnitude
    ); */

    double l_scalar_normal = 2 * ((Pf_Pi->get_this_vector_unitary())->scalar_with(this->get_N_vector()));
    Vector *nomal_scalar_with_above = this->get_N_vector()->multiply_by_a_scalar(l_scalar_normal);
    Vector *R_vector = nomal_scalar_with_above->minus_with_the_vector((Pf_Pi->get_this_vector_unitary()));

    double F_d = (Pf_Pi->get_this_vector_unitary())->scalar_with(this->get_N_vector());

    if (F_d < 0 ) {
        F_d = 0;
    }

    double F_e = R_vector->scalar_with(Direction->get_this_vector_unitary()->multiply_by_a_scalar(-1));

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

returnType Plan::does_the_point_intercept(Vector *dir, Vector *P_o) {
    returnType result;
    Vector* Ppi_minus_P_o = this->Ppi_Point->minus_with_the_vector(P_o);
    double Ppi_mns_Po_scalar_N = Ppi_minus_P_o->scalar_with(this->get_N_vector());
    double D_scalar_n = dir->scalar_with(this->get_N_vector());
    result.point_of_intersection = -1.0;
    result.doesIntersect = false;
    result.doesTheRayInterceptSomeLid = false;
    result.typeOfTheInterceptedObject = this->getTypeOfThisObject();
    if ( D_scalar_n == 0 ) {
        return result;
    }
    double T_i = Ppi_mns_Po_scalar_N / D_scalar_n;
    if ( T_i > 0 ) {
        this->set_T_i(T_i);
        result.point_of_intersection = T_i;
        result.doesIntersect = true;
        return result;
    }
    delete Ppi_minus_P_o;
    return result;
};


void Plan::applyRotateX(double angle){
    this->N_vector->ThisRotateX(angle);
    this->N_vectorIni->ThisRotateX(angle);
};
void Plan::applyRotateY(double angle){
    this->N_vector->ThisRotateY(angle);
    this->N_vectorIni->ThisRotateY(angle);
};
void Plan::applyRotateZ(double angle){
    this->N_vector->ThisRotateZ(angle);
    this->N_vectorIni->ThisRotateZ(angle);
};

void Plan::applyTranslate(double x, double y, double z){
    this->Ppi_Point->ThisTranslate(x,y,z);
    this->Ppi_PointIni->ThisTranslate(x,y,z);
};

void Plan::applyScale(double sx, double sy, double sz){

};

void Plan::applyReflectXY(){};
void Plan::applyReflectXZ(){};
void Plan::applyReflectYZ(){};

void Plan::applyShearYX(double angle){};
void Plan::applyShearXY(double angle){};
void Plan::applyShearXZ(double angle){};
void Plan::applyShearZX(double angle){};
void Plan::applyShearYZ(double angle){};
void Plan::applyShearZY(double angle){};


Vector *Plan::calculateWordToCanvas(Vector *P_o, Vector *P_Look, Vector *Up, Vector *worldVector){
    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    double x = worldVector->get_x_Point();
    double y = worldVector->get_y_Point();
    double z = worldVector->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    delete K;
    delete Kc;
    delete Vup;
    delete I;
    delete Ic;
    delete Jc;

    return new Vector(newX, newY, newZ);
};

void Plan::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up){
    Vector *zero = this->calculateWordToCanvas(P_o, P_Look, Up, new Vector(0,0,0));
    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    Vector *worldVector = this->Ppi_PointIni;
    double x = worldVector->get_x_Point();
    double y = worldVector->get_y_Point();
    double z = worldVector->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->get_PI_Point()->set_x_Point(newX);
    this->get_PI_Point()->set_y_Point(newY);
    this->get_PI_Point()->set_z_Point(newZ);


    x = this->N_vectorIni->get_x_Point();
    y = this->N_vectorIni->get_y_Point();
    z = this->N_vectorIni->get_z_Point();

    newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    Vector *newNvector = new Vector(newX, newY, newZ);
    newNvector = newNvector->minus_with_the_vector(zero);
    newNvector = newNvector->get_this_vector_unitary();

    this->N_vector = newNvector;

    delete K;
    delete Kc;
    delete Vup;
    delete I;
    delete Ic;
    delete Jc;
};


void Plan::set_TextureImage(string filename, bool horizontalAxis){
    this->texture = new Image();
    this->imageLoaded = texture->loadImage(filename);
    this->planHorizontalAxis = horizontalAxis;
};
