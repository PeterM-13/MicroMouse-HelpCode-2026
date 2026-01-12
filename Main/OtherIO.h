#ifndef Other_IO
#define Other_IO
// (Other Input / Output)

#include "Globals.h"
#include "YourAlgorithm.h"


extern unsigned int pulseLedDelay_ms;
extern unsigned int pulseBuzzerDelay_ms;


void setupOtherIO();
void loopOtherIO();

void pushButtonPressed();
bool checkButtonForPress();

void ledOn();
void ledOff();
void arduinoLedOn();
void arduinoLedOff();

void buzzerOn();
void buzzerOff();

void pulseLedLoop();
void pulseBuzzerLoop();

#endif // Other_IO