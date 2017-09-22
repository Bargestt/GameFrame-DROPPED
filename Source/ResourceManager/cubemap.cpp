#include "cubemap.h"

CubeMap::CubeMap()
{

}

void CubeMap::bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _ID);
}

bool CubeMap::load(std::vector<std::string> faces)
{
    if(_ID != 0)
        clearData();
    glGenTextures(1,&_ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _ID);

    int nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &_width, &_height, &nrChannels, 0);
        if(nrChannels == 1)
            _format = GL_BLUE;
        else if(nrChannels == 2)
            _format = GL_RG;
        else if(nrChannels ==3)
            _format = GL_RGB;
        else if(nrChannels == 4)
            _format = GL_RGBA;
        else
            _format = GL_RED;
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
            return false;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return true;

}
