#ifndef FONTTEXTURE_H
#define FONTTEXTURE_H

#include <ResourceManager/texturebase.h>

#include <glm.h>
#include <map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H



class FontTexture
{
public:
    FontTexture();

    bool loadFont(const char* path, int size = 60, int charCount = 128);

    struct Character
    {
        GLuint TextureID;   // ID handle of the glyph texture
        glm::ivec2 Size;    // Size of glyph
        glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
        GLuint Advance;    // Horizontal offset to advance to next glyph

        std::vector<GLfloat> toVertices(int x, int y, float downScale = 1.0f);
     };

    std::map<GLchar, Character> m_Characters;
protected:
        int m_Size;
        void loadChar(const FT_Face& face, GLubyte chr);
};

#endif // FONTTEXTURE_H
