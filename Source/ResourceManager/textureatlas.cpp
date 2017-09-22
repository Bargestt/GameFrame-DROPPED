#include "textureatlas.h"


TextureAtlas::TextureAtlas()
{
    setTileSize(16);
}

TextureAtlas::TextureAtlas(const char *path, int tile_Height)
{
    loadFromFile(path);

    setTileSize(tile_Height);
}




std::vector<GLfloat> TextureAtlas::getTexture(int x, int y) const
{
        GLfloat xMin = x*m_TileSize;
        GLfloat yMin =y*m_TileSize;

        GLfloat xMax = (xMin+m_TileSize);
        GLfloat yMax = (yMin+m_TileSize);

        return
        {
                xMin,yMax,
                xMax,yMax,
                xMax,yMin,
                xMin,yMin
        };
}

std::vector<GLfloat> TextureAtlas::getTexture6p(int x, int y) const
{
    GLfloat xMin = x*m_TileSize;
    GLfloat yMin =y*m_TileSize;

    GLfloat xMax = (xMin+m_TileSize);
    GLfloat yMax = (yMin+m_TileSize);

    return
    {
        xMin,yMax,
        xMax,yMax,
        xMax,yMin,

        xMax,yMin,
        xMin,yMin,
        xMin,yMax
    };
}

std::vector<GLfloat> TextureAtlas::getTextureTriangle(int x, int y) const
{
    GLfloat xMin = x*m_TileSize;
    GLfloat yMin =y*m_TileSize;

    GLfloat xMax = (xMin+m_TileSize);
    GLfloat yMax = (yMin+m_TileSize);

    return
    {
        xMin, yMax,
        (xMin+xMax)/2, (yMin + yMax) /2,
        xMax, yMax
    };

}


void TextureAtlas::setTileSize(int tile_Height)
{
    m_TileSize = ( 1.0f / ( (float)this->width() ) * tile_Height );
}

