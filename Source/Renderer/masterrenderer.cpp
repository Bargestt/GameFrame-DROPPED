#include "masterrenderer.h"

MasterRenderer::MasterRenderer()   
{
    //basicShaders/basicTextureLight.frag
    //GameShaders/TerrainShader
    rectRenderer.loadObject(BasicObjects::get()->rectCW);
    rectRenderer.loadShader("res/shader/basicShaders/basicTextureLight.vert",
                                                "res/shader/basicShaders/basicTextureLight.frag");

    cubeRenderer.loadObject(BasicObjects::get()->cube);
    cubeRenderer.loadShader("res/shader/basicShaders/basicTextureLight.vert",
                                                "res/shader/basicShaders/basicTextureLight.frag");



    debugRenderer.loadShader("res/shader/basicShaders/basicColor.vert",
                                                "res/shader/basicShaders/basicColor.frag");

    pyramid.loadObject(BasicObjects::get()->pyramid);
    pyramid.loadShader("res/shader/basicShaders/basicTextureLight.vert",
                       "res/shader/basicShaders/basicTextureLight.frag");

    skyBox.loadObject(BasicObjects::get()->skyBox);
    skyBox.loadShader("res/shader/GameShaders/SkyBoxShader.vert",
                                        "res/shader/GameShaders/SkyBoxShader.frag");

//    terrRenderer.loadShader("res/shader/GameShaders/TerrainShader.vert",
//                            "res/shader/GameShaders/TerrainShader.frag");


    guiRenderer.loadShader("res/shader/GameShaders/GUIShader.vert",
                                                "res/shader/GameShaders/GUIShader.frag");

    lightSources.push_back(LightSource(glm::vec3(0,10,10), glm::vec3(1,1,1) ));

    frameBuffer.initReflection(400, 300);

    rectRenderer.setLightSource(getLightSource());
    cubeRenderer.setLightSource(getLightSource());
    pyramid.setLightSource(getLightSource());
    //terrRenderer.setLightSource(getLightSource());

}

void MasterRenderer::setWindowParams(int width, int height, const Camera &camera)
{
        textRenderer.setCamera(camera);
        guiRenderer.setCamera(camera);
        m_WindowWidth = width;
        m_WindowHeight = height;
}

void MasterRenderer::drawRect(const Entity &rect)
{
    rectRenderer.add(rect);
}

void MasterRenderer::drawCube(const Entity &cube)
{
    cubeRenderer.add(cube);
}

void MasterRenderer::drawText(const TextObject &text)
{
    textRenderer.add(text);
}

void MasterRenderer::drawArrow(const Arrow &arrow)
{
    debugRenderer.addArrow(arrow);
}

void MasterRenderer::drawGUI(const GuiObj &GUI)
{
    guiRenderer.drawImage(GUI);
}

void MasterRenderer::startRender(GLFWwindow *window, const Camera &camera)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//void MasterRenderer::addTerrain(Terrain &terrain)
//{
//    terrRenderer.setTerrain(terrain);
//}



void MasterRenderer::finishRender(GLFWwindow *window, const Camera &camera)
{
    cubeRenderer.add(Entity(getLightSource().getPosition(), {0,0,0}, {0,0}));
    pyramid.add({{3,0,0},{0,0,0}, {1,0}});

    //do rendering stuff


    rectRenderer.render(camera);

    cubeRenderer.render(camera);

    debugRenderer.render(camera);

    pyramid.render(camera);



    //terrRenderer.render(camera);


    //triangleRenderer.render(camera);




    frameBuffer.bind();

    skyBox.render( camera.reflectionCam(1) );

    frameBuffer.unBind();

    skyBox.render(camera);

    textRenderer.render();



//    guiRenderer.drawImage(GuiObj( {-0.5,0.5}, {0.3,0.3}, frameBuffer.m_Texture ) );
//    guiRenderer.render();


    glfwSwapBuffers(window);
    glfwPollEvents();
}

float MasterRenderer::getHight() const
{
    return m_WindowHeight;
}

float MasterRenderer::geyWidth() const
{
    return m_WindowWidth;
}

LightSource &MasterRenderer::getLightSource()
{
    return lightSources.front();
}
