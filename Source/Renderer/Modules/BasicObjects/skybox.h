#ifndef SKYBOX_H
#define SKYBOX_H

#include <Renderer/Modules/basemodel.h>
#include <ResourceManager/resourcemanager.h>


class SkyBox : public Mesh
{
public:
    SkyBox()
    {
        verticesPos =
        {
                -1.0f,  1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f,  1.0f,

                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f,


                -1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f, -1.0f,

        };
        indices =
        { //indices
          0,1,2,
          2,3,0,

          4,5,6,
          6,7,4,

          8,9,10,
          10,11,8,

          12,13,14,
          14,15,12,

          16,17,18,
          18,19,16,

          20,21,22,
          22,23,20
        };
    }

    Mesh *clone() const override
    {
        return new SkyBox(*this);
    }

    SkyBox& setTexCoords(const TextureAtlas& atlas, int x, int y) override
    {
        return *this;
    }
};

#endif // SKYBOX_H
