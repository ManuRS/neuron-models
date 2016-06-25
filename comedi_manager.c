#include <comedilib.h>

/*comedi_manager*/
static comedi_t *disp;
const char fileroute[] = "/dev/comedi0";
static int aref = AREF_GROUND;
#define IN_RANGE 0
#define OUT_RANGE  0

/*enviar*/
static int disp_out;
static unsigned int start_subdevice_out = 0;
static int canal_out=0;
static int rango_out=0;
static comedi_range * range_out;
static lsampl_t maxdata_out;

/*recibir*/
static int disp_in;
static unsigned int start_subdevice_in = 0;
static int canal_in=0;
static int rango_in=0;
static comedi_range * range_in;
static lsampl_t maxdata_in;


int comedi_iniciar(void){

  printf("INICIANDO COMEDI\n");

  /*CONEXION A LA TARJETA*/
  disp=comedi_open("/dev/comedi0");
  if(disp==NULL){
  	comedi_perror("comedi_open");
	  return -1;
  }

  /*PUERTO DE ENTRADA*/
  disp_in = comedi_find_subdevice_by_type(disp, COMEDI_SUBD_AI, start_subdevice_in);
  if(disp_in<0){
  	comedi_close(disp);
  	printf("\tError: AI %d\n", COMEDI_SUBD_AI);
  	return -1;
  }

  /* Rellenar comedi_range manualmente
  range_in = (comedi_range *)malloc(sizeof(comedi_range));
  range_in->min=-10;
  range_in->max=10;
  range_in->unit=UNIT_volt;
  */
  range_in = comedi_get_range(disp, disp_in, canal_in, IN_RANGE);
  maxdata_in = comedi_get_maxdata(disp, disp_in, canal_in);
  printf("\tIN -> maxdata: %.1f\n\t\tmaxrange: %.1f \n\t\tminrange: %.1f\n", (double)maxdata_in, range_in->max, range_in->min );

  /*PUERTO DE SALIDA*/
  disp_out = comedi_find_subdevice_by_type(disp, COMEDI_SUBD_AO, start_subdevice_out);
  if(disp_out<0){
  	comedi_close(disp);
  	printf("Error: AO %d\n", COMEDI_SUBD_AO);
  	return -1;
  }

  range_out = comedi_get_range(disp, disp_out, canal_out, OUT_RANGE);
  maxdata_out = comedi_get_maxdata(disp, disp_out, canal_out);
  printf("\tOUT -> maxdata: %.1f\n\t\tmaxrange: %.1f \n\t\tminrange: %.1f\n\n", (double)maxdata_out, range_out->max, range_out->min);

  return 0;
}

int comedi_enviar(double valor){
  double ret;
  lsampl_t envio = comedi_from_phys(valor, range_out, maxdata_out);
  ret = comedi_data_write(disp, disp_out, canal_out, rango_out, aref, envio);
  if(ret<0){
    printf("Error: comedi_data_write\n");
      return -1;
  }
  return 0;
}

int comedi_recibir(double * ret){
  int control;
  lsampl_t data;
  control = comedi_data_read(disp, disp_in, canal_in, rango_in, aref, &data);
  if(control<0){
    printf("Error: comedi_data_read\n");
    return -1;
  }
  *ret = comedi_to_phys(data, range_in, maxdata_in);
  return 0;
}

void comedi_cerrar(void){
  comedi_enviar(0.0);
  comedi_cancel(disp, disp_in);
  comedi_cancel(disp, disp_out);
  comedi_close(disp);
}
