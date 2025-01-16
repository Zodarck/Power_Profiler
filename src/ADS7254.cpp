#include "ADS7254.h"
#include <Arduino.h>
#include <SPI.h>

#include <stdio.h>
#include <stdint.h>

uint16_t binaryToDecimal(uint16_t *binary);

ADS7254::ADS7254(char CS, SPIClass *bus_SPI)
{

    ChipSelect = CS;
    spi_adc = bus_SPI;

    pinMode(ChipSelect, OUTPUT);

    digitalWrite(ChipSelect, LOW);
    spi_adc->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    delay(10);

    spi_adc->transfer16(0b1000110001000000);

    spi_adc->endTransaction();
    digitalWrite(ChipSelect, HIGH);
}

uint16_t ADS7254::ReadValue(uint8_t channel)
{
    uint16_t raw_data = 0;
    uint32_t buffer = 0;

    digitalWrite(ChipSelect, LOW);
    spi_adc->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    delay(10);

    //buffer = spi_adc->transfer32(0);

    spi_adc->endTransaction();
    digitalWrite(ChipSelect, HIGH);

    // Serial.printf("RAW: %u\n",raw_data);

    switch (channel)
    {
    case 1:
        raw_data = buffer >> 1;
        break;
    case 2:
        raw_data = buffer >> 17;
        break;
    }

    // raw_data = binaryToDecimal(&raw_data);
    //  raw_data = raw_data & 0xFFF;
    return raw_data & 0xFFF;
}

uint16_t binaryToDecimal(uint16_t *binary)
{
    int16_t decimal = 0;
    int isNegative = (binary[0] == '1'); // Vérifie si c'est un nombre négatif (complément à 2)

    for (int i = 0; i < 16; i++)
    {
        decimal = (decimal << 1) | (binary[i] - '0'); // Décalage à gauche et ajout du bit courant
    }

    // Si le nombre est négatif, on effectue la conversion du complément à 2
    if (isNegative)
    {
        decimal = decimal - (1 << 16);
    }

    return decimal;
}
