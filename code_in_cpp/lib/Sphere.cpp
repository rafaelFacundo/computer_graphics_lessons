#include "../include/Sphere.h"

#include <math.h>
#include <iostream>
using namespace std;

Sphere::Sphere():Object(){}

void Sphere::set_radius(double radius){
    this->Sphere_radius = radius;
}

Sphere::Sphere(
    double center[3],
    double K_e[3],
    double K_d[3],
    double shine,
    double radius
):Object() {
    this->typeOfThisObject = 0;
    this->set_Center_of_Object(center);
    this->set_K_e(K_e);
    this->set_K_d(K_d);
    this->set_shine(shine);
    this->set_radius(radius);
    this->centerIni = new Vector(center[0], center[1], center[2]);
};

/* Method that says if the ray intersect the sphere */
returnType Sphere::does_the_point_intercept( Vector *dir, Vector *P_o) {
    returnType result;
    Vector *w = P_o->minus_with_the_vector(this->center_Of_Object);
    double a = dir->scalar_with(dir);
    double b = 2 * w->scalar_with(dir);
    double cx = w->scalar_with(w) - pow(this->Sphere_radius, 2);
    double delta = pow(b,2) - 4*a*cx;

    if (delta > 0) {
        double T_i = (-b - sqrt(delta))/(2*a);
        result.point_of_intersection = T_i;
        result.doesIntersect = true;
        result.doesTheRayInterceptSomeLid = false;
        result.typeOfTheInterceptedObject = this->getTypeOfThisObject();
        this->set_T_i(T_i);
    }else {
        result.point_of_intersection = -1.0;
        result.doesIntersect = false;
        result.doesTheRayInterceptSomeLid = false;
        result.typeOfTheInterceptedObject = this->getTypeOfThisObject();
    }

    return result;
}

double Sphere::get_radius() {
    return this->Sphere_radius;
};

void Sphere::gime_your_color(
    Vector *Eye_position,
    Vector *Direction,
    Light *light,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
) {
    Vector *intensity;
    double clds;
    Vector *Light_source_position;
    Vector *Pf_Pi;

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

    double *center_of_the_sphere = this->get_center();

    Vector *normal = new Vector(
        (P_i->get_x_Point() - center_of_the_sphere[0])/this->get_radius(),
        (P_i->get_y_Point() - center_of_the_sphere[1])/this->get_radius(),
        (P_i->get_z_Point() - center_of_the_sphere[2])/this->get_radius()
    );

    double dr_nom = sqrt(Direction->scalar_with(Direction));
    Vector *vector_v = new Vector(
        -(Direction->get_x_Point())/dr_nom,
        -(Direction->get_y_Point())/dr_nom,
        -(Direction->get_z_Point())/dr_nom
    );

    Vector* R_vector = normal->multiply_by_a_scalar(2.0);
    R_vector = R_vector->multiply_by_a_scalar(l_vector->scalar_with(normal));
    R_vector = R_vector->minus_with_the_vector(l_vector);

    double F_d = l_vector->scalar_with(normal);

    if (F_d < 0 ) {
        F_d = 0.0;
    }

    Vector *I_eye_d = intensity->at_sign_with(this->get_K_d());
    I_eye_d = I_eye_d->multiply_by_a_scalar(F_d);

    double F_e = R_vector->scalar_with(vector_v);

    if (F_e <0 ) {
        F_e = 0;
    };

    F_e = pow(F_e, this->get_shiness());


    Vector *I_eye_e = intensity->at_sign_with(this->get_K_e());
    I_eye_e = I_eye_e->multiply_by_a_scalar(F_e);

    Vector *vectorWithColors = I_eye_d->sum_with_the_vector(I_eye_e);
    vectorWithColors = vectorWithColors->sum_with_the_vector(Ambient_light_intensity->at_sign_with(this->get_K_a()));

    addressToPutTheColor[0] += vectorWithColors->get_x_Point();
    addressToPutTheColor[1] += vectorWithColors->get_y_Point();
    addressToPutTheColor[2] += vectorWithColors->get_z_Point();

    delete I_eye_d;
    delete I_eye_e;
    delete vectorWithColors;




};

Vector* Sphere::get_center_vector() {
    return this->center_Of_Object;
};

void Sphere::applyRotateX(double angle){};
void Sphere::applyRotateY(double angle){};
void Sphere::applyRotateZ(double angle){};

void Sphere::applyTranslate(double x, double y, double z){
    this->get_center_vector()->ThisTranslate(x,y,z);
    this->centerIni->ThisTranslate(x,y,z);
};

void Sphere::applyScale(double sx, double sy, double sz){
    this->set_radius(this->get_radius() * sx);
};

void Sphere::applyReflectXY(){};
void Sphere::applyReflectXZ(){};
void Sphere::applyReflectYZ(){};

void Sphere::applyShearYX(double angle){};
void Sphere::applyShearXY(double angle){};
void Sphere::applyShearXZ(double angle){};
void Sphere::applyShearZX(double angle){};
void Sphere::applyShearYZ(double angle){};
void Sphere::applyShearZY(double angle){};


void Sphere::applyConvertWordVectoToCanvas(Vector *P_o, Vector *P_Look, Vector *Up) {
    Vector *K = P_o->minus_with_the_vector(P_Look);
    Vector *Kc = K->get_this_vector_unitary();

    Vector *Vup = Up->minus_with_the_vector(P_o);
    Vector *I = Vup->vectorProductWith(Kc);
    Vector *Ic = I->get_this_vector_unitary();

    Vector *Jc = Kc->vectorProductWith(Ic);

    double minusIcPlusEye = -(Ic->scalar_with(P_o));
    double minusJcPlusEye = -(Jc->scalar_with(P_o));
    double minusKcPlusEye = -(Kc->scalar_with(P_o));

    Vector *worldVector = this->centerIni;
    double x = worldVector->get_x_Point();
    double y = worldVector->get_y_Point();
    double z = worldVector->get_z_Point();

    double newX = minusIcPlusEye + Ic->get_z_Point() * z + Ic->get_y_Point() * y + Ic->get_x_Point() * x;
    double newY = minusJcPlusEye + Jc->get_z_Point() * z + Jc->get_y_Point() * y + Jc->get_x_Point() * x;
    double newZ = minusKcPlusEye + Kc->get_z_Point() * z + Kc->get_y_Point() * y + Kc->get_x_Point() * x;

    this->get_center_vector()->set_x_Point(newX);
    this->get_center_vector()->set_y_Point(newY);
    this->get_center_vector()->set_z_Point(newZ);

    delete K;
    delete Kc;
    delete Vup;
    delete I;
    delete Ic;
    delete Jc;
}
