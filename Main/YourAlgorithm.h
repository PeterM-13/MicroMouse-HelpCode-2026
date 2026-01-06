#ifndef Your_Algorithm
#define Your_Algorithm

#include "Globals.h"
#include "IRcontrol.h"
#include "MotorControl.h"
#include "Navigation.h"
#include "OtherIO.h"

extern bool startAlgorithm;
extern bool startAlgorithm2;

void setupAlgorithm();
void loopAlgorithm();

void mainAlgorithm();

void startOffsetAction();
void moveForwardAction();
void turnLeftAction();
void turnRightAction();
void turnAroundAction();

void testIrReadings();
void testMotors();


#endif // Your_Algorithm