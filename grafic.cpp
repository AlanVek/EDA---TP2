#include "grafic.h"
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "Floor.h"
#include <iostream>

#define ARROW_FACTOR 0.75
#define RADIUS_FACTOR 1.3

using namespace std;

//Inicializa Allegro.
int iniciar_allegro(){		
	if (!al_init())
		return 0;
	al_init_primitives_addon();
	return 1;
}

//Actualiza los dibujos de la grilla.
void updateGrid(int cant_ancho,int cant_alto,Baldosa*piso,Robot*r,unsigned int count){	
	ALLEGRO_COLOR blanco = al_map_rgb(BL, BL, BL);
	ALLEGRO_COLOR gris = al_map_rgb(GR, GR, GR);
	for (int i = 0; i < cant_alto; i++) {
		for (int j = 0; j < cant_ancho; j++) {

			//Cuequea estado de cada baldosa.
			if (getCurrentBaldosa(piso, i, j, cant_ancho, cant_alto)->State)

				//Si está limpia, la pinta de blanco.
				paintBox(j, i, cant_ancho, cant_alto, blanco);				
			else

				//Si no, la pinta de gris.
				paintBox(j, i, cant_ancho, cant_alto, gris);				
		}
	}
	//Vuelve a dibujar las flechas (se borraron al actualizar las casillas, pero es intencional, 
	//ya que las flechas deben ir moviéndose).
	drawArrows(r, count, cant_ancho, cant_alto);
	al_flip_display();		//Lo muestra.
}

//Crea una grilla o tabla de cant_ancho * cant_alto.
void createGrid(int cant_ancho, int cant_alto) {
	ALLEGRO_COLOR negro = al_map_rgb(NE, NE, NE);
	ALLEGRO_COLOR gris = al_map_rgb(GR, GR, GR);
	float ancho_casilla = W / cant_ancho;
	float alto_casilla = H / cant_alto;
	al_clear_to_color(gris);					//Pinta todo de gris.
	for (int i = 1; i < cant_ancho; i++)

		//Líneas verticales.
		al_draw_line(ancho_casilla * i, 0, ancho_casilla * i, H, negro, LINE_WIDTH);
	
	for (int i = 1; i < cant_alto; i++)
		
		//Líneas horizontales.
		al_draw_line(0, alto_casilla * i, W, alto_casilla * i, negro, LINE_WIDTH);
}
void paintBox(double x, double y,int cant_ancho, int cant_alto,ALLEGRO_COLOR rgb) {

//Pinta la casilla en X y en Y con el color pasado por parámetro.
	
	float posit_x = floor(x);
	float posit_y = floor(y);

	float ancho_casilla = W / cant_ancho;
	float alto_casilla = H / cant_alto;

	float x_org = posit_x * ancho_casilla;
	float y_org = posit_y * alto_casilla;

	float x_fin = (posit_x + 1.0) * ancho_casilla;
	float y_fin = (posit_y + 1.0) * alto_casilla;

	if ((cant_ancho - posit_x) == 1)
		x_fin = W - 1;
	if ((cant_alto - posit_y) == 1)
		y_fin = H - 1;
	al_draw_filled_rectangle(x_org+LINE_WIDTH/2, y_org+LINE_WIDTH/2, x_fin, y_fin, rgb);
}

//Dibuja las flechas.
void drawArrows(Robot* r,int count, unsigned int cant_ancho, unsigned int cant_alto) {	
	ALLEGRO_COLOR negro = al_map_rgb(NE, NE, NE);
	float ancho_casilla = W / cant_ancho;
	float alto_casilla = H / cant_alto;
	double xEnd, yEnd;
	for (int i = 0; i < count; i++) {

		//Posición en X donde terminará la flecha según el ángulo. Se toma módulo 1 según consigna.
		xEnd = r[i].x + cos(-r[i].angle);

		//Posición en Y donde terminará la flecha según el ángulo. Se toma módulo 1 según consigna.
		yEnd = r[i].y + sin(-r[i].angle);
		
		//Línea.
		al_draw_line(r[i].x*ancho_casilla, r[i].y*alto_casilla, xEnd*ancho_casilla, yEnd*alto_casilla, negro, LINE_WIDTH*ARROW_FACTOR);	
		
		//Círculo.
		al_draw_filled_circle(r[i].x*ancho_casilla, r[i].y*alto_casilla, LINE_WIDTH*RADIUS_FACTOR, negro);  
	}
}
