
// Bit bang example for LTC1867 octal 16 bit ADC

#include "LTC1867_BitBang.h"

const int cs = 10;
const int din = 12;
const int dout = 11;
const int clk = 13;

int channel;
unsigned int voltage;

// set up a new serial object
//SoftwareSerial SSerial(rxPin, txPin);
LTC1867 adc(cs, clk, dout, din);

void setup() {
  // put your setup code here, to run once:
  //pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  //pinMode(LEDPin, OUTPUT);
  adc.begin();
  Serial.println("Connected to Nano");
  Serial.println("Test LTC1867 bit bang comms.");
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
