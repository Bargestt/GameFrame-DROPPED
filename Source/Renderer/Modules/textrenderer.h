#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <ResourceManager/fonttexture.h>
#include <Renderer/Modules/basemodel.h>
#include <camera.h>

#include <shader.h>

class TextRenderer
{
public:    
    TextRenderer();

    void setCamera(const Camera& camera);
    void loadShader(const char *vertexPath, const char *fragmentPath);
    void add(const TextObject& data);
    void render();

protected:
    FontTexture m_Font;
    Shader m_Shader;
    BaseModel m_Model;

    std::vector<TextObject> m_TextsArray;
private:
    void generateBuffers();



};

#endif // TEXTRENDERER_H
