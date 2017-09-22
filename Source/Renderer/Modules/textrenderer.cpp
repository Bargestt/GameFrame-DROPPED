#include "textrenderer.h"

TextRenderer::TextRenderer()
{    
    m_Shader.load("res/shader/basicShaders/basicFont.vert",
                  "res/shader/basicShaders/basicFont.frag");



    generateBuffers();
}
void TextRenderer::setCamera(const Camera &camera)
{
    m_Shader.use();
    m_Shader.setProjection(camera.getOrthoMatrix());
}

void TextRenderer::loadShader(const char *vertexPath, const char *fragmentPath)
{
    m_Shader.load(vertexPath, fragmentPath);
}

void TextRenderer::add(const TextObject &data)
{
    m_TextsArray.push_back(data);
}

void TextRenderer::render()
{
    m_Shader.use();    

    glActiveTexture(GL_TEXTURE0);
    m_Model.bindVAO();

    for(TextObject& textObj : m_TextsArray )
    {
        m_Shader.setVec("textColor",textObj.m_Color.x, textObj.m_Color.y, textObj.m_Color.z);


        int x = textObj.X;
        std::string::const_iterator c;
        for (c = textObj.m_Text.begin(); c != textObj.m_Text.end(); c++)
        {
            FontTexture::Character ch = m_Font.m_Characters[*c];
            m_Model.changeVBO(0,ch.toVertices(   x,
                                                                               textObj.Y,
                                                                               textObj.m_Scale
                                                                               ) );


            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //advance cursors for next glyph ( advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * textObj.m_Scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
    }
    m_TextsArray.clear();

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}


void TextRenderer::generateBuffers()
{    
    m_Model.genVAO();
    std::vector<GLfloat> vec;
    vec.resize(24);

    m_Model.addVBO(4,vec,GL_DYNAMIC_DRAW);
}
