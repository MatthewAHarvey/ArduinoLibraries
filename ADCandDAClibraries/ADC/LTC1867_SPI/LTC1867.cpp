#include "LTC1867.h"

void LTC1867::begin() {
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);
  SPI.begin();
}

uint16_t LTC1867::read(uint8_t channel) {
  // First MSB is 1 because single ended channel reading mode
  // Second MSB is 0 if even number channel and 1 if odd.
  // Third and Fourth bits are the channel address bits. Take channel number and bitshift right. See datasheet.
  // Channel anded with 7 because it can't go higher than this. If 8 or higher was accidentally selected, nonsense
  // would then be sent to the chip since the higher bits would be overwritten.
  uint8_t addr = 0b10000100 | (((channel & 0b111) % 2) << 6) | (((channel & 0b111) >> 1) << 4);
  digitalWrite(_cs, LOW);
  (void) SPI.transfer(addr);
  (void) SPI.transfer(0); // send a second byte of zeros because the chip expects 16 clock pulses
  digitalWrite(_cs, HIGH);
  delayMicroseconds(4); // minimum reliable microsecond delay to ensure a sample has been converted.

  digitalWrite(_cs, LOW);
  uint8_t b1 = SPI.transfer(0);
  uint8_t b2 = SPI.transfer(0);
  digitalWrite(_cs, HIGH);

  return (b1 << 8) | b2; // shift the 8 MSB along and combine with the 8 LSB to get 16 bit number
}

