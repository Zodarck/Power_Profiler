#include <Arduino.h>
#include "IHM.h"
#include "INA236.h"

static IHM *ihm;
static INA236 *ina236;

void setup()
{
    Wire.begin();           // initialisation interface Wire pour i2c
    Serial.begin(115200);   // initialisation interface série sur USB
    ihm = new IHM(&Wire);   // instanciation objet ihm avec interface Wire
    ina236 = new INA236();  // instanciation objet ina236
    ihm->screen->display(); // affichage de la valeur par defaut de l'IHM, logo adafruit
    delay(1000);            // blocage pour laisser le logo à l'écran
}

void loop()
{
    delay(50); // rafraichissement max 200Hz
    float tension, courant;
    tension = ina236->computeVoltage(ina236->readWord(BUS_VOLTAGE_R)) + 0.0135; // mesure et calcul tension
    courant = ina236->computeCurrent(ina236->readWord(CURRENT_R)) - 0.0012;     // mesure et calcul courant
    Serial.printf("%3f - ", tension);
    Serial.printf("%3f \n", courant); // debug
    ihm->getData(tension, courant);   // transfert et conversion pour affichage sur IHM
    ihm->drawUI();                    // MaJ IHM
}
