#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "models_tools.h"
#include "realtime_manager.h"
#include "comedi_manager.h"

void ini_hr (double *x_ini, double *y_ini, double *z_ini, double *min, double *minABS, double *max){

    /*No perder tanto tiempo*/
    *x_ini=1.797032;
    *y_ini=-4.132035;
    *z_ini=1.955857;
    *min=-1.608734;
    *minABS=-1.608734;
    *max=1.797032;
    rafaga_hr=260166;
    return;

    double x_old = -1, y_old = 0.5, z_old = 0.3;
    double x, y, z;
    double maxHR=-999999;
    double minHR=999999;
    double minHRb=999999;
    int i = 0;
    rafaga_hr=0;
    FILE *f;
    f = fopen ("data/ini_hr.dat", "w");
    
    for(i=0; i<280000*4; i++){
        /*El modelo converge*/
        x = x_old + paso_hr * (y_old + 3*x_old*x_old - x_old*x_old*x_old - z_old + e);
	    y = y_old + paso_hr * (1 - 5*x_old*x_old - y_old);
	    z = z_old + mu*paso_hr * (-z_old + s*(x_old+1.6) );
	    x_old = x;
	    y_old = y;
	    z_old = z; 
	    fprintf(f, "%d %f\n", i, x);
    }
    
    for(i=0; i<280000*3; i++){
        /*Calculamos max y min*/
        x = x_old + paso_hr * (y_old + 3*x_old*x_old - x_old*x_old*x_old - z_old + e);
	    y = y_old + paso_hr * (1 - 5*x_old*x_old - y_old);
	    z = z_old + mu*paso_hr * (-z_old + s*(x_old+1.6) );
	    if(x>maxHR){
	        maxHR=x;
	    }
	    if(x<minHR && x>x_old){
	        minHRb=minHR;
	        minHR=x_old;
	    }
	    x_old = x;
	    y_old = y;
	    z_old = z;
    }
    
    /*Rafaga*/
    while(1){
        x = x_old + paso_hr * (y_old + 3*x_old*x_old - x_old*x_old*x_old - z_old + e);
	    y = y_old + paso_hr * (1 - 5*x_old*x_old - y_old);
	    z = z_old + mu*paso_hr * (-z_old + s*(x_old+1.6) );
	    
	    x_old = x;
	    y_old = y;
	    z_old = z;
	    
        if((int)(x*1000000)==(int)(maxHR*1000000))
            break;
    }
    
    /*Rafaga*/
    while(1){
        x = x_old + paso_hr * (y_old + 3*x_old*x_old - x_old*x_old*x_old - z_old + e);
	    y = y_old + paso_hr * (1 - 5*x_old*x_old - y_old);
	    z = z_old + mu*paso_hr * (-z_old + s*(x_old+1.6) );
	    
	    x_old = x;
	    y_old = y;
	    z_old = z;
	    
	    rafaga_hr++;
        if((int)(x*1000000)==(int)(maxHR*1000000))
            break;
    }
    
    *x_ini = x;
    *y_ini = y;
    *z_ini = z;
    *min = minHRb;
    *minABS = minHR;
    *max = maxHR;
     
    /* 
    printf("x_ini=%f\n", x);
    printf("y_ini=%f\n", y);
    printf("z_ini=%f\n", z);
    printf("min=%f\n", minHRb);
    printf("minABS=%f\n", minHR);
    printf("max=%f\n", maxHR);
    printf("rafaga_hr=%d\n", rafaga_hr);
    */
    
    fclose(f);
    return;
 
}

void ini_iz (double *v_ini, double *u_ini, double *min, double *minABS, double *max){

    /*No perder tanto tiempo*/
    *v_ini=30.240263;
    *u_ini=-5.544592;
    *min=-50.000000;
    *minABS=-74.235106;
    *max=30.240470;
    rafaga_iz=59324;
    return;

    double v, u;
    double v_old = -68.324165;
    double v_old2= -68.324165;
    double u_old = 0.346447;
    double maxIZ=-999999;
    double minIZ=999999;
    double minIZb=999999;
    int i = 0;
    rafaga_iz = 0;
    FILE *f;
    f = fopen ("data/ini_iz.dat", "w");

    for(i=0; i<60000*3; i++){
        /*El modelo converge*/
        if(v_old>=30){ 
  		    v_old=c; 
  		    u_old=u_old+d; 
	    }
	    v = v_old + paso_iz * (0.04*v_old*v_old + 5*v_old + 140 - u_old + I );
	    u = u_old + paso_iz * a * (b*v_old - u_old);
	    v_old = v; 
	    u_old = u; 
	    fprintf(f, "%d %f\n", i, v);
    }
  
    for(i=0; i<60000*3; i++){
        /*Calculamos max y min*/
        if(v_old>=30){ 
  		    v_old=c; 
  		    u_old=u_old+d; 
	    }
	    v = v_old + paso_iz * (0.04*v_old*v_old + 5*v_old + 140 - u_old + I );
	    u = u_old + paso_iz * a * (b*v_old - u_old);
	
	    if(v>maxIZ){
	        maxIZ=v;
	    }
        if(v_old2>v_old && v_old<v && i!=0){
            /*Cambio de tendencia*/
            if(v_old<minIZ){
                minIZ=v_old;
            }
        }
        if(v_old2>=v_old && v_old<=v && i!=0){
            /*Cambio de tendencia*/
            if(v_old<minIZb){
                minIZb=v_old;
            }
        }
    
        v_old = v;
	    v_old2 = v_old; 
	    u_old = u;
    }
    
    /*Rafaga*/
    while(1){
        if(v_old>=30){ 
  		    v_old=c; 
  		    u_old=u_old+d; 
	    }
	    v = v_old + paso_iz * (0.04*v_old*v_old + 5*v_old + 140 - u_old + I );
	    u = u_old + paso_iz * a * (b*v_old - u_old);
	    
	    v_old = v;
	    v_old2 = v_old; 
	    u_old = u;
	    
        if((int)(v*100)==(int)(maxIZ*100))
            break;
	    
    }
    
    /*Rafaga*/
    while(1){
        if(v_old>=30){ 
  		    v_old=c; 
  		    u_old=u_old+d; 
	    }
	    v = v_old + paso_iz * (0.04*v_old*v_old + 5*v_old + 140 - u_old + I );
	    u = u_old + paso_iz * a * (b*v_old - u_old);
	    
	    v_old = v;
	    v_old2 = v_old; 
	    u_old = u;
	    
	    rafaga_iz++;
        if((int)(v*100)==(int)(maxIZ*100))
            break;
    
    }
    
    *v_ini = v;
    *u_ini = u;
    *min = minIZ;
    *minABS = minIZb;
    *max = maxIZ;
    fclose(f);
    
    /*
    printf("v_ini=%f\n", v);
    printf("u_ini=%f\n", u);
    printf("min=%f\n", minIZ);
    printf("minABS=%f\n", minIZb);
    printf("max=%f\n", maxIZ);
    printf("rafaga_iz=%d\n", rafaga_iz);
    */
    
    return;
}

void ini_mr (double *x_ini, double *y_ini, double *min, double *minABS, double *max){
    
    double x, y, x_interpol;
    double x_old=-1.96;
    double y_old=-4.0;
    int i=0, j=0;
    double maxi = -9999;
    double mini = 9999;
    
    FILE *f;
    f = fopen ("data/ini_mr.dat", "w");

    /*BUCLE 1*/
    for(i=0; i<10000*5; i++){
    
        //Punto primero
        y = y_old - mu_mr * (x_old+1) + mu_mr*o_mr;
        
        y_old = y_old + e_mr*I_mr;
        
        if(x_old<=0){
            x = alpha_mr/(1-x_old) + y_old;
        }else if(x_old>=alpha_mr+y_old){
            x = -1;
        }else{
            x = alpha_mr+y_old;
        }
        
        /*BUCLE 2*/
        puntos_rafaga=10000;
        for(j=0; j<((puntos_rafaga-400)/400); j++, i++){
            x_interpol = x_old + (x-x_old) / 24 * (j);
            fprintf(f, "%d %f\n", i, x_interpol);
        
            if(i>20000){
                if(x_interpol<mini)
                    mini=x_interpol;
                else if(x_interpol>maxi)
                    maxi=x_interpol;
            }
        
        }
        
        x_old = x;
        y_old = y;
         
    }

    *x_ini = x;
    *y_ini = y;
    *min = mini*0.6;
    *minABS = mini;
    *max = maxi;
    rafaga_mr=10000;
    
    /*
    printf("x_ini=%f\n", x);
    printf("y_ini=%f\n", y);
    printf("min=%f\n", mini*0.6);
    printf("minABS=%f\n", mini);
    printf("max=%f\n", maxi);
    */
    
    fclose(f);
    return;

}

void calcula_escala (double min_virtual, double max_virtual, double min_viva, double max_viva, double *escala_virtual_a_viva, double *escala_viva_a_virtual, double *offset_virtual_a_viva, double *offset_viva_a_virtual){
    
    double rg_virtual, rg_viva;
    
    rg_virtual = max_virtual-min_virtual;
    rg_viva = max_viva-min_viva;
    
    /*printf("rg_virtual=%f, rg_viva=%f\n", rg_virtual, rg_viva);*/
    
    *escala_virtual_a_viva = rg_viva / rg_virtual;
    *escala_viva_a_virtual = rg_virtual / rg_viva;
    
    *offset_virtual_a_viva = min_viva - (min_virtual*(*escala_virtual_a_viva));
    *offset_viva_a_virtual = min_virtual - (min_viva*(*escala_viva_a_virtual));

    return;
}


int ini_recibido (double *min, double *minABS, double *max){

    /*Iniciamos rt y comedi*/
    
    if(comedi_iniciar()==-1) return -1;
    
    /*Vamos a escanear 10000 puntos durante x segundos para determinar min y max*/
    int i=0, j;
    double valor_recibido=0.0, valor_old=0.0, resta=0.0, pendiente_max=-999999;
    //double bajada_mayor=-999999;
    //double subida_mayor=-999999;
    
    int segs_observo=15;
    
    double maxi=-999999;
    double mini=999999;
    double miniB=999999;
    FILE *f;
    f = fopen ("data/ini_lectura.dat", "w");
    realtime_on();
    for (i=0; i<10000*(segs_observo/2.0); i++){
        comedi_recibir(&valor_recibido);
        
        if(valor_recibido>maxi){
            maxi=valor_recibido;
        }else if(valor_recibido<mini){
            mini=valor_recibido;
        }
        
        if(i>2){
            resta=valor_recibido-valor_old;
            
            if(resta>pendiente_max){
                pendiente_max=resta;
                miniB=valor_old;
            }
        }
        
        
        if(i%10==0)
            valor_old=valor_recibido;
         
        //fprintf(f, "%d %f\n", i, valor_recibido);
        realtime_wait();
    }
    
    int count_aux=0;
    for (j=0; j<10000*(segs_observo/2); i++, j++){
        comedi_recibir(&valor_recibido);
        
        if(fabs(mini*0.7-valor_recibido)<0.0025){
            count_aux++;
        }

         
        fprintf(f, "%d %f\n", i, valor_recibido);
        realtime_wait();
    }
    
    realtime_off();
    comedi_cerrar();
    
    printf("LECTURA INICIAL\n");
    printf("\tmax_leido=%f\n", maxi);
    printf("\tmin_leido=%f\n", mini);
    printf("\tmin_leidoB=%f\n", mini*0.7);
    printf("\trafs/seg=%f\n\n", count_aux/(segs_observo/2.0));
    ////////
    if(t_auto==1){
        tiempo_de_rafaga_s = 1 / (count_aux/(segs_observo/2.0));
        puntos_rafaga = tiempo_de_rafaga_s * 10000;
    }else{
        tiempo_de_rafaga_s = tiempo_de_rafaga_s_def;
        puntos_rafaga = puntos_rafaga_def;
    }
    ///////
    fclose(f);

	*minABS = mini;
    *min = mini*0.7;
    *max = maxi;
    return 1;
}
