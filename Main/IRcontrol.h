#ifndef IR_Control_H
#define IR_Control_H

#include <Wire.h>
#include <Adafruit_VL6180X.h>

#include "Globals.h"
#include "OtherIO.h"

struct IrSensor {
  Adafruit_VL6180X sensor;
  uint8_t shutdownPin;
  uint8_t address;
};

const int N_SENSORS = 4; // Number of sensors

extern int irReadings[N_SENSORS];
extern bool irSensorsActive;

void setupIrSensors();
void loopIrSensors();

void readIrRange(int sensorIndex);
void checkAllWalls();

#endif // IR_Control_H