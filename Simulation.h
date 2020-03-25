#pragma once
#include "prototipos.h"
#include <allegro5/allegro.h>

typedef struct {
	Robot* Robs;
	Baldosa* Piso;
	unsigned int height;
	unsigned int width;
	int robotCount;
	ALLEGRO_DISPLAY* disp;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* Queue;
} Sim;

Sim* createSimulation(unsigned int count, unsigned int width, unsigned int height, int mode);
void freeSimulation(Sim* s,int mode);
unsigned int simulate(Sim* s, int mode);