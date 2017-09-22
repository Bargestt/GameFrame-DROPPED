#ifndef SKYBOXRENDERER_H
#define SKYBOXRENDERER_H

#include <Renderer/Modules/dynamicobject.h>


class SkyBoxRenderer : public DynamicObject
{

public:
    SkyBoxRenderer();    


    // RenderObject interface
public:
    void render(const Camera &camera) override;

    // RenderObject interface
public:
    void loadObject(const Mesh &mesh) override;
};

#endif // SKYBOXRENDERER_H
