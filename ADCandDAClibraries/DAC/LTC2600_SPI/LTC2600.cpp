#include "LTC2600.h"

void LTC2600::begin()
{
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
    SPI.begin();
}

void LTC2600::setVoltage(int channel, unsigned int voltage)
{
	// Command: 0 0 1 1 Write to and Update (Power Up) n
    // Address: 0000 is DAC A, 0111 is DAC H
    uint8_t commandAddress = 0b00110000 | (channel & 0b111);
    digitalWrite(_cs, LOW);
    (void) SPI.transfer(commandAddress);
    (void) SPI.transfer(voltage >> 8); // send 8 MSB of voltage
    (void) SPI.transfer(voltage & 0b11111111); // send 8 LSBs of voltage
    digitalWrite(_cs, HIGH);
}

void LTC2600::setAllVoltages(unsigned int voltage)
{
	// Command: 0 0 1 0Write to Input Register n, Update (Power Up) All n
    // Address: 1111 is write to all.
    uint8_t commandAddress = 0b00101111;
    digitalWrite(_cs, LOW);
    (void) SPI.transfer(commandAddress);
    (void) SPI.transfer(voltage >> 8); // send 8 MSB of voltage
    (void) SPI.transfer(voltage & 0b11111111); // send 8 LSBs of voltage
    digitalWrite(_cs, HIGH);
}

