#ifndef INA236_H
#define INA236_H
#include "Wire.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#define CONFIG_R 0x00
#define SHUNT_VOLTAGE_R 0x01
#define BUS_VOLTAGE_R 0x02
#define POWER_R 0x03
#define CURRENT_R 0x04
#define CALIB_R 0x05
#define MASK_R 0x06
#define LIMIT_R 0x07

#define INA_ADDR 0x42
#define CONFIGURATION 0b0100000111111111    // maximum conversion time, no avg, 81.92mV shunt
#define SHUNT_CALIB  2097                   // shunt cal value, 2097=30.52µA/LSB (max value) -- 1920=33.33µA/LSB (better math?)

class INA236 {
public:
    unsigned int voltage_r;
    unsigned int current_r;
    unsigned int power_r;

    INA236();
    //void readAlert();
    void writeReg(char reg, char* val, char len);
    unsigned int readReg(char reg);
    float computeVoltage(unsigned int reg_v); //1.6 mV/LSB
    float computeCurrent(unsigned int reg_c); //shunt_cal*current
    float computePower(unsigned int reg_p); //32*shunt_cal*power
};

#endif
