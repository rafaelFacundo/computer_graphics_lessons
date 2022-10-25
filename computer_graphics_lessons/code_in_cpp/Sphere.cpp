#include "Sphere.h"
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
    this->set_Center_of_Object(center);
    this->set_K_e(K_e);
    this->set_K_d(K_d);
    this->set_shine(shine);
    this->set_radius(radius);
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
    Vector *Light_source_position,
    Vector *Light_source_intesity,
    Vector *Ambient_light_intensity,
    double *addressToPutTheColor
) {
    
    Vector *Dir_times_t = Direction->multiply_by_a_scalar(this->T_i);

    Vector *P_i = Eye_position->sum_with_the_vector(Dir_times_t);

    Vector *Pf_Pi = new Vector(
        Light_source_position->get_x_Point() - P_i->get_x_Point(), 
        Light_source_position->get_y_Point() - P_i->get_y_Point(), 
        Light_source_position->get_z_Point() - P_i->get_z_Point() 
    );

    double Pf_pi_norm = sqrt(Pf_Pi->scalar_with(Pf_Pi));
                
    Vector *l_vector = new Vector( 
        (Pf_Pi->get_x_Point())/Pf_pi_norm, 
        (Pf_Pi->get_y_Point())/Pf_pi_norm, 
        (Pf_Pi->get_z_Point())/Pf_pi_norm 
    );

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

    

    

    /* double I_eye_d[3] = { 
        I_f[0] * K_d[0]*F_d, 
        I_f[1] * K_d[1]*F_d, 
        I_f[2] * K_d[2]*F_d 
    }; */

    /* double scalarLn = prod_Esc(l_vector, normal); */
    /* Reaproveitando o valor de F_d, pois é L escalar normal */

    Vector* R_vector = normal->multiply_by_a_scalar(2.0);
    R_vector = R_vector->multiply_by_a_scalar(l_vector->scalar_with(normal));
    R_vector = R_vector->minus_with_the_vector(l_vector);

    /* double r[3] = {
        2 * scalarLn * normal[0] - l_vector[0],
        2 * scalarLn * normal[1] - l_vector[1],
        2 * scalarLn * normal[2] - l_vector[2],
    }; */

    /* double F_e = prod_Esc(r, vector_v); */

    double F_d = l_vector->scalar_with(normal); 
                
    if (F_d < 0 ) {
        F_d = 0.0;
    }

    Vector *I_eye_d = Light_source_intesity->at_sign_with(this->get_K_d());
    I_eye_d = I_eye_d->multiply_by_a_scalar(F_d);

    double F_e = R_vector->scalar_with(vector_v);

    if (F_e <0 ) {
        F_e = 0;
    };

    F_e = pow(F_e, this->get_shiness());

    /* double I_eye_e[3] = { 
        I_f[0] * K_d[0]*F_e, 
        I_f[1] * K_d[1]*F_e, 
        I_f[2] * K_d[2]*F_e 
    }; */

    Vector *I_eye_e = Light_source_intesity->at_sign_with(this->get_K_e());
    I_eye_e = I_eye_e->multiply_by_a_scalar(F_e);

    Vector *vectorWithColors = I_eye_d->sum_with_the_vector(I_eye_e);
    vectorWithColors = vectorWithColors->sum_with_the_vector(Ambient_light_intensity->at_sign_with(this->get_K_a()));

    addressToPutTheColor[0] = vectorWithColors->get_x_Point() * 255;
    addressToPutTheColor[1] = vectorWithColors->get_y_Point() * 255;
    addressToPutTheColor[2] = vectorWithColors->get_z_Point() * 255;
    

    /* double and[3] = {
        vectorWithColors->get_x_Point(),
        vectorWithColors->get_y_Point(),
        vectorWithColors->get_z_Point()
    }; */

    


    /* double color[3] = {
        I_eye_d[0] + I_eye_e[0] + L_amb[0],
        I_eye_d[1] + I_eye_e[1] + L_amb[1],
        I_eye_d[1] + I_eye_e[1] + L_amb[2],
    }; */

    
};

