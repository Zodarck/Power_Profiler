#ifndef LMP8358_H
#define LMP8358_H

class LMP8358{
    public :
    int gain;
    
    LMP8358(char SCK, char MISO,char MOSI,char CS);

    void setGain(int G); //Gain available : 10 / 20 / 50 / 100 / 200 / 500 / 1000
    void shutdown();
    private :
};

#endif