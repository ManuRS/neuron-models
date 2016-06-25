#ifndef MODELS_TOOLS
#define MODELS_TOOLS

#define num_rafagas_max 40
#define num_rafagas_analisis 3

#define porcentaje_offset 0.8
#define porcentaje_frA 0.75
#define porcentaje_frB 0.75
#define diff_offset 5000

#define frontera_diff 5.0

#define t_auto 1
#define puntos_rafaga_def 2500 //10000
#define tiempo_de_rafaga_s_def 0.25 //1.0

//#define MODO_CALIBRADO 0 u 8
#define MODO_CALIBRADO 8

/*Parametros hr*/
#define paso_hr 0.001
#define e 3.281 /*2.2*/
#define mu 0.0021
#define s 4

/*Parametros iz*/
#define paso_iz 0.001
#define a 0.02
#define b 0.2
#define c -50.0
#define d 2.0
#define I 10.0

/*Parametros mr*/
#define alpha_mr 6
#define mu_mr 0.001
#define o_mr -0.1
#define e_mr 1
#define I_mr 1

int rafaga_hr;
int rafaga_iz;
int rafaga_mr;

int puntos_rafaga;
float tiempo_de_rafaga_s;

/*Funciones*/
void ini_hr (double *x_ini, double *y_ini, double *z_ini, double *min, double *minB, double *max);
void ini_iz (double *v_ini, double *u_ini, double *min, double *minABS, double *max);
void ini_mr (double *x_ini, double *y_ini, double *min, double *minABS, double *max);

void calcula_escala (
                     double min_virtual, double max_virtual, 
                     double min_viva, double max_viva, 
                     double *escala_virtual_a_viva, double *escala_viva_a_virtual, 
                     double *offset_virtual_a_viva, double *offset_viva_a_virtual
                    );
                    
int ini_recibido (double *min, double *minABS, double *max);

#endif
