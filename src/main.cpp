#include <Arduino.h>
#include <SPI.h>
#include "LMP8358.h"
#include "ADS7254.h"

#define CS_ADC 0

SPIClass* bus_SPI;

void setup() {
    Serial.begin(115200);
}

void loop() {
    
    ADS7254 ADC(SCK,MISO,MOSI, CS_ADC, bus_SPI);
    LMP8358 PGA(SCK,MISO,MOSI,SS);

    float voltage = 0;
    float current = 0;

    voltage = (ADC.ReadValue(1)*2.5)/65528;
    voltage = voltage * 0.141; //Voltage before the voltage divider
    current = (ADC.ReadValue(2)*2.5)/65528;
    current = current/0.08; //Current through the 80mOhm shunt resistor

    //Display raw values
    Serial.print("Raw voltage : ");
    Serial.println(ADC.ReadValue(1));
    Serial.print("Raw current : ");
    Serial.println(ADC.ReadValue(2));

    //Display converted values
    Serial.print("Voltage : ");
    Serial.print(voltage);
    Serial.println("V");
    Serial.print("Current : ");
    Serial.print(current);
    Serial.println("A");

    delay(1000);
}
