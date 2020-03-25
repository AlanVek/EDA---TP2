#pragma once
#include "prototipos.h"
#include "Robot.h"
#include "Simulation.h"
/*createGrid: Crea una grilla en Allegro con cant_alto de casillas en vertical
y cant_ancho de casillas en horizontal. Las casillas son de color gris. */
void createGrid(int cant_ancho, int cant_alto);

void updateGrid(int cant_ancho, int cant_alto, Baldosa* piso, Robot* r, unsigned int count);

/*cleanBox: Recibe una posición (x,y) y el tamaño de la grilla, y pinta la casilla
a la cual pertenece la posición (x,y) de blanco (siempre y cuando sea una posición válida). */
void paintBox(double x, double y, int cant_ancho, int cant_alto,ALLEGRO_COLOR rgb);

void drawArrows(Robot* r, int count, unsigned int cant_ancho, unsigned int cant_alto);

int iniciar_allegro ();

bool createDisplay(Sim* s);
bool createEventQueue(Sim* s);
bool createTimer(Sim* s);