// Library for the LTC2600 8 channel 16bit DAC.
// Incomplete functionality but it can set voltages on individual channels
// or all channels at once. Daisychain operation not implemented.
// Default case is to use Arduino's SPI implementation with MOSI, CLK pins being
// fixed. CS pin can be any IO pin.
// Second init case uses bitbanging for use on ATTINY chips using ATTINYcore
// which does not seem to implement hardware SPI correctly. In this case,
// comms with chip are much slower but any IO pins can be used.

#ifndef _LTC2600_H
#define _LTC2600_H

#include <Arduino.h>
#include <SPI.h>

class LTC2600
{
	private:
        // Private functions and variables here.  They can only be accessed
        // by functions within the class.
        uint8_t _cs;

    public:
        // Public functions and variables.  These can be accessed from
        // outside the class.
        LTC2600() : _cs(10) {} // SPI hardware used. CS on D10
        LTC2600(uint8_t cs) : _cs(cs) {} // SPI hardware used
    
        void begin();
        void setVoltage(int channel, unsigned int voltage);
        void setAllVoltages(unsigned int voltage);
};
#endif
