#ifndef STATEPLAYING_H
#define STATEPLAYING_H



#include <glheader.h>



#include <Renderer/masterrenderer.h>

#include <States/gamestatebase.h>
#include "States/Events/event.h"

#include <Util/fpscounter.h>

#include <World/world.h>



#include "config.h"
#include "player.h"

#include "application.h"

class StatePlaying : public GameStateBase
{
public:
    StatePlaying(Application& app, const Config& config);

     void initialize()     override;
     void cleanup()  override;

     void pause()    override;
     void resume()   override;

     void handleEvents()     override;


     void update(float deltaTime)   override;
     void fixedUpdate() override;
     void render(MasterRenderer& renderer)   override;

     void setContolWindow(GLFWwindow* window);
private:
    Player m_Player;
    GLFWwindow* m_pWindow;

    FPSCounter counter;


    World m_World;


    void togglePolygonMode();

};

#endif // STATEPLAYING_H
