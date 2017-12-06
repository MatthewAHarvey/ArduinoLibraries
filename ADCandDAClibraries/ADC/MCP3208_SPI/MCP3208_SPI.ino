#include <SoftwareSerial.h>
#include <SPI.h>
#include "MCP3208.h"

const byte rxPin = -1;
const byte txPin = 0;
int voltage = 0;
const int CS = 3;

// set up a new serial object
SoftwareSerial SSerial(rxPin, txPin);
MCP3208 adc(CS);

void setup() {
  // put your setup code here, to run once:
  pinMode(txPin, OUTPUT);
  SSerial.begin(9600);
  //pinMode(LEDPin, OUTPUT);
  adc.begin();
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  SSerial.println("Connected to ATTINY84");
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i =0; i<8; i++)
  {
    SSerial.print(i);
    SSerial.print(": ");
    //SSerial.println(random(4095));
    voltage = adc.analogRead(i);
    SSerial.println(voltage);
    delay(200);
  }
}
