#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

/*****************************************
DEFINE
******************************************/
#define MAX_ANCHO 70
#define MAX_ALTO 100
#define MAX_ROBOTS 300
#define OK 1
#define ERROR 0
#define KEYLENGHT 2
#define KEY_H 1
#define KEY_W 2
#define KEY_R 3
#define KEY_M 4
#define EXPECTEDPARAMS 4
#define BL 255
#define GR 128
#define GR2 190
#define NE 0
#define ANG_MAX 2*M_PI
#define SUCIO false
#define LIMPIO true
#define MODO1 1
#define MODO2 2
#define SIM_CANT 1000
#define W 1000
#define H 1000
#define LINE_WIDTH 7
#define MODE_2_LIM 0.1
#define FPS 9.0
/*****************************************
TYPEDEF
*****************************************/
typedef struct {
    int height;
    int width;
    int robot_amount;
    int mode;
} user_t;
typedef struct {
    double x;
    double y;
    double angle;
} Robot;

typedef struct {
    bool State;     //True: Clean, False: Dirty.
} Baldosa;

typedef struct {
    double x;
    double y;
} Posicion;
