#ifndef LMP8358_H
#define LMP8358_H

#include <Arduino.h>
#include <SPI.h>
class LMP8358
{
private:
    uint8_t ChipSelect;
    SPIClass *spi_pga;

public:
    LMP8358(char CS, SPIClass *bus_SPI);

    void setGain(uint16_t G); // Gain available : 10 | 20 | 50 | 100 | 200 | 500 | 1000
    void shutdown();
};

#endif