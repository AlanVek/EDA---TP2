#pragma once

#include "prototipos.h"

Robot* createRobots(Baldosa* p, int count, unsigned int width, unsigned int height, int mode);
void freeRobots(Robot* robs);
void moveRobot(Robot* r, Baldosa* p, unsigned int width, unsigned int height);