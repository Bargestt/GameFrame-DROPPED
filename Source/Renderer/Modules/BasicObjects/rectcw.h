#ifndef RECTCW_H
#define RECTCW_H

#include <Renderer/Modules/basemodel.h>
#include <ResourceManager/resourcemanager.h>
#include <glm.h>
struct RectCW : public Mesh
{
    RectCW(){
        verticesPos =
        {
            1,1,0,
            1,0,0,
            0,0,0,
            0,1,0
        };
        indices =
        {
            0,1,2,
            0,2,3
        };
        textureCoords =
        {
            ResourceManager::get()->m_Atlas->getTexture(1,0)
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
        return new RectCW(*this);
    }
    RectCW& setTexCoords(const TextureAtlas& atlas, int x, int y) override
    {
        textureCoords = atlas.getTexture(x,y);
        return *this;
    }
    RectCW& calculateNormals()
    {
        return *this;
    }
};

#endif // RECTCW_H
