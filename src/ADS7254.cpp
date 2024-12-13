#include "ADS7254.h"
#include <iostream>
#include <Arduino.h>
#include <SPI.h>

using namespace std;

ADS7254::ADS7254(char SCK, char MISO,char MOSI,char CS, SPIClass* bus_SPI){
    
    CS = ChipSelect;

    bus_SPI = new SPIClass;
    spi_adc = bus_SPI;

    bus_SPI->begin(SCK,MISO,MOSI,CS);      

    pinMode(ChipSelect,OUTPUT);
}

void ADS7254::standby(){
    spi_adc->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(ChipSelect, LOW);

    spi_adc->transfer32(0b1000110001100000);

    digitalWrite(ChipSelect, HIGH);
    spi_adc->endTransaction();
}

float ADS7254::ReadValue(uint8_t channel){
    uint16_t raw_data[2];
    uint32_t buffer = 0;

    spi_adc->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(ChipSelect, LOW);
    
    buffer = spi_adc->transfer32((uint32_t)0b0011110001000000);

    spi_adc->endTransaction();
    digitalWrite(ChipSelect, HIGH);
    
    if(channel == 1){
        raw_data[0] = buffer & 0xFFFF0000;
        return raw_data[0]<<1;
    }
    if(channel == 2){
        raw_data[1] = (buffer & 0x0000FFFF) << 16;
        return raw_data[1]<<1;
    }
}