#ifndef CONTEXT_H
#define CONTEXT_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "config.h"

struct Context
{
    GLFWwindow* window;

    Context(Config& config);


};

#endif // CONTEXT_H
