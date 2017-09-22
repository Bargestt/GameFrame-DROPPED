#ifndef BASICOBJECTS_H
#define BASICOBJECTS_H

#include <Renderer/Modules/basemodel.h>
#include <ResourceManager/resourcemanager.h>

#include <Renderer/Modules/BasicObjects/rectcw.h>
#include <Renderer/Modules/BasicObjects/cube.h>
#include <Renderer/Modules/BasicObjects/pyramid.h>
#include <Renderer/Modules/BasicObjects/skybox.h>
#include <Renderer/Modules/BasicObjects/rectTopLeft.h>

struct BasicObjects {
private:
    BasicObjects();

    static BasicObjects* instance;
public:
    static BasicObjects* get()
    {
        if(instance == nullptr)
            instance = new BasicObjects();
        return instance;
    }    

    RectCW rectCW;
    RectTopLeft rectTopLeftOrient;
    Cube cube;
    Pyramid pyramid;
    SkyBox skyBox;

};



#endif // BASICOBJECTS_H
