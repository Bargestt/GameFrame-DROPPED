#ifndef RECTTOPLEFT_H
#define RECTTOPLEFT_H

#include <Renderer/Modules/basemodel.h>
#include <ResourceManager/resourcemanager.h>
#include <glm.h>

struct RectTopLeft : public Mesh
{
    RectTopLeft(){
        verticesPos =
        {
            0,0,0,
            1.0f,0,0,
            1.0f,-1.0f,0,
            0,-1.0f,0
        };
        indices =
        {
            0,1,2,
            0,2,3
        };
        textureCoords =
        {
            0,1,
            1,1,
            1,0,
            0,0
        };
        normals = {
            0,0,-1.0f,
            0,0,-1.0f,
            0,0,-1.0f,
            0,0,-1.0f,
        };

    }
    Mesh *clone() const override
    {
        return new RectTopLeft(*this);
    }
    RectTopLeft& setTexCoords(const TextureAtlas& atlas, int x, int y) override
    {
        textureCoords = atlas.getTexture(x,y);
        return *this;
    }
    RectTopLeft& calculateNormals()
    {
        return *this;
    }    
};

#endif // RECTCW_H
