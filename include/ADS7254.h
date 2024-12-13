#include <Arduino.h>
#include <SPI.h>

#ifndef ADS7254_H
#define ADS7254_H

class ADS7254{
    private :
    uint8_t ChipSelect;
    SPIClass* spi_adc;

    public :
    
    ADS7254(char SCK, char MISO,char MOSI,char CS, SPIClass* bus_SPI);

    float ReadValue(uint8_t channel);
    void standby();
};

#endif