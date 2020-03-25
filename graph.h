#pragma once
#include "prototipos.h"

#define TAMANIO_PANTALLAX_UTIL (W - 80)
#define TAMANIO_PANTALLAY_UTIL 700
#define PANTALLA_Y_NUMEROS (H - 300)

#define BORDE_IZQUIERDO 80
#define ALTURA_TEXTO 40
#define BORDE_INFERIOR 60

int inicializa(void);
double max_arreglo(double* arreglo);
int graph(double* timetaken, int canti);