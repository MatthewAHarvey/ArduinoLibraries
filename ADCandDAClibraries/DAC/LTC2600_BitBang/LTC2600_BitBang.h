// Library for the LTC2600 8 channel 16bit DAC.
// Incomplete functionality but it can set voltages on individual channels
// or all channels at once. Daisychain operation not implemented.
// Default case is to use Arduino's SPI implementation with MOSI, CLK pins being
// fixed. CS pin can be any IO pin.
// Second init case uses bitbanging for use on ATTINY chips using ATTINYcore
// which does not seem to implement hardware SPI correctly. In this case,
// comms with chip are much slower but any IO pins can be used.

#ifndef _LTC2600_BITBANG_H
#define _LTC2600_BITBANG_H

#include <Arduino.h>


class LTC2600
{
	private:
        // Private functions and variables here.  They can only be accessed
        // by functions within the class.
        uint8_t _cs;
        uint8_t _clk;
        uint8_t _dout;
        uint8_t _commandAddress;

        void pulseClk();
        void sendByte(uint8_t dataByte);

    public:
        // Public functions and variables.  These can be accessed from
        // outside the class.
        LTC2600(uint8_t cs, uint8_t clk, uint8_t dout); 
    
        void begin();
        void setVoltage(int channel, unsigned int voltage);
        void setAllVoltages(unsigned int voltage);
};
#endif
