#include "IRcontrol.h"

IrSensor irSensors[N_SENSORS] = {
  // Sensor object, Shutdown Pin #, I2C address.
  { Adafruit_VL6180X(), A3, 0x32 },
  { Adafruit_VL6180X(), A2, 0x31 },
  { Adafruit_VL6180X(), A1, 0x30 },
  { Adafruit_VL6180X(), A0, 0x29 }
};

int irReadings[N_SENSORS]; // Store most recent range measurements
int currentSensor = 3; // The sensor currently being read from
bool irSensorsActive = false; // Taking range measurements when true
long preIrReadTime = 0; // Last time an IR sensor was read


void setupIrSensors()
{
  // ------------------- Pin Setup  -------------------
  for (int i = 0; i < N_SENSORS; i++) {
    pinMode(irSensors[i].shutdownPin, OUTPUT);
    digitalWrite(irSensors[i].shutdownPin, LOW);
  }

  // --- Udpdate Sensor I2C Addresses ---
  for(int sensorIndex=0; sensorIndex<N_SENSORS; sensorIndex++)
  {
    digitalWrite(irSensors[sensorIndex].shutdownPin, HIGH); // Power-up IR sensor
    delay(20);
    if (irSensors[sensorIndex].sensor.begin()) // Initialise IR sensor
    {
      irSensors[sensorIndex].sensor.setAddress(irSensors[sensorIndex].address); // Change sensor's address
      delay(10);
    }
    else
    {
      print("ERROR: Failed to initialise sensor " + String(sensorIndex));
      // fatalError = true;
      // buzzerOn();
      // break;
    }
  }
  if(!fatalError){ print("INFO: IR Sensors ready!"); }
}

void loopIrSensors()
{
  if(irSensorsActive) 
  {
    const long now = millis();
    if (millis() - preIrReadTime >= IR_SENSOR_READ_DELAY)
    {
      preIrReadTime = now;
      currentSensor ++;
      if(currentSensor >= N_SENSORS) // Reset count if above 3
      {
        currentSensor = 0;
      }
      readIrRange(currentSensor); // Read one sensor per allowed interval to limit I2C load
    }
  }
}

void readIrRange(int sensorIndex)
{
  uint8_t range = irSensors[sensorIndex].sensor.readRange();
  uint8_t status = irSensors[sensorIndex].sensor.readRangeStatus();
  if (status == VL6180X_ERROR_NONE) 
  {
    irReadings[sensorIndex] = range;
  }
  else 
  {
    print("ERROR: IR Sensor " + String(sensorIndex) + " bad status: " + String(status), 2);
    irReadings[sensorIndex] = 299; // MAX Reading
    // Safe to assume error usually just range overflow
  }
}

void checkAllWalls()
{
  wallFront = (irReadings[FRONT_LEFT_SENSOR] < IR_SENSOR_1_WALL_THRESHOLD && irReadings[FRONT_RIGHT_SENSOR] < IR_SENSOR_4_WALL_THRESHOLD);
  wallLeft = (irReadings[LEFT_SENSOR] < IR_SENSOR_2_WALL_THRESHOLD); 
  wallRight = (irReadings[RIGHT_SENSOR] < IR_SENSOR_3_WALL_THRESHOLD);
}
