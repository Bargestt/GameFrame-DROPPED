#include "matrixfunctions.h"

#include <camera.h>
#include <entity.h>
#include <config.h>





glm::mat4 mathfunc::makeModelMatrix(const Entity& entity)
{
    glm::quat orient;

    if(entity.rotation.x != 0)
        orient *= glm::angleAxis(glm::radians(entity.rotation.x),glm::vec3(1.0, 0.0, 0.0) * orient);
    if(entity.rotation.y != 0)
        orient *= glm::angleAxis(glm::radians(entity.rotation.y),glm::vec3(0.0, 1.0, 0.0) * orient);
    if(entity.rotation.z != 0)
        orient *= glm::angleAxis(glm::radians(entity.rotation.z),glm::vec3(0.0, 0.0, 1.0) * orient);

    return glm::translate(glm::mat4_cast(orient), entity.position);
}
glm::mat4 mathfunc::makeModelMatrix2(const Entity& entity)
{
    static glm::quat orient;
    static glm::vec3 prev_rot;

    if(entity.rotation != prev_rot){
        glm::quat m;
        orient = m;
        if(entity.rotation.x != 0)
            orient *= glm::angleAxis(glm::radians(entity.rotation.x),glm::vec3(1.0, 0.0, 0.0) * orient);
        if(entity.rotation.y != 0)
            orient *= glm::angleAxis(glm::radians(entity.rotation.y),glm::vec3(0.0, 1.0, 0.0) * orient);
        if(entity.rotation.z != 0)
            orient *= glm::angleAxis(glm::radians(entity.rotation.z),glm::vec3(0.0, 0.0, 1.0) * orient);
    }
    prev_rot = entity.rotation;
    return glm::translate(glm::mat4_cast(orient), entity.position);

}

glm::mat4 mathfunc::makeModelMatrix3(const Entity& entity)
{
    static glm::quat orient;
    static glm::vec3 prev_rot;

    if(entity.rotation != prev_rot){
        glm::quat m;
        orient = m;
        if(entity.rotation.x != 0)
            orient *= glm::angleAxis(glm::radians(entity.rotation.x),glm::vec3(1.0, 0.0, 0.0) * orient);
        if(entity.rotation.y != 0)
            orient *= glm::angleAxis(glm::radians(entity.rotation.y),glm::vec3(0.0, 1.0, 0.0) * orient);
        if(entity.rotation.z != 0)
            orient *= glm::angleAxis(glm::radians(entity.rotation.z),glm::vec3(0.0, 0.0, 1.0) * orient);
    }
    prev_rot = entity.rotation;

    if(entity.scale.x == 1.0f && entity.scale.y == 1.0f && entity.scale.z == 1.0f )
        return glm::translate(glm::mat4_cast(orient), entity.position);
    else
    {
            glm::mat4 scale;
            scale = glm::scale(scale, entity.scale);
            return glm::translate(glm::mat4_cast(orient), entity.position) * scale;
    }

}

glm::mat4 mathfunc::makeModelMatrix_Translation(const Entity& entity)
{
    glm::mat4 matrix;

    matrix = glm::translate(matrix,entity.position);

    return matrix;
}

glm::mat4 mathfunc::makeViewMatrix(const Camera& camera)
{
    glm::mat4 matrix;

    matrix = glm::rotate(matrix,glm::radians(camera.rotation.x), {1,0,0});
    matrix = glm::rotate(matrix,glm::radians(camera.rotation.y), {0,1,0});
    matrix = glm::rotate(matrix,glm::radians(camera.rotation.z), {0,0,1});

    matrix = glm::translate(matrix, -camera.position);

    return matrix;
}

glm::mat4 mathfunc::makeProjectionMatrix(const Config &config)
{
    float x = config.window_Width;
    float y = config.window_Height;
    float fov = config.fov;

    return glm::perspective(glm::radians(fov), x / y, 0.1f, 2000.0f);
}


