#pragma once
typedef int (*pCallback) (char*, char*, void*);


/*parseCmdLine: 
1. Recibe:
	- (int) argC: Cantidad de parámetros, keys y opciones.
	- (char*) argV: Vector con los parámetros, keys y opciones.
	- (*pCallback) parseCallback: Función de callback a la cual referirse al encontrar un
	parámetro, key u opción.
	- (void*) userData: Vector que le transferirá a parseCallback para guardar los datos.
2. Devuelve:
	- (int) 0 si se encontraron errores de forma o errores lógicos (detectados por pCallback).
	- (int) Suma de parámetros y opciones. */

int parseCmdLine(int argC, char* argV[], pCallback parseCallback, void* userData);
/*validateInput:
1. Recibe:
	- (char*) key = Clave de la opción.
	- (char*) value = Valor de la opción.
	- (void*) userData = Donde se guardarán los valores recibidos en caso de ser lógicamente válidos.

2. Devuelve:
	- (int) 0 si lo ingresado no fue válido.
	- (int) 1 si lo ingresado fue válido.

Opciones válidas: 
	- key = h, 0<(int)value<MAX_ALTO
	- key = w, 0<(int)value<MAX_ANCHO
	- key = r, 0<(int)value<MAX_ROBOTS
	- key = m, (m==1 || m==2) */

int validateInput (char* key, char* value , void* userData);

/*checkModeValue:
1. Recibe:
	- (int) value: Valor a chequear.
2. Devuelve:
	- (bool) true: Si el valor proporcionado es válido como modo.
	- (bool) false: Si el valor proporcionado no es válido como modo.

Se fija si el valor pasado es uno de los modos válidos (1 ó 2). */

bool checkModeValue(int value);

/*checkKey:
1. Recibe:
	- (char*) key: Valor a chequear si es una de las claves válidas.
2. Devuelve:
	- (int) 0 si la clave no es válida.
	- (int) 1 si la clave es "h".
	- (int) 2 si la clave es "w".
	- (int) 3 si la clave es "r".
	- (int) 4 si la clave es "m".  */

int checkKey(char* key);

void lowerstring(char* s);