#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include <glheader.h>
#include <shader.h>
#include <Renderer/Modules/basemodel.h>
#include <ResourceManager/resourcemanager.h>
#include <Renderer/Modules/BasicObjects/basicobjects.h>
#include <camera.h>


struct GuiObj
{
    glm::vec2 m_Position;
    glm::vec2 m_Scale;
    GLuint m_Texture;

    GuiObj(glm::vec2 position, glm::vec2 scale, GLuint texture)
        : m_Position(position), m_Scale(scale), m_Texture(texture)
    {  }
};

class GuiRenderer
{
    Shader m_Shader;
    BaseModel m_Model;

    std::vector<GuiObj> GUIs;
    const GTexture* test = nullptr;
    glm::vec3 position;
public:
    GuiRenderer();

    void loadShader(const char *vertexPath, const char *fragmentPath);
    void setCamera(const Camera& camera);
    void drawImage(const GuiObj& GUI);
    void render();
};

#endif // GUIRENDERER_H
