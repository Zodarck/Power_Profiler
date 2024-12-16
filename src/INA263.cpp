#include "INA236.h"
#include <Arduino.h>

using namespace std;

INA236::INA236() {
    const unsigned char configuration[] = { 0b01000011,0b11000111 }; // minimum conversion time, no avg, 81.92mV shunt
    const unsigned char shunt_calib[] = { 0b00001000,0b00110001 }; // minimum conversion time, no avg, 81.92mV shunt
    Wire.beginTransmission(INA_ADDR);
    Wire.write(CONFIG_R);
    for (int i = 0; i < 2; i++) {
        Wire.write(configuration[i]);
    }
    Wire.endTransmission();
    delay(50);
    Wire.beginTransmission(INA_ADDR);
    Wire.write(CALIB_R);
    for (int i = 0; i < 2; i++) {
        Wire.write(shunt_calib[i]);
    }
    Wire.endTransmission();
}
//void INA236::readAlert() {}

void INA236::writeReg(char reg, char* val, char len) { //mettre un tableau de char
    Wire.beginTransmission(reg);
    for (int i = 0; i < len; i++) {
        Wire.write(val[i]);
    }
    Wire.endTransmission();
}

unsigned int INA236::readReg(char reg) {
    unsigned int value;
    char i = 0;
    Wire.beginTransmission(INA_ADDR);
    Wire.write(reg);
    Serial.printf("reg %d :", reg);
    Wire.endTransmission();
    Wire.requestFrom(INA_ADDR, 2);
    while (Wire.available() < 2);
    value = Wire.read() * 0xFF;
    value += Wire.read();
    Serial.printf("value %x\n\n", value);


    return value;
}

float INA236::computeVoltage(unsigned int reg_v) {
    return (float)reg_v * 0.0016;
}
float INA236::computeCurrent(unsigned int reg_c) {
    return (float)reg_c * 0.00003052;
}
float INA236::computePower(unsigned int reg_p) {
    return (float)reg_p * 0.00097664;
}