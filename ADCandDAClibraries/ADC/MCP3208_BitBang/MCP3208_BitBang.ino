// Test new MCP3208 library that bit bangs the SPI comms.
// This is needed as a workaround for the current ATTINYcore
// not handing SPI properly.
// CS pin must go low during comms.
// MCP3208 changes Dout state on clock falling edges
// Protocol from datasheet: Page 16
// CS goes low, clock starts and a high start bit is sent
// First bit is 1 for single-ended channel read (0 for differential)
// Second bit is D2
// Third bit is D1
// Fourth bit is D0. These choose the channel to read. CH7 would be 111
// Send another bit that is ignored. In this time, the chip does the sample and read.
// It then ignores all further inputs and outputs
// First bit is null
// Second is B11 (Most significant bit...
// Thirteenth bit is B0 after which Dout goes high impedance
// Set CS high again until next request.

#include <SoftwareSerial.h>

const byte rxPin = -1;
const byte txPin = 6;
SoftwareSerial SSerial(rxPin, txPin);

const int CS = 0;
const int CLK = 1;
const int DOut = 2;
const int DIn = 3;
//int channel = 0;
int D0;
int D1;
int D2;
uint8_t highBits; // contains 4 MSB of voltage reading
uint8_t lowBits;  // contains 8 LSB of voltage reading

void pulseCLK()
{
    digitalWrite(CLK, LOW);
    // delayMicroseconds(4);
    digitalWrite(CLK, HIGH);
}

int read(int channel)
{
    // figure out which channel we are reading
    D0 = (channel >> 0) & B00000001; // first bit of channel
    D1 = (channel >> 1) & B00000001; // second bit
    D2 = (channel >> 2) & B00000001; // third bit
    // init input bits to zero.
    highBits = 0;
    lowBits = 0; 
    //start write by setting CS LOW
    digitalWrite(CS, LOW);
    // start bit HIGH
    digitalWrite(DOut, HIGH);
    // delayMicroseconds(4);
    pulseCLK();
    // single channel HIGH
    digitalWrite(DOut, HIGH);
    // delayMicroseconds(4);
    pulseCLK();
    // send D2
    digitalWrite(DOut, D2);
    // delayMicroseconds(4);
    pulseCLK();
    // send D1
    digitalWrite(DOut, D1);
    // delayMicroseconds(4);
    pulseCLK();
    // send D0
    digitalWrite(DOut, D0);
    // delayMicroseconds(4);
    pulseCLK();
    // pulse the clock to allow the MCP3208 to read the voltage
    pulseCLK();
    // pulse again because a null bit is being sent by the MCP which we ignore
    pulseCLK();

    // Now reading time. The MCP updates on falling edges so we should pulse the clock then read.
    pulseCLK();
    // delayMicroseconds(4);
    highBits |= digitalRead(DIn) << 3;
    pulseCLK();
    // delayMicroseconds(4);
    highBits |= digitalRead(DIn) << 2;
    pulseCLK();
    // delayMicroseconds(4);
    highBits |= digitalRead(DIn) << 1;
    pulseCLK();
    // delayMicroseconds(4);
    highBits |= digitalRead(DIn) << 0;
    // Now 8 LSBs.
    pulseCLK();
    // delayMicroseconds(4);
    lowBits |= digitalRead(DIn) << 7;
    pulseCLK();
    // delayMicroseconds(4);
    lowBits |= digitalRead(DIn) << 6;
    pulseCLK();
    // delayMicroseconds(4);
    lowBits |= digitalRead(DIn) << 5;
    pulseCLK();
    // delayMicroseconds(4);
    lowBits |= digitalRead(DIn) << 4;
    pulseCLK();
    // delayMicroseconds(4);
    lowBits |= digitalRead(DIn) << 3;
    pulseCLK();
    // delayMicroseconds(4);
    lowBits |= digitalRead(DIn) << 2;
    pulseCLK();
    // delayMicroseconds(4);
    lowBits |= digitalRead(DIn) << 1;
    pulseCLK();
    // delayMicroseconds(4);
    lowBits |= digitalRead(DIn) << 0;

    //Finished reading so set chipselect high again.
    digitalWrite(CS, HIGH);
    pulseCLK();
    // put them back together and return them as an integer voltage.
    return (highBits << 8) | lowBits;
    
}

void setup() {
    SSerial.begin(9600);
    SSerial.println("Connected to ATTINY84");
    // put your setup code here, to run once:
    pinMode(CS, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(DOut, OUTPUT);
    pinMode(DIn, INPUT_PULLUP);

    digitalWrite(CS, HIGH);
    digitalWrite(CLK, HIGH);
    digitalWrite(DOut, HIGH);
}

void loop() {
    // put your main code here, to run repeatedly:
    for(int i =0; i < 8; i++)
    {
        SSerial.print(i);
        SSerial.print(": ");
        SSerial.println(read(i));
        delay(10);
    }
}
