#include "MicroTimer.h"

long halfSecond = 5e5;
MicroTimer eventTimer;
MicroTimer tenSecondTimer(10e6);
MicroTimer totalTimer;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Connected to MicroTimer test.");
    
    eventTimer.init(halfSecond);
    tenSecondTimer.reset();
    totalTimer.reset();
}

void loop() {
  // put your main code here, to run repeatedly:
    if(eventTimer.timedOut(true))
    { 
        Serial.print("Half second elapsed: ");
        Serial.println(totalTimer.elapsed());
    }
    if(tenSecondTimer.timedOut(false))
    {
        Serial.println("Tens seconds elapsed.");
    }
}
