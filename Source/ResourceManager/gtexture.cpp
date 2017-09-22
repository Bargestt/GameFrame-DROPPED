#define STB_IMAGE_IMPLEMENTATION
#include "gtexture.h"



GTexture::GTexture(void)
{

}

GTexture::GTexture(GLuint id)
{
    _ID = id;
}

GTexture::~GTexture()
{
    glDeleteTextures(1,&_ID);
}


void GTexture::loadFromData(unsigned char *data, int channels = 3)
{
    if(_ID != 0)
        clearData();
    glGenTextures(1,&_ID);


    glBindTexture(GL_TEXTURE_2D, _ID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);

    if(channels == 1)
        _format = GL_BLUE;
    else if(channels == 2)
        _format = GL_RG;
    else if(channels ==3)
        _format = GL_RGB;
    else if(channels == 4)
        _format = GL_RGBA;
    else
        _format = GL_RED;

    glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

}

bool GTexture::loadFromFile(const char* path)
{
    if(_ID != 0)
        clearData();

    int nrChannels;
    unsigned char *data = stbi_load(path, &_width, &_height, &nrChannels, 0);
    if (data)
    {
        std::cout<<"loading texture: "<<path<<std::endl;
        loadFromData(data,nrChannels);
    }
    else
    {
        std::cout << "Failed to load texture: "<< path<<std::endl;
        return false;
    }

    stbi_image_free(data);

    return true;
}











