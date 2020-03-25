#include <stdio.h>
#include "Floor.h"
#include "Robot.h"
#include <iostream>
#include <math.h>
#include "grafic.h"
#define CORRECTOR 0.000001
void moveRobot(Robot* r, Baldosa* p, unsigned int width, unsigned int height) {		
//Cambia posición y ángulo del robot.

	Posicion nextBaldosa = getNextBaldosa(r);		//Pide la baldosa a la que debería moverse.
	while (nextBaldosa.x <= 0 || nextBaldosa.x >= width || nextBaldosa.y <= 0 || nextBaldosa.y >= height) {
		//Mientras se pase de los límites de la pantalla, genera un nuevo ángulo y pide la nueva baldosa.
		(*r).angle = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * ANG_MAX);
		nextBaldosa = getNextBaldosa(r);
	}
	//Cuando encuentra una opción válida, pasa la nueva posición del robot a los miembros X e Y de la esctructura Robot
	// del robot pasado por parámetro.
	r->x = nextBaldosa.x;
	r->y = nextBaldosa.y;

	//Cambioa a LIMPIO el estado de la nueva baldosa.
	getCurrentBaldosa(p, (int)floor(nextBaldosa.y), (int)floor(nextBaldosa.x),width,height)->State = LIMPIO;
}

//Crea un puntero a array de esctructura Robot con los miembros ya inicializados.
Robot* createRobots(Baldosa*p, int count, unsigned int width, unsigned int height, int mode) {
	int i;

	//Asigna memoria.
	Robot* robs = new (std::nothrow)Robot[count];

	//Genera números aleatorios (dentro de sus respectivos parámetros) para X, Y y ángulo.
	if (robs) {
		for (i = 0; i < count; i++) {
			robs[i].angle = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * ANG_MAX);
			robs[i].x = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (width-CORRECTOR));
			robs[i].y = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (height-CORRECTOR));
			
			//Cambia estado de la baldosa a LIMPIO.
			getCurrentBaldosa(p, (int)floor(robs[i].y), (int)floor(robs[i].x), width, height)->State = LIMPIO;
			
			//Si está en modo 1, pinta la casilla de blanco.
			if (mode==MODO1)
				paintBox(robs[i].x, robs[i].y, width, height,al_map_rgb(BL,BL,BL));
		}
	}
	return robs;	//Devuelve el puntero.
}

void freeRobots(Robot* robs) {	//Libera memoria ocupada por puntero a estructura Robot.
	if (robs) {
		delete [] robs;
		robs = nullptr;
	}
}