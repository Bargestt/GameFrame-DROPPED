#include "application.h"



Application::Application(Config& config) :
                                        context_(config),
                                        camera_(config)
{

    pushState<StatePlaying>(*this,config);

    //==================== CALLBACKS====================

    glfwSetFramebufferSizeCallback(context_.window, Application::framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(context_.window, );

    rendrer_.setWindowParams(config.window_Width,config.window_Height,camera_);
}

void Application::run()
{
    constexpr int ticksPerSecond = 60;
    float tickTime = 1.0f / ticksPerSecond;


    float lastFrame;
    float lag = 0;

    while(!glfwWindowShouldClose(context_.window) && !states_.empty())
    {


        float deltaTime,  currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        lag += deltaTime;


        auto& state = *states_.back();

        state.handleEvents();

        state.update(deltaTime);
        if(lag >= tickTime){
            state.fixedUpdate();
            lag -= tickTime;
        }

        camera_.updateMatrices();

        rendrer_.startRender(context_.window, camera_);
        state.render(rendrer_);        
        rendrer_.finishRender(context_.window, camera_);


        handleInput(context_.window);

        if(shouldPopState) {
            shouldPopState = false;
            popState();
        }
    }

}

void Application::popState()
{
    states_.pop_back();
}

Camera &Application::getCamera()
{
    return camera_;
}

GLFWwindow *Application::getWindow()
{
    return context_.window;
}

MasterRenderer &Application::getRenderer()
{
    return rendrer_;
}

void Application::handleInput(GLFWwindow *window)
{
    if (glfwGetKey(context_.window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        shouldPopState = true;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rendrer_.getLightSource().move(0,0,0.1);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rendrer_.getLightSource().move(0,0,-0.1);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rendrer_.getLightSource().move(-0.1,0,0);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rendrer_.getLightSource().move(0.1,0,0);
    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
        rendrer_.getLightSource().move(0,0.1,0);
    if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
        rendrer_.getLightSource().move(0,-0.1,0);





//            glfwSetWindowShouldClose(context_.window, true);

}


//===================callbacks=============
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void Application::processInput(GLFWwindow *window)
{


//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
}
