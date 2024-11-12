#include "LMP8358.h"
#include <iostream>
#include <Arduino.h>
#include <SPI.h>

using namespace std;

LMP8358::LMP8358(char SCK, char MISO,char MOSI,char CS){
    SPI.begin(SCK,MISO,MOSI,CS);
}

void LMP8358::setGain(int G){
    gain = G;
    
    if(gain == 10){
        SPI.write(0b0000001100000 000);
    }
    if(gain == 20){
        SPI.write(0b0000001100000 100);
    }
    if(gain == 50){
        SPI.write(0b0000001100000 010);
    }
    if(gain == 100){
        SPI.write(0b0000001100000 110);
    }
    if(gain == 200){
        SPI.write(0b0000001100000 001);
    }
    if(gain == 500){
        SPI.write(0b0000001100000 101);
    }
    if(gain == 1000){
        SPI.write(0b0000001100000 011);
    }
}

void shutdown(){
    SPI.write(0b0000001100000000);
}