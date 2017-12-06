#include "LTC2600.h"

const int CS = 10; // chip select pin

LTC2600 dac(CS);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("LTC2600 Nano Test");
    dac.begin();
}

void loop() {
    // put your main code here, to run repeatedly:
    for(int i = 0; i < 2^16; i++)
    {
        //dac.setVoltage(0, i);
        dac.setAllVoltages(i);
    }
    Serial.println("Sweep completed.");
}
