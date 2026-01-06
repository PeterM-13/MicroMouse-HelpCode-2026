#include "OtherIO.h"

// Push Button vars
const int PUSH_BUTTON_PIN = A6;
bool pushButtonState = false;
bool pushButtonPrevState = false;

// LED variabes
const int LED_PIN = 9;
bool pulseLedState = false;
unsigned int pulseLedDelay_ms = 0;
long prevPulseLedTime = 0;

// Buzzer variables
const int BUZZER_PIN = 8;
bool pulseBuzzerState = false;
unsigned int pulseBuzzerDelay_ms = 0;
long prevPulseBuzzerTime = 0;

// Spare pins
const int SPARE_PIN_1 = 10;
const int SPARE_PIN_2 = 12;


void setupOtherIO()
{
  // Pin Setup
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SPARE_PIN_1, OUTPUT);
  pinMode(SPARE_PIN_2, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(SPARE_PIN_1, LOW);
  digitalWrite(SPARE_PIN_2, LOW);

  //  Set Interrupt(s) 
  attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON_PIN), pushButtonPressed, RISING);
}

void loopOtherIO()
{
  checkButtonForPress();

  pulseLedLoop();
}

// -------- Button Functions -------
void pushButtonPressed()
{
  if(pushButtonState == pushButtonPrevState)
  {
    pushButtonState = !pushButtonState;
  }
}

bool checkButtonForPress()
{
  if(pushButtonState != pushButtonPrevState)
  {
    print("EVENT: Button Pressed");
    ledOn();
    delay(200); // Allow button bounce
    ledOff();
    pushButtonPrevState = pushButtonState;
    
    // Start Algorithm
    fatalError = false;
    collisionDetectionActive = false;
    startAlgorithm = true;
    clearBuffer(actionBuffer);
    setupAlgorithm();
    return true;
  }
  return false;
}

// ------- LED Functions -------
void ledOn()
{
  digitalWrite(LED_PIN, HIGH);
}
void ledOff()
{
  digitalWrite(LED_PIN, LOW);
}

// The little orange LED on the Arduino itself.
void arduinoLedOn()
{
  digitalWrite(LED_BUILTIN, HIGH);
}
void arduinoLedOff()
{
  digitalWrite(LED_BUILTIN, LOW);
}

void pulseLedLoop()
{
  long currentPulseLedTime = millis();
  if (pulseLedDelay_ms > 0 && currentPulseLedTime > prevPulseLedTime + pulseLedDelay_ms) 
  {
    digitalWrite(LED_PIN, pulseLedState);
    pulseLedState = !pulseLedState;
    prevPulseLedTime = currentPulseLedTime;
  }
}


// ------ Buzzer Functions -------
void buzzerOn()
{
  digitalWrite(BUZZER_PIN, HIGH);
}
void buzzerOff()
{
  digitalWrite(BUZZER_PIN, LOW);
}

void pulseBuzzerLoop()
{
  long currentPulseBuzzerTime = millis();
  if (pulseBuzzerDelay_ms > 0 && currentPulseBuzzerTime > prevPulseBuzzerTime + pulseBuzzerDelay_ms) 
  {
    digitalWrite(BUZZER_PIN, pulseBuzzerState);
    pulseBuzzerState = !pulseBuzzerState;
    prevPulseBuzzerTime = currentPulseBuzzerTime;
  }
}





