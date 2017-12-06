#include "LTC2600_BitBang.h"

LTC2600::LTC2600(uint8_t cs, uint8_t clk, uint8_t dout)
{
    _cs = cs;
    _clk = clk;
    _dout = dout;
}

void LTC2600::begin()
{
    pinMode(_cs, OUTPUT);
    pinMode(_clk, OUTPUT);
    pinMode(_dout, OUTPUT);
    
    digitalWrite(_cs, HIGH);
    digitalWrite(_clk, HIGH);
    digitalWrite(_dout, HIGH);   
}

void LTC2600::setVoltage(int channel, unsigned int voltage)
{
	// Command: 0 0 1 1 Write to and Update (Power Up) n
    // Address: 0000 is DAC A, 0111 is DAC H
    _commandAddress = 0b00110000 | (channel & 0b111);
    digitalWrite(_cs, LOW);
    sendByte(_commandAddress); // Send command bits.
    sendByte(voltage >> 8); // Send 8 MSB of voltage
    sendByte(voltage & B11111111); // Send 8 LSB of voltage
    digitalWrite(_cs, HIGH);
}

void LTC2600::setAllVoltages(unsigned int voltage)
{
	// Command: 0 0 1 0Write to Input Register n, Update (Power Up) All n
    // Address: 1111 is write to all.
    _commandAddress = 0b00101111;
    digitalWrite(_cs, LOW);
    sendByte(_commandAddress); // Send command bits.
    sendByte(voltage >> 8); // Send 8 MSB of voltage
    sendByte(voltage & B11111111); // Send 8 LSB of voltage
    digitalWrite(_cs, HIGH);
}

void LTC2600::sendByte(uint8_t dataByte)
{
    for(int i = 7; i > -1; i--)
    {
        digitalWrite(_dout, ((dataByte >> i) & B00000001));
        pulseClk();
    }
}
void LTC2600::pulseClk()
{
    digitalWrite(_clk, LOW);
    digitalWrite(_clk, HIGH);
}

