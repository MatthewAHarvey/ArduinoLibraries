#ifndef _MCP3208_BITBANG_H
#define _MCP3208_BITBANG_H

#include <Arduino.h>


class MCP3208
{
	private:
        // Private functions and variables here.  They can only be accessed
        // by functions within the class.
        uint8_t _cs; // chip select pin
        uint8_t _clk; // clock pin
        uint8_t _din; // digital in pin
        uint8_t _dout; // digital out pin
        uint8_t commandAddress; // used to store the opening command byte

        void pulseClk();
        void sendByte(uint8_t dataByte);
        uint8_t readByte();

    public:
        // Public functions and variables.  These can be accessed from
        // outside the class.
        MCP3208(uint8_t cs, uint8_t clk, uint8_t dout); // SPI hardware used
    
        void begin();
        void read(int channel, unsigned int voltage);
        void readDif(unsigned int voltage);
};
#endif