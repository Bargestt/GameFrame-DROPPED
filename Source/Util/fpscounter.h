#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <glheader.h>
#include <iostream>

class FPSCounter
{
public:
    FPSCounter();
    void update();
    void updateFPS();
    int FPS = 0;
protected:
    int Frames = 0;


    float deltaTime, lastFrame =0;
};

#endif // FPSCOUNTER_H
