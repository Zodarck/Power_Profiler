#include "INA236.h"
#include <Arduino.h>

using namespace std;

INA236::INA236() {
    const char configuration[] = { 0b01000011,0b11000111 };
    // maximum conversion time, no avg, 81.92mV shunt
    const char shunt_calib[] = { 0b00001000,0b00110001 };
    // shunt cal value, 2097=30.52µA/LSB (max value) -- 1920=33.33µA/LSB (meilleur math?)

    writeWord(CONFIG_R, configuration, 2);
    delay(50); // delay de relax de l'INA236
    writeWord(CALIB_R, shunt_calib, 2);
}
//void INA236::readAlert() {}

void INA236::writeWord(char reg, const char* val, char len) {   // tableau de char MSB first
    Wire.beginTransmission(INA_ADDR);   // start bit
    Wire.write(reg);                    // reg select
    for (int i = 0; i < len; i++) {     // bit writing
        Wire.write(val[i]);
    }
    Wire.endTransmission();             // stop bit
}

unsigned int INA236::readWord(char reg) {
    Wire.beginTransmission(INA_ADDR);               // start bit
    Wire.write(reg);                                // reg select
    Wire.endTransmission();                         // stop bit

    Wire.requestFrom(INA_ADDR, 2);                  // lecture Word
    while (Wire.available() < 2);                   // attente reception
    return Wire.read() * 0xFF + Wire.read();        // 1st call : MSB - 2nd call : LSB
}

float INA236::computeVoltage(unsigned int reg_v) {  // 1,6mV / LSB
    return (float)reg_v * 0.0016;
}
float INA236::computeCurrent(unsigned int reg_c) {  // 30,52µA / LSB
    return (float)reg_c * 0.00003052;
}
float INA236::computePower(unsigned int reg_p) {    // 976,64µW / LSB
    return (float)reg_p * 0.00097664;
}