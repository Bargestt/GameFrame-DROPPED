#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <vector>
#include <ctime>
#include <chrono>

#include <glheader.h>

#include <Renderer/masterrenderer.h>

#include "States/gamestatebase.h"
#include "States/stateplaying.h"
#include "States/Events/event.h"

#include "context.h"


class Application
{
public:
    Application(Config& config);
    void run();

    template<typename T, typename... Args>
    void pushState(Args&&... args)
    {
        states_.push_back(std::make_unique<T> (std::forward<Args>(args)...));
        auto& t = states_.back();
        t->initialize();
    }

    void popState();

    Camera& getCamera();
    GLFWwindow* getWindow();
    MasterRenderer& getRenderer();

private:
    void handleInput(GLFWwindow *window);


    Context context_;
    MasterRenderer rendrer_;
    Camera camera_;



    std::vector<std::unique_ptr<GameStateBase>> states_;
    bool shouldPopState = false;


    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow *window);
};

#endif // APPLICATION_H
