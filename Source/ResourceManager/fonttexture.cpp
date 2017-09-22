#include "fonttexture.h"

FontTexture::FontTexture() : m_Size( 60 )
{
    loadFont("C:/Windows/Fonts/arial.ttf");
}

bool FontTexture::loadFont(const char *path, int size, int charCount)
{    
    m_Size = size;

    FT_Library ft;
    FT_Face face;

    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    if (FT_New_Face(ft, path, 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;


    // Set size of glyphs
    FT_Set_Pixel_Sizes(face, 0, m_Size);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


    for (GLubyte c = 0; c < charCount; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph:" << c << std::endl;
            continue;
            return false;
        }

        loadChar( face, c );
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    return true;
}

void FontTexture::loadChar(const FT_Face &face, GLubyte chr)
{
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Now store character for later use
    Character character =
    {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (GLuint)face->glyph->advance.x
    };
    m_Characters.insert(std::pair<GLchar, Character>(chr, character));
}





//================ CHARACTER =========================
std::vector<GLfloat> FontTexture::Character::toVertices(int x, int y, float downScale)
{
        GLfloat xpos = x + Bearing.x * downScale;
        GLfloat ypos = y - (Size.y - Bearing.y) * downScale;

        GLfloat w = Size.x * downScale;
        GLfloat h = Size.y * downScale;

        return{
                xpos,     ypos,       0.0, 1.0 ,
              xpos,     ypos + h,   0.0, 0.0 ,              
              xpos + w, ypos,       1.0, 1.0 ,

                        xpos + w, ypos,       1.0, 1.0 ,
              xpos,     ypos + h,   0.0, 0.0 ,              
              xpos + w, ypos + h,   1.0, 0.0
        };
}
