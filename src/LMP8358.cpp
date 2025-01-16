#include "LMP8358.h"
#include <Arduino.h>
#include <SPI.h>

LMP8358::LMP8358(char CS, SPIClass *bus_SPI)
{
    ChipSelect = CS;
    spi_pga = bus_SPI;

    pinMode(ChipSelect, OUTPUT);
}

void LMP8358::setGain(uint16_t G)
{
    switch (G)
    {
    case 10:
        digitalWrite(ChipSelect, LOW);
        spi_pga->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

        spi_pga->transfer16(0b0000001100000000);

        spi_pga->endTransaction();
        digitalWrite(ChipSelect, HIGH);
        break;
    case 20:
        digitalWrite(ChipSelect, LOW);
        spi_pga->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

        spi_pga->transfer16(0b0000001100000100);

        spi_pga->endTransaction();
        digitalWrite(ChipSelect, HIGH);
        break;
    case 50:
        digitalWrite(ChipSelect, LOW);
        spi_pga->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

        spi_pga->transfer16(0b0000001100000010);

        spi_pga->endTransaction();
        digitalWrite(ChipSelect, HIGH);
        break;
    case 100:
        digitalWrite(ChipSelect, LOW);
        spi_pga->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

        spi_pga->transfer16(0b0000001100000110);

        spi_pga->endTransaction();
        digitalWrite(ChipSelect, HIGH);
        break;
    case 200:
        digitalWrite(ChipSelect, LOW);
        spi_pga->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

        spi_pga->transfer16(0b0000001100000001);

        spi_pga->endTransaction();
        digitalWrite(ChipSelect, HIGH);
        break;
    case 500:
        digitalWrite(ChipSelect, LOW);
        spi_pga->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

        spi_pga->transfer16(0b0000001100000101);

        spi_pga->endTransaction();
        digitalWrite(ChipSelect, HIGH);
        break;
    case 1000:
        digitalWrite(ChipSelect, LOW);
        spi_pga->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

        spi_pga->transfer16(0b0000001100000011);

        spi_pga->endTransaction();
        digitalWrite(ChipSelect, HIGH);
        break;
    }
}

void LMP8358 ::shutdown()
{
    digitalWrite(ChipSelect, LOW);
    spi_pga->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    spi_pga->transfer16(0b0000001100000000);

    spi_pga->endTransaction();
    digitalWrite(ChipSelect, HIGH);
}