#include "YourAlgorithm.h"

bool startAlgorithm = false;

/* *******

  These variables are available to read from:
  > currentDirection = NORTH, EAST, SOUTH or WEST.
  > currentCell.X / currentCell.Y = Current X, Y position in maze. 

  * [0,0] = bottom left.
  * Default starting position is [0,0] facing EAST -> Defined in Navigation.cpp.
  * Update this if want to test your mouse in a different starting position/orientation.

 ********/

void setupAlgorithm()
{
  delay(1000); // Allow button press
  setupNavigation(); // Resets starting position
  startOffsetAction(); // Move forward slightly to see walls ahead (assuming you start with mouse flat against back wall)
}


void loopAlgorithm()
{ 
  if(startAlgorithm) // Set True after button pressed
  {
    mainAlgorithm();
  
    // --- Algorithms to Test HW ---
    // Ensure only ONE algo is uncommented at once (this includes the main one above).
    // testIrReadings();
    // testMotors();
    // startAlgorithm = false;  // uncomment this to stop looping
  }
}


// Default algorithm that makes decisions based on proximity to center.
void mainAlgorithm()
{
  if(currentActionComplete && isBufferEmpty(actionBuffer))
  {
    // Check if reached the middle. Stop if reached.
    if (checkMiddle())
    {
      startAlgorithm = false;
      parkMotors();
      ledOn();
      return;
    }

    if(!wallFront)
    {
      if(!wallRight && distToMiddle(getCell(EAST)) < distToMiddle(getCell(NORTH)))
      {
        // No wall front or right. Turn right as it's close to middle.
        turnRightAction();
      }
      else if(!wallLeft && distToMiddle(getCell(WEST)) < distToMiddle(getCell(NORTH)))
      {
        // No wall front or left. Turn left as it's close to middle.
        turnLeftAction();
      }
      else
      {
        // No wall forwards, so go forwards.
        moveForwardAction();
      }
     // Not considered: (!wallLeft && !wallRight), or decisions of equel distance to middle.
    }
    else if(!wallRight && !wallLeft)
    {
      if(distToMiddle(getCell(EAST)) > distToMiddle(getCell(WEST)))
      {
        turnLeftAction();
      }
      else
      {
        turnRightAction();
      }
      // Not considered: right and left == same dist to middle.
    }
    else if(!wallRight)
    {
      // If wall in front and no wall right, turn right.
      turnRightAction();
    }
    else if(!wallLeft)
    {
      // If wall front and no wall left, turn left.
      turnLeftAction();
    }
    else 
    {
      // Reached dead end, so turn around.
      turnAroundAction();
    }
  }
}




// ------------- Algorithms for hardware tests -------------
// Run these to identify issues with the hardware.
void testMotors()
{
  // Drives the mouse forwards at varying speed, slow to fast.
  addBlindMoveForwardAction(1, 50);
  addBlindMoveForwardAction(1, 75);
  addBlindMoveForwardAction(1, 100);
  addParkAction();
  startAlgorithm = false; // This stops algo from looping
}

void testIrReadings()
{
  // Logs the readings from each phototransistor.
  // View logs in 'Serial Plotter'.
  // Watch values change as you put an object in front of each sensor. 
  irSensorsActive = true;
  Serial.print(String(irReadings[FRONT_LEFT_SENSOR]));
  Serial.print(",");
  Serial.print(String(irReadings[LEFT_SENSOR]));
  Serial.print(",");
  Serial.print(String(irReadings[RIGHT_SENSOR]));
  Serial.print(",");
  Serial.println(String(irReadings[FRONT_RIGHT_SENSOR]));
}







// ------------ Simplified navigation functions -----------
void startOffsetAction()
{
  navForward();
  addBlindMoveForwardAction(0.75, 80);
  addCheckWallsAction();
}
void moveForwardAction()
{ 
  navForward();
  addMoveForwardAction(1.0, 92);
  addCheckWallsAction();
}
void turnLeftAction()
{
  if(wallFront)
  {
    addIrMonitoringAction(70); 
  }
  else
  {
    const float DIST_OFFSET = 0.8 - (stepsSincelastWallGap/(float)CELL_DISTANCE);
    if(stepsSincelastWallGap != 0 && DIST_OFFSET >= 0.0)
    {
      addBlindMoveForwardAction(DIST_OFFSET, 70);
    }
    else
    {
      wallLeft = true;
      return;
    }
  }
  navLeft();
  navForward();
  addTurnLeftAction(80);
  addMoveForwardAction(0.65, 70);
  addCheckWallsAction();
}
void turnRightAction()
{
  if(wallFront)
  {
    addIrMonitoringAction(70); 
  }
  else
  {
    const float DIST_OFFSET = 0.8 - (stepsSincelastWallGap/(float)CELL_DISTANCE);
    if(stepsSincelastWallGap != 0 && DIST_OFFSET >= 0.0)
    {
      addBlindMoveForwardAction(DIST_OFFSET, 70);
    }
    else
    {
      wallRight = true;
      return;
    }
  }
  navRight();
  navForward();
  addTurnRightAction(80);
  addMoveForwardAction(0.65, 70);
  addCheckWallsAction();
}
void turnAroundAction()
{
  navRight();
  navRight();
  addIrMonitoringAction(70);
  addTurnAroundAction(80);
  addBlindReverseAction(0.5, 85);
  startOffsetAction();
}