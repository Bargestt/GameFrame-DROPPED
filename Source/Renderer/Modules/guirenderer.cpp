#include "guirenderer.h"

GuiRenderer::GuiRenderer(): position(0,0,0)
{
    m_Model.genVAO();
    m_Model.addVBO(3,
                    {
                       -1,1,0.0,
                       1, 1,0.0,                       
                       -1,-1,0.0,
                       1, -1, 0.0
                   });
}

void GuiRenderer::loadShader(const char *vertexPath, const char *fragmentPath)
{
    m_Shader.load(vertexPath, fragmentPath);
}

void GuiRenderer::setCamera(const Camera &camera)
{
    m_Shader.use();
    m_Shader.setProjection(camera.getProjectionlMatrix());
}

void GuiRenderer::drawImage(const GuiObj &GUI)
{
    GUIs.push_back( GUI );
}

void GuiRenderer::render()
{
    m_Shader.use();

    for( GuiObj& obj : GUIs){
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(obj.m_Position, 0.0) );
        model = glm::scale(model, glm::vec3(obj.m_Scale, 0.0) );
        m_Shader.setModel(model);

        glBindTexture(GL_TEXTURE_2D, obj.m_Texture);

        m_Model.bindVAO();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    GUIs.clear();
}
