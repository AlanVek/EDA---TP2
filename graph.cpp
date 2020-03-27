#include "graph.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "prototipos.h"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include "Simulation.h"

void imprimir_bordes_y(ALLEGRO_FONT* font2, int maximo);
ALLEGRO_DISPLAY* setDisplay(int * errorFlag);
ALLEGRO_BITMAP* setGraphics(double* timeTaken, int canti, int *errorFlag);
void waitForClosure(ALLEGRO_DISPLAY* mi_display, int* errorFlag);


//Genera histograma para el modo 2.
int graph(double* timetaken,int canti)		
{
	//Inicialización de Allegro. Si no se puede, devuelve 0.
	if (inicializa() == -1)
		return 0;
	int errorFlag = 1;
	
	//Crea display. Si no se puede, devuelve 0.
	ALLEGRO_DISPLAY* mi_display = setDisplay(&errorFlag);	
	if (!errorFlag)
		return 0;

	//Carga imágenes. Si no se puede, devuelve 0.
	ALLEGRO_BITMAP* imagen = setGraphics(timetaken, canti,&errorFlag);	
	if (!errorFlag)
		return 0;

	//Espera a que se cierre display. Si hubo error, devuelve 0.
	waitForClosure(mi_display,&errorFlag);
	if (!errorFlag)
		return 0;

	//Se destruye lo creado para Allegro.
	al_destroy_display(mi_display); 
	al_destroy_bitmap(imagen);
	
	return 1;
}


/*Inicializa Allegro y los addons usados. 
Muestra mensajes de errores en caso de no ser posible y devuelve -1. */
int inicializa(void)
{
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Could not inicialize allegro", NULL, NULL);
		al_rest(3);
		return -1;
	}
	if (!al_init_font_addon())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Could not inicialize addon", NULL, NULL);
		al_rest(3);
		return -1;
	}
	if (!al_init_ttf_addon())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Could not inicialize ttf addon", NULL, NULL);
		al_rest(3);
		return -1;
	}
	if (!al_init_image_addon())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Could not inicialize ttf addon", NULL, NULL);
		al_rest(3);
		return -1;
	}

	return 0;
}

//Devuelve el valor máximo de un arreglo.
double max_arreglo(double* arreglo)
{
	int max = 0;
	for (int i = 0; i < MAX_ROBOTS; i++)
	{
		if (arreglo[i] > max)
		{
			max = arreglo[i];
		}
	}
	return max;
}

//Imprime los números correspondientes al eje Y.
void imprimir_bordes_y(ALLEGRO_FONT* font3, int maximo)
{
	//Use char const* as target type.
	std::string s[3];
	char const* pchar[3];  
	for (int i = 3; i > 0; i--)
	{
		s[i-1] = std::to_string(maximo*i/3);
		pchar[i-1] = s[i-1].c_str();
		al_draw_text(font3, al_map_rgb(0, 0, 0), 20, (H - BORDE_INFERIOR) * (1-i/4.0) , 0, pchar[i-1]);
	}
	al_draw_text(font3, al_map_rgb(0, 0, 0), 30, H - BORDE_INFERIOR, 0, "0");
}


//Crea display, carga mensajes y hace chequeo de errores.
ALLEGRO_DISPLAY* setDisplay(int * errorFlag) {
	//Crea el display.
	ALLEGRO_DISPLAY* display = NULL;

	//Inicializa fuente.
	ALLEGRO_FONT* font = al_load_ttf_font("BOSQUE.ttf", 64, 0);			

	//Si no pudo crear el display...
	if (!(display = al_create_display(W,H))|| !font)
	{
		//Mestra mensaje de error y espera tres segundos.
		al_show_native_message_box(NULL, NULL, NULL, "Error", NULL, NULL); 
		al_rest(3);

		//Modifica puntero controlador de errores.
		*errorFlag = 0;		
	}																	
	
	//Si no hubo error...
	if (*errorFlag) {

		//Fondo blanco.
		al_clear_to_color(al_map_rgb(255, 255, 255));

		//Título del gráfico.
		al_draw_text(font, al_map_rgb(0, 0, 0), W / 2, 0, ALLEGRO_ALIGN_CENTRE, "Histograma");

		//Titulo de la pestaña.
		al_set_window_title(display, "MODO 2");	
	}

	//Destruye la fuente creada.
	al_destroy_font(font);		

	//Devuelve el display creado.
	return display;
}


//Setea parte gráfica (imágenes, fuentes, números, ejes).
ALLEGRO_BITMAP* setGraphics(double *timeTaken,int canti, int *errorFlag) {
	std::string str;

	//Retorna el máximo valor en el arreglo timetaken.
	int maximo = max_arreglo(timeTaken);		

	//Carga dos fuentes iguales en distinto tamaño.
	ALLEGRO_FONT* font2 = NULL;
	font2 = al_load_ttf_font("BOSQUE.ttf", 20, 0);
	ALLEGRO_FONT* font3 = NULL;
	font3 = al_load_ttf_font("BOSQUE.ttf", 12, 0);			

	//Carga bitmap con imagen de rectángulo.
	ALLEGRO_BITMAP* imagen_rectangulo = NULL;				
	imagen_rectangulo = al_load_bitmap("rectangulo.png");	

	//Muestra mensaje de error si algo no funcionó.
	if (!font2 || !font3 || !imagen_rectangulo) {

		//Muestra mensaje de error y espera tres segundos.
		al_show_native_message_box(NULL, NULL, NULL, "Error", NULL, NULL);     
		al_rest(3);

		//Modifica puntero controlador de errores.
		*errorFlag = 0;			
	}

	/*Si no hubo errores, se dibujan los ejes y se disponen los rectángulos del histograma en
	función de los valores de ticks para cada cantidad de robots. */
	if (*errorFlag) {
		char const* pchar;

		//Imprime los números del eje y.
		imprimir_bordes_y(font2, maximo);			
		for (int contador = 0; contador < canti; contador++)
		{
			//Convierte el número contador+1 en string.
			str = std::to_string(contador + 1);
			
			//Convierte a char* necesario para usar en al_draw_text.
			pchar = str.c_str();				
	
			/*Para que no se solapen, se usan dos letras distintas, dependiendo de 
			la cantidad de robots, para que no se solapen los números en el eje x. */
			if (canti < 25)
				al_draw_text(font2, al_map_rgb(0, 0, 0), TAMANIO_PANTALLAX_UTIL / canti * contador + BORDE_IZQUIERDO, H - ALTURA_TEXTO, 0, pchar);
			else
				al_draw_text(font3, al_map_rgb(0, 0, 0), TAMANIO_PANTALLAX_UTIL / canti * contador + BORDE_IZQUIERDO, H - ALTURA_TEXTO, 0, pchar);
			al_draw_scaled_bitmap(imagen_rectangulo,
				0, 0, al_get_bitmap_width(imagen_rectangulo), al_get_bitmap_height(imagen_rectangulo),
				TAMANIO_PANTALLAX_UTIL / canti * contador + BORDE_IZQUIERDO, 
				(H - ((TAMANIO_PANTALLAY_UTIL) / (float)maximo) * timeTaken[contador]) - BORDE_INFERIOR, 
				TAMANIO_PANTALLAX_UTIL * 2.0 / (canti * 3.0), ((TAMANIO_PANTALLAY_UTIL) / (float)maximo) * timeTaken[contador],0);
		}
		//Se muestra en pantalla.
		al_flip_display();		
	}
	//Se destruyen fuentes creadas.
	al_destroy_font(font2);
	al_destroy_font(font3);			

	//Se devuelve bitmap.
	return imagen_rectangulo;		
}

//Espera en loop hasta que se cierre el display.
void waitForClosure(ALLEGRO_DISPLAY* mi_display,int * errorFlag) {
	//Crea event queue.
	ALLEGRO_EVENT_QUEUE* queue = NULL;		
		
	//Crea evento.
	ALLEGRO_EVENT Event;				


	//Si no se puede crear event queue...
	if (!(queue = al_create_event_queue())){

		//Modifica puntero controlador de errores.
		*errorFlag = 0;						

		//Muestra mensaje de error.
		al_show_native_message_box(NULL, NULL, NULL, "Error", NULL, NULL);     

		//Espera tres segundos.
		al_rest(3);
	}

	//Si no hubo errores...
	if (*errorFlag) {

		//Registra eventos del display.
		al_register_event_source(queue, al_get_display_event_source(mi_display));
		
		
		bool running = true;
		
		//Loop infinito.
		while (running)
		{
			//Cuando se detecte que se cerró el display, sale del loop.
			if (al_get_next_event(queue, &Event) && Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				running = false;
		}
	}

	//Destruye event queue creada.
	al_destroy_event_queue(queue);		
}