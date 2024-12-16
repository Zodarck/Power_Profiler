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

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

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