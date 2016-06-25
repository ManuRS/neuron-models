#ifndef COMEDI_MANAGER
#define COMEDI_MANAGER

int comedi_iniciar(void);
int comedi_enviar(double valor);
int comedi_recibir(double * ret);
void comedi_cerrar(void);

#endif
