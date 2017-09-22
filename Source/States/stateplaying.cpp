#include "stateplaying.h"

StatePlaying::StatePlaying(Application &app, const Config &config) : GameStateBase(app)
{
    app.getCamera().attach(m_Player);
    setContolWindow(app.getWindow());

    m_Player.connectToterrain(m_World.getTerrain());
    //app.getRenderer().addTerrain(m_World.getTerrain());
}

void StatePlaying::initialize()
{}
void StatePlaying::cleanup()
{}
void StatePlaying::pause()
{}
void StatePlaying::resume()
{}

void StatePlaying::handleEvents()
{
    m_Player.handleInput(m_pWindow);

    static float sleep = 0;
    if(sleep + 0.5 < glfwGetTime())
    {
        if (glfwGetKey(m_pWindow, GLFW_KEY_F1) == GLFW_PRESS){
            togglePolygonMode();
            sleep = glfwGetTime();
        }
    }

}



void StatePlaying::update(float deltaTime)
{
    counter.update();

    m_World.update();

    m_Player.update(deltaTime);

}

void StatePlaying::fixedUpdate()
{
    counter.updateFPS();

    m_World.fixedUpdate();
}

void StatePlaying::render(MasterRenderer &renderer)
{


    //cofigure master renderer
    //tell him what to render
    renderer.drawCube(Entity( {0,0,-6}, {0,0,0},{1,0} ));

    const Camera& cam = application_->getCamera();


    m_World.render(renderer, cam);

    renderer.drawText({std::to_string(counter.FPS), 0.0f, renderer.getHight()-50, 1.0f,glm::vec3(1.0f, 0.3f,0.3f)});

    renderer.drawText({m_Player.statusStr(), 0.0f, renderer.getHight() - 100, 0.5f, glm::vec3(1,0,0)});

    renderer.drawArrow(Arrow(
                            glm::vec3(cam.position.x,   cam.position.y - 0.95, cam.position.z),
                            glm::vec3(0,0,0),
                            0.1f,
                            glm::vec3(0,1,0)));

    renderer.drawArrow(Arrow(
                            glm::vec3(cam.position.x,   cam.position.y - 0.94, cam.position.z),
                            glm::vec3(0,90,0),
                            0.1f,
                            glm::vec3(1,0,0)));


    //test plane

    PlaneR rect = { -1,15,-5,  7,10,5 };

    //PlaneR rect2 = { 6,15,4,  13,10,5 };

    renderer.drawCube({ rect.topLeft(), {0,0,0}, {0.2f, 0.2f, 0.2f} });
    renderer.drawCube({ rect.bottomRight(), {0,0,0}, {0.2f, 0.2f, 0.2f}  });

    renderer.drawCube({ rect.bottomLeft(), {0,0,0}, {0.2f, 0.2f, 0.2f}  });
    renderer.drawCube({ rect.topRight(), {0,0,0}, {0.2f, 0.2f, 0.2f}  });

    //renderer.drawGUI( GuiObj( {0,0},{0.3, 0.3}, ResourceManager::get()->m_TerrainTexture .id()) );
//    rendrer.drawRect(rect);
//    rendrer.drawRect(rect2);




}

void StatePlaying::setContolWindow(GLFWwindow *window)
{
    m_pWindow = window;
}


void StatePlaying::togglePolygonMode()
{
    static bool mode = true;

    if(mode){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        mode = false;
    }
    else{
        mode = true;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
