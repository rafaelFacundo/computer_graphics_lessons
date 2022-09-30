#include <SDL2/SDL.h>
#include <math.h>

double prod_Esc(double vector1[3], double vector2[3]) { 
    double result = vector1[0]*vector2[0] + vector1[1]*vector2[1] + vector1[2]*vector2[2]; 
    return result; 
}

double min (double number, double number2) {
    if (number > number2) {
        return number2;
    }
    return number;
}

int main(int argc, char const *argv[]) { 
    SDL_Window* window = NULL; 
    SDL_Renderer* renderer = NULL;
    
    double wid = 600.0; 
    double h = 600.0; 
    double n_linhas = 600.0; 
    double n_colunas = 600.0; 
    double dJ = 50.0; 

    double Dx = wid/n_colunas; 
    double Dy = h/n_linhas;

    double z = -dJ; 
    double raioDaEsf = 80.0;

    double cJan[3] = {0.0,0.0,-dJ}; 
    double centroEsfera[3] = {0.0,0.0,-90}; 
    double P_o[3] = {0.0,0.0,0.0}; 
    double Fonte_luminosa[3] = {0.0,5.0,0.0};
    double L_amb[3] = {0.05, 0.05, 0.05};
    double I_f[3] = {0.7,0.7,0.7}; 
    double K_d[3] = {255,0.0,0.0}; 
    double w[3] = { 
        P_o[0] - centroEsfera[0], 
        P_o[1] - centroEsfera[1], 
        P_o[2] - centroEsfera[2] 
    }; 
    

    SDL_Init(SDL_INIT_VIDEO); 
    SDL_CreateWindowAndRenderer(wid,h, 0, &window, &renderer); 
    SDL_SetRenderDrawColor(renderer, 100, 100, 100,255); 
    SDL_RenderClear(renderer); 

    for (int l = 0; l < n_linhas; l++) { 
        double Yj = h/2 - Dy/2 - l*Dy; 
        for (int c = 0; c < n_colunas; c++) { 
            double Xj = - wid/2 + Dx/2 + c*Dx; 
            double dir[3] = { Xj, Yj, z }; 

            double a = prod_Esc(dir, dir); 
            double b = 2 * prod_Esc(w, dir); 
            double cx = prod_Esc(w, w) - pow(raioDaEsf, 2); 
            double delta = pow(b,2) - 4*a*cx;

            if (delta > 0) { 
                /* SDL_RenderDrawPoint(renderer, c, l); */ 
                double T_i = (-b - sqrt(delta))/(2*a);
 
                double P_i[3] = { 
                    P_o[0] + dir[0] * T_i, 
                    P_o[1] + dir[1] * T_i, 
                    P_o[2] + dir[2] * T_i 
                };

                double Pf_Pi[3] = { 
                    Fonte_luminosa[0] - P_i[0], 
                    Fonte_luminosa[1] - P_i[1], 
                    Fonte_luminosa[2] - P_i[2] 
                };

                double Pf_pi_norm = sqrt(prod_Esc(Pf_Pi, Pf_Pi));
                
                double l_vector[3] = { 
                    Pf_Pi[0]/Pf_pi_norm, 
                    Pf_Pi[1]/Pf_pi_norm, 
                    Pf_Pi[2]/Pf_pi_norm 
                };

                double normal[3] = { 
                    (P_i[0] - centroEsfera[0])/raioDaEsf, 
                    (P_i[1] - centroEsfera[1])/raioDaEsf, 
                    (P_i[2] - centroEsfera[2])/raioDaEsf 
                };
                
                double dr_nom = sqrt(prod_Esc(dir,dir));
                double vector_v[3] = { 
                    -dir[0]/dr_nom, 
                    -dir[1]/dr_nom, 
                    -dir[2]/dr_nom 
                };

                double F_d = prod_Esc(l_vector, normal); 
                
                if (F_d < 0 ) {
                    F_d = 0;
                }
                
                double I_eye_d[3] = { 
                    I_f[0] * K_d[0]*F_d, 
                    I_f[1] * K_d[1]*F_d, 
                    I_f[2] * K_d[2]*F_d 
                };

                double scalarLn = prod_Esc(l_vector, normal);
                double r[3] = {
                    2 * scalarLn * normal[0] - l_vector[0],
                    2 * scalarLn * normal[1] - l_vector[1],
                    2 * scalarLn * normal[2] - l_vector[2],
                };

                double F_e = prod_Esc(r, vector_v);

                if (F_e <0 ) {
                    F_e = 0;
                };

                double I_eye_e[3] = { 
                    I_f[0] * K_d[0]*F_e, 
                    I_f[1] * K_d[1]*F_e, 
                    I_f[2] * K_d[2]*F_e 
                };

                double color[3] = {
                    I_eye_d[0] + I_eye_e[0] + L_amb[0],
                    I_eye_d[1] + I_eye_e[1] + L_amb[1],
                    I_eye_d[1] + I_eye_e[1] + L_amb[2],
                };

                SDL_SetRenderDrawColor(
                    renderer,
                    min(color[0],255.0),
                    min(color[1],255.0),
                    min(color[2],255.0),
                    255
                ); 
                SDL_RenderDrawPoint(renderer, c, l); 
            } 
        } 
    }
    SDL_RenderPresent(renderer);
    SDL_Event event; 
    int isRunning = 1; 
    while (isRunning) { 
        while (SDL_PollEvent (&event) != 0) { 
            if(event.type == SDL_QUIT) 
            isRunning = 0; 
        }
    SDL_UpdateWindowSurface (window); 
    } 
    SDL_DestroyWindow (window); 
    SDL_Quit ();
    return 0;
}