#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include <glheader.h>



#include <Renderer/Modules/textrenderer.h>
#include <Renderer/Modules/lightsource.h>
#include <Renderer/Modules/trianglerenderer.h>


#include <Renderer/Modules/guirenderer.h>
#include <Renderer/Modules/dynamicobject.h>
#include <Renderer/Modules/skyboxrenderer.h>

#include <Renderer/Modules/framebuffer.h>


#include <Renderer/Modules/Debug/debugelements.h>


#include <Renderer/Modules/BasicObjects/basicobjects.h>
//#include <Renderer/Modules/terrainrenderer.h>


class MasterRenderer
{
public:
    MasterRenderer();

    void setWindowParams(int width, int height, const Camera &camera);

    void drawRect(const Entity &rect);
    void drawCube(const Entity &cube);
    void drawText(const TextObject& text);
    void drawArrow(const Arrow& arrow);
    //void addTerrain(Terrain &terrain);
    void drawGUI(const GuiObj &GUI);

    void startRender(GLFWwindow *window, const Camera &camera);

    void finishRender(GLFWwindow *window, const Camera &camera);


    float getHight() const;
    float geyWidth() const;

    LightSource &getLightSource();

    FrameBuffer frameBuffer;
    SkyBoxRenderer   skyBox;
private:

    //renderer subordinates
    std::vector<LightSource> lightSources;
    LightSource lightSource;

    DynamicObject   rectRenderer;
    DynamicObject   cubeRenderer;
    DynamicObject   pyramid;




    TextRenderer textRenderer;
    GuiRenderer guiRenderer;
    DebugElements debugRenderer;




    float m_WindowHeight;
    float m_WindowWidth;
};

#endif // MASTERRENDERER_H
