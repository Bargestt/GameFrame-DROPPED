#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "gtexture.h"

class CubeMap : public GTexture
{
public:
    CubeMap();

    bool load(std::vector<std::string> faces);

    void bind() const override;
};

#endif // CUBEMAP_H
