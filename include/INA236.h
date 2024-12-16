#ifndef INA236_H
#define INA236_H
#include "Wire.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#define CONFIG_R 0x00                       // registre pour configurer l'ina236 (def: 0b0100 0001 0010 0111 -- 0x4127)
#define SHUNT_VOLTAGE_R 0x01                // registre de sortie de l'ADC pour mesure courant
#define BUS_VOLTAGE_R 0x02                  // registre de sortie de l'ADC pour mesure tension (IN- / GND)
#define POWER_R 0x03                        // valeur calculée de puissance, proportionnelle à la valeur du shunt
#define CURRENT_R 0x04                      // valeur calculée du courant en fonction de SHUNT_VOLTAGE_R et de CALIB_R
#define CALIB_R 0x05                        // registre contenant une valeur arbitraire en fonction du shunt et du courant max
#define MASK_R 0x06                         // registre d'activation par masquage des alertes liées à la valeur limite
#define LIMIT_R 0x07                        // registre contenant la valeur limite selon l'alerte activée

#define INA_ADDR 0x42                       // adresse i2c 7 bits

class INA236 {
public:
    unsigned int voltage_r;                 // valeur issue de BUS_VOLTAGE_R
    unsigned int current_r;                 // valeur issue de CURRENT_R
    unsigned int power_r;                   // valeur issue de POWER_R

    INA236();
    //void readAlert(); // fonction non utilisée
    void writeWord(char reg, const char* val, char len);  // écriture d'un mot i2c depuis un tableau de char
    unsigned int readWord(char reg);                // lecture d'un mot i2c vers un entier 16bits
    float computeVoltage(unsigned int reg_v);       // conversion BUS_VOLTAGE_R vers f16 -- 1.6 mV/LSB
    float computeCurrent(unsigned int reg_c);       // conversion CURRENT_R vers f16 -- 30.52µA/LSB
    float computePower(unsigned int reg_p);         // conversion POWER_R vers f16 -- 32 * 30.52µW/LSB
};

#endif
