#include <Arduino.h>
#include "IHM.h"
#include "INA236.h"

static IHM* ihm;
static INA236* ina236;

void setup() {
    Wire.begin(SDA, SCL, 50000);
    Serial.begin(115200);
    ihm = new IHM(&Wire);
    ina236 = new INA236();
    ihm->screen->display();
    delay(5000);
}

void loop() {
    delay(500);
    float tension, courant;
    tension = ina236->computeVoltage(ina236->readReg(BUS_VOLTAGE_R));
    courant = ina236->computeCurrent(ina236->readReg(CURRENT_R));
    Serial.printf("%5f - ", tension);Serial.println(courant);
    ihm->getData(tension, courant);
    ihm->drawUI();
    Serial.println("running");
}

//Wire.begin();
//Serial.begin(19200);
//init des objets