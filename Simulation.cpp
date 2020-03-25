#include <stdio.h>
#include "Simulation.h"
#include "Floor.h"
#include "Robot.h"
#include <iostream>
#include "grafic.h"

//Crea e inicializa un puntero a esctructura Sim (Simulation).
//Dependiendo del modo, pueden o no inicializarse el timer, el display y la event queue.
Sim* createSimulation(unsigned int count, unsigned int width, unsigned int height, int mode) {
	Sim* Simulation = new (std::nothrow) Sim;
	
	//Si se pudo alocar memoria y es el modo 1...
	
	if (Simulation && mode == MODO1) {

		//Crea display. Si hay error, muestra mensaje y Simulation=NULL.
		if (!createDisplay(Simulation)) {
			std::cout << "Failed to create display\n";
			Simulation = NULL;
		}
		else
			al_set_window_title(Simulation->disp, "EDA - Trabajo Práctico N°2"); //Si lo puede crear, pone título.

		//Crea event queue. Si hay error, muestra mensaje y Simulation=NULL.
		if (!createEventQueue(Simulation)) {
			std::cout << "Failed to create event queue.\n";
			Simulation = NULL;
		}
		//Crea timer. Si hay error, muestra mensaje y Simulation=NULL.
		if (!createTimer(Simulation)) {
			std::cout << "Failed to create timer\n";
			Simulation = NULL;
		}
	}

	//Si se pudo crear, e independientemente del modo, setea altura, ancho, puntero a 
	//estructura Baldosa (array Piso), puntero a estructura Robot (array Robs) y cantidad de robots.
	if (Simulation) {
		Simulation->height = height;
		Simulation->width = width;
		Simulation->Piso = createFloor(width, height);
		Simulation->Robs = createRobots(Simulation->Piso,count, width, height,mode);
		Simulation->robotCount = count;
	}

	return Simulation;
}

//Libera recursos asignados a la simulación.
void freeSimulation(Sim* s,int mode) {
	freeFloor(s->Piso);
	freeRobots(s->Robs);
	if (mode == MODO1) {
		al_destroy_display(s->disp);
		al_destroy_timer(s->timer);
		al_destroy_event_queue(s->Queue);
	}
	if (s) {
		delete s;
		s = nullptr;
	}
}

//Simula todo el programa. La distinción entre modo 1 y modo 2 radica en la parte gráfica.
unsigned int simulate(Sim* s,int mode) {
	unsigned long ticks = 0.0;

	//En modo 1...

	if (mode==MODO1){
		ALLEGRO_EVENT evento;

		//crea event queue e inicia timer.
		al_register_event_source(s->Queue, al_get_timer_event_source(s->timer));
		al_start_timer(s->timer);

		//Actualiza gráficos y mueve robots cada 1/FPS segundos hasta que todo el piso esté en estado LIMPIO.
		while (!isFloorClean(s->Piso, s->width, s->height)) {
			if (al_get_next_event(s->Queue, &evento) && evento.type == ALLEGRO_EVENT_TIMER) {
				for (int i = 0; i < s->robotCount; i++) {
					updateGrid(s->width, s->height, s->Piso, s->Robs, s->robotCount);	//Actualiza gráficos.
					moveRobot(s->Robs+i, s->Piso, s->width, s->height);					//Mueve robots.
				}
				ticks++;			//En cada vuelta, se incrementa en 1 la cantidad de ticks.
			}
		}
	}

	//En modo 2...
	else {

		//Mientras haya baldosas con estado SUCIO, mueve a los robots y aumenta los ticks.
		while (!isFloorClean(s->Piso, s->width, s->height)) {
			for (int i = 0; i < s->robotCount; i++)
				moveRobot(s->Robs + i, s->Piso, s->width, s->height);
			ticks++;
		}
	}
	return ticks;
}

//Crea display y chequea errores.
bool createDisplay(Sim* s) {
	s->disp = al_create_display(W, H);
	if (!s->disp)
		return false;
	return true;
}

//Crea event queue y chequea errores.
bool createEventQueue(Sim* s) {
	s->Queue = al_create_event_queue();
	if (!s->Queue)
		return false;
	return true;
}

//Crea timer y chequea errores.
bool createTimer(Sim* s) {
	s->timer = al_create_timer(1 / FPS);
	if (!s->timer)
		return false;
	return true;
}