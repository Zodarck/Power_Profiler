#ifndef ADS7254_H
#define ADS7254_H

#include <Arduino.h>
#include <SPI.h>
class ADS7254
{
private:
    uint8_t ChipSelect;
    SPIClass *spi_adc;

public:
    ADS7254(char CS, SPIClass *bus_SPI);

    uint16_t ReadValue(uint8_t channel);
};

#endif