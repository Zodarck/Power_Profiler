#include "LMP8358.h"
#include <iostream>
#include <Arduino.h>
#include <SPI.h>
#include <LMP8358.h>

using namespace std;

LMP8358::LMP8358(uint8_t SCK, uint8_t MISO,uint8_t MOSI,uint8_t CS){
    SPI.begin(SCK,MISO,MOSI,CS);
}

void LMP8358::setGain(uint16_t G){
    if(G == 10){
        SPI.write(0b0000001100000000);
    }
    if(G == 20){
        SPI.write(0b0000001100000100);
    }
    if(G == 50){
        SPI.write(0b0000001100000010);
    }
    if(G == 100){
        SPI.write(0b0000001100000110);
    }
    if(G == 200){
        SPI.write(0b0000001100000001);
    }
    if(G == 500){
        SPI.write(0b0000001100000101);
    }
    if(G == 1000){
        SPI.write(0b0000001100000011);
    }
}

void LMP8358 :: shutdown(){
    SPI.write(0b0000001100000000);
}