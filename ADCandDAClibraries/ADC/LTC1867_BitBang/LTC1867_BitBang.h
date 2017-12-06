// LTC1867 Octal 16 bit ADC Bit Banging library.
// The chip starts taking a sample reading on a rising edge of the chip select pin.
// Send a command setting the channel, at the end of the command, cs goes high starting conversion.
// Wait enough time (1.5 microseconds) for a sample conversion to take place, then put chip select low
// again and clock in the new reading.
// Whilst reading in the new sample, can also set a different channel to be read.

// This library currently only works for 8 Single-Ended mode.
// From datasheet: http://www.farnell.com/datasheets/1930160.pdf
// SD OS S1 S0 COM “+” “–”
// 1  0  0  0  0   CH0 GND
// 1  0  0  1  0   CH2 GND
// 1  0  1  0  0   CH4 GND
// 1  0  1  1  0   CH6 GND
// 1  1  0  0  0   CH1 GND
// 1  1  0  1  0   CH3 GND
// 1  1  1  0  0   CH5 GND
// 1  1  1  1  0   CH7 GND

// SD OS S1 S0 COM UNI SLP
// SD = SINGLE/DIFFERENTIAL BIT
// OS = ODD/SIGN BIT
// S1 = ADDRESS SELECT BIT 1
// S0 = ADDRESS SELECT BIT 0
// COM = CH7/COM CONFIGURATION BIT
// UNI = UNIPOLAR/BIPOLAR BIT
// SLP = SLEEP MODE BIT

// Keep COM low so that all 8 channels are referenced to ground
// Keep UNI low so that it outputs the reading in unipolar binary instead of bipolar 2's complement since
// all readings are positive anyway
// Keep SLP low so that the unit does not go to sleep. It takes 60ms to wake otherwise.

// Nano wiring:
// MISO pin D12
// MOSI pin D11
// SCK pin D13
// but can use any pins

#ifndef _LTC1867_BITBANG_H
#define _LTC1867_BITBANG_H

#include <Arduino.h>

class LTC1867 {
    private:
        // Private functions and variables here.  They can only be accessed
        // by functions within the class.
        uint8_t _cs;
        uint8_t _clk;
        uint8_t _dout;
        uint8_t _din;
        uint8_t commandAddress;

        void pulseClk();
        void sendByte(uint8_t dataByte);
        uint8_t receiveByte();

    public:
        // Public functions and variables.  These can be accessed from
        // outside the class.
        LTC1867(uint8_t cs, uint8_t clk, uint8_t dout, uint8_t din);
    
        void begin();
        uint16_t read(uint8_t channel);
        
};
#endif
