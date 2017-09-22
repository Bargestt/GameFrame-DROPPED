#ifndef GTEXTURE_H
#define GTEXTURE_H

#include  <map>
#include <vector>


#include <ResourceManager/texturebase.h>




class GTexture : public TextureBase
{
protected:
public:
    GTexture(void);
    GTexture(GLuint id);
    ~GTexture();

    void loadFromData(unsigned char *data, int channels);
    bool loadFromFile(const char *path);


    //TODO: neeed extension for ARRAY TEXTURE
    //bool loadArray(const char *path, int width, int height, int layers);

};

#endif // GTEXTURE_H
