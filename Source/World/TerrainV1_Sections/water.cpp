#include "water.h"

Water::Water()
{
    using namespace world_const;
    m_Shader.load("res/shader/GameShaders/WaterShader.vert",
                       "res/shader/GameShaders/WaterShader.frag");

    m_Model.genVAO();

    std::vector<GLfloat> vertices = {
        0,0,0,
        0,0, 1,
        1,0,0,
        1,0, 1
    };

    m_Model.addVBO(3, vertices);
    m_Model.addEBO({0,1,3, 0,3,2});
}

void Water::render(MasterRenderer& renderer)
{
    glBindTexture(GL_TEXTURE_2D, renderer.frameBuffer.m_Texture);
    m_Model.bindVAO();
    glDrawElements(GL_TRIANGLES, m_Model.getIndecesCount(),GL_UNSIGNED_INT,0);
}
