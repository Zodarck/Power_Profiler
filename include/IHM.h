#ifndef IHM_H
#define IHM_H
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <stdio.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class IHM {
public:
    Adafruit_SSD1306* screen;

    double pTension, pCourant, pWatt; //dédié affichage valeur, simplification du print et de la valeur de l'unité
    unsigned char multTension, multCourant, multWatt;
    char multValue[3] = { ' ','m','u' };

    IHM(TwoWire* wire);

    void drawUI();      // draw the main menu w/ RT value
    void getData(float tension, float courant);     // update the value of 
    void writeText(int size, int x, int y, string text);
    void writeText(int size, int x, int y, char* text);
    void drawBitmap(char x, char y, char w, char h, unsigned char* bitmap);
};

#endif