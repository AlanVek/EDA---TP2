#pragma once

#include "prototipos.h"

Baldosa* createFloor(int width, int height);
void freeFloor(Baldosa* p);
Baldosa* getCurrentBaldosa(Baldosa* piso, unsigned int fil, unsigned int col, unsigned int width, unsigned int height);
bool isFloorClean(Baldosa* piso, int width, int height);
Posicion getNextBaldosa(Robot* robot);