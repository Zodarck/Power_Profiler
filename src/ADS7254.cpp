#include "ADS7254.h"
#include <Arduino.h>
#include <SPI.h>

ADS7254::ADS7254(char CS, SPIClass *bus_SPI)
{

    ChipSelect = CS;
    spi_adc = bus_SPI;

    pinMode(ChipSelect, OUTPUT);

    spi_adc->write32((uint32_t)0b1000110001000000);
}

float ADS7254::ReadValue(uint8_t channel)
{
    uint16_t raw_data[2];
    uint32_t buffer;

    digitalWrite(ChipSelect, LOW);
    spi_adc->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    
    buffer = spi_adc->transfer32((uint32_t)0b0100110001000000); 
    spi_adc->endTransaction();
    digitalWrite(ChipSelect, HIGH);

    if (channel == 1)
    {
        raw_data[0] = buffer & 0b11111111111111110000000000000000;
        return raw_data[0] << 16;
    }
    if (channel == 2)
    {
        raw_data[1] = (buffer & 0x0000FFFF) << 16;
        return raw_data[1] << 1;
    }
}