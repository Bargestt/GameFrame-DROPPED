#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <ResourceManager/gtexture.h>

#include <vector>

class TextureAtlas : public GTexture
{
     GLfloat m_TileSize;

public:    
     TextureAtlas();
    TextureAtlas(const char* path, int tile_Height = 16);


    std::vector<GLfloat> getTexture(int x, int y) const;
    std::vector<GLfloat> getTexture6p(int x, int y) const;
    std::vector<GLfloat> getTextureTriangle(int x, int y) const;



    void setTileSize(int tile_Height);


};



#endif // TEXTUREATLAS_H
