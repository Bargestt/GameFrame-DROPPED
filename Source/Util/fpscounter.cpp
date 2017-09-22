#include "fpscounter.h"

FPSCounter::FPSCounter()
{

}

void FPSCounter::update()
{
    Frames++;
}

void FPSCounter::updateFPS()
{

    float currentTime = glfwGetTime();
    if(currentTime - lastFrame >= 0.5)
    {
        deltaTime = currentTime - lastFrame;
        FPS = (float)Frames / deltaTime;

        lastFrame = currentTime;
        Frames =0;
    }
}
