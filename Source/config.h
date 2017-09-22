#ifndef CONFIG_H
#define CONFIG_H

struct Config
{
    int window_Height = 1020;
    int window_Width  = 1980;

    bool isFullscreen = false;
    bool showCursor = false;

    int renderDistance = 100;
    int fov = 45;

    int limitFPS = 60;

};

#endif // CONFIG_H
