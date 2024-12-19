#ifndef LMP8358_H
#define LMP8358_H

#include <Arduino.h>
class LMP8358
{
public:
    LMP8358(uint8_t SCK, uint8_t MISO, uint8_t MOSI, uint8_t CS);

    void setGain(uint16_t G); // Gain available : 10 | 20 | 50 | 100 | 200 | 500 | 1000
    void shutdown();
};

#endif