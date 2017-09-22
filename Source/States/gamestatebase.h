#ifndef GAMESTATE_H
#define GAMESTATE_H

class MasterRenderer;
class Application;


class GameStateBase
{
public:
    GameStateBase(Application& app) : application_(&app)
    {    }
    ~GameStateBase() = default;

    virtual void initialize() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents() = 0;


    virtual void update(float deltaTime) = 0;
    virtual void fixedUpdate() = 0;
    virtual void render(MasterRenderer& renderer) = 0;
protected:
        Application* application_;
private:


};

#endif // GAMESTATE_H
