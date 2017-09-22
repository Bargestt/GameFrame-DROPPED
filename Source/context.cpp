#include "context.h"

Context::Context(Config &config)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    if(config.isFullscreen)
    {
        window = glfwCreateWindow(config.window_Width, config.window_Height, "1GameFrame", glfwGetPrimaryMonitor(), NULL);
    }
    else
    {
        window = glfwCreateWindow(config.window_Width, config.window_Height, "1GameFrame", NULL, NULL);
    }


    if (window == NULL)
    {
       std::cout << "Failed to create GLFW window" << std::endl;
       glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
       std::cout << "Failed to initialize GLAD" << std::endl;
     }

    //================= glEnable==========================
    glEnable(GL_DEPTH_TEST);

    //glCullFace(GL_BACK); //GL_FRONT    GL_FRONT_AND_BACK
//    glFrontFace(GL_CW);  //or GL_CCW
//    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(config.showCursor){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }   else   {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }


    glfwSwapInterval(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //==================== CALLBACKS====================

    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
}


