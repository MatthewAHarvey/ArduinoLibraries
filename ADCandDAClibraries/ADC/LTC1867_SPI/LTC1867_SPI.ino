#include <SoftwareSerial.h>

#include "LTC1867.h"

const byte rxPin = -1;
const byte txPin = 0;
unsigned int voltage = 0;
int channel = 0;
const int CS = 10;

// set up a new serial object
//SoftwareSerial SSerial(rxPin, txPin);
LTC1867 adc(CS);

void setup() {
  // put your setup code here, to run once:
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  //pinMode(LEDPin, OUTPUT);
  adc.begin();
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  Serial.println("Connected to Nano");
}

void loop() {
  // put your main code here, to run repeatedly:
//  for(int i =0; i<8; i++)
//  {
//    Serial.print(i);
//    Serial.print(": ");
//    //SSerial.println(random(4095));
//    voltage = adc.read(i);
//    Serial.println(voltage);
//    delay(200);
//  }
    if(Serial.available())
    {
        channel = Serial.read() - '0';
        Serial.read();
        Serial.read();
        Serial.print("Channel: "); 
        Serial.println(channel);
    }
    voltage = adc.read(channel);
    Serial.println(voltage);
    delay(200);
}
