#include "IHM.h"
#include <iostream>

using namespace std;

IHM::IHM(TwoWire* wire) { // initialisation du SSD1306
    screen = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, wire, OLED_RESET);
    if (!screen->begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // if fail
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }
}

void IHM::drawUI() {
    screen->clearDisplay();
    char tLine[24];
    char cLine[24];
    char pLine[24];
    sprintf(tLine, "Tension %9.02f %cV", pTension, multValue[multTension]);
    sprintf(cLine, "Courant %9.02f %cA", pCourant, multValue[multCourant]);
    sprintf(pLine, "Watt %12.02f %cW", pWatt, multValue[multWatt]);
    writeText(1, 0, 0, tLine);
    writeText(1, 0, 22, cLine);
    writeText(1, 0, 44, pLine);
    screen->display();
}
void IHM::getData(float tension, float courant) {
    multTension = 0;
    multCourant = 0;
    multWatt = 0;

    pTension = tension;
    pCourant = courant;
    pWatt = (courant * tension);

    // Volt
    if (tension < 1.0) {       //mV
        if (tension < 0.001) {  //uV
            multTension = 2;
            pTension *= 1000000.0;
        }
        else {
            multTension = 1;
            pTension *= 1000.0;
        }
    }

    // Ampère
    if (courant < 1.0) {       //mA
        if (courant < 0.001) {  //uV
            multCourant = 2;
            pCourant *= 1000000.0;
        }
        else {
            multCourant = 1;
            pCourant *= 1000.0;
        }
    }

    // Watt
    if (courant * tension < 1.0) {       //mV
        if (courant * tension < 0.001) {  //uV
            multWatt = 2;
            pWatt *= 1000000.0;
        }
        else {
            multWatt = 1;
            pWatt *= 1000.0;
        }
    }

}
void IHM::writeText(int size, int x, int y, string text) {

    screen->setTextSize(size);      // Normal 1:1 pixel scale
    screen->setTextColor(SSD1306_WHITE); // Draw white text
    screen->setCursor(x, y);     // Start at top-left corner
    screen->cp437(true);         // Use full 256 char 'Code Page 437' font

    // Not all the characters will fit on the display. This is normal.
    // Library will draw what it can and the rest will be clipped.
    for (int16_t i = 0; i < int(text.length()); i++) {
        screen->write(text[i]);
    }
}
void IHM::writeText(int size, int x, int y, char* text) {

    screen->setTextSize(size);  // Upscale factor
    screen->setTextColor(SSD1306_WHITE); // Draw white text
    screen->setCursor(x, y);    // 0,0 at top-left corner
    screen->cp437(true);        // Use full 256 char 'Code Page 437' font
    screen->printf(text);       // Convert text to pixel, then send to SSD1306
}

void IHM::drawBitmap(char x, char y, char w, char h, unsigned char* bitmap) {
    screen->drawBitmap(x, y, bitmap, w, h, 1);
}

