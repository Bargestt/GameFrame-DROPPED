#ifndef DEBUGELEMENTS_H
#define DEBUGELEMENTS_H

#include <Renderer/Modules/basemodel.h>
#include <shader.h>

#include <ResourceManager/resourcemanager.h>

#include <glm/glm.hpp>

#include <camera.h>

struct Arrow
{
    glm::vec3 position;
    glm::vec3 rotation;
    float baseWidth;
    glm::vec3 color;

    Arrow( glm::vec3 pos, glm::vec3 rot, float newWidth,  glm::vec3 newColor) :
        position(pos), rotation(rot), baseWidth(newWidth), color(newColor)
    {   }
};

class DebugElements
{
    std::vector<Arrow> arrows;

    Shader shader;
    BaseModel model;

    int vbo;
public:
    DebugElements();

    void loadShader(const char *vertexPath, const char *fragmentPath);

    void addArrow(const Arrow &arrow);

    void render( const Camera& camera);
};

#endif // DEBUGELEMENTS_H
