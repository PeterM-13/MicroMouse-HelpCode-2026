#ifndef GLOBALS_H
#define GLOBALS_H

#include <array>
#include <cmath>

#include "ActionBuffer.h"
#include "Config.h"


// ------------- Define Global Vars ----------
// Constants
extern const int DEBUG_MODE;

// Variables
extern bool wallLeft;
extern bool wallRight;
extern bool wallBack;
extern bool wallFront;
extern bool fatalError;
extern bool collisionDetectionActive;
extern bool laneCenteringActive;
extern bool updateGyroData;

// ------------- Define Global Functions ----------
void setupGlobals();

void print(String text, int priority = 1);
void printLoopTime();

// ------------- Define Global Type(s) -------------
enum IR_SENSORS
{
  FRONT_LEFT_SENSOR = 0,
  LEFT_SENSOR = 1,
  RIGHT_SENSOR = 2,
  FRONT_RIGHT_SENSOR = 3,
};


#endif // GLOBALS_H