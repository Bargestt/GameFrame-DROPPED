#ifndef CUBE_H
#define CUBE_H

#include <Renderer/Modules/basemodel.h>
#include <ResourceManager/resourcemanager.h>

struct Cube : public Mesh
{
    Cube(){
        verticesPos =
        { //vertices
          //back
          0,0,0,
          1,0,0,
          1,1,0,
          0,1,0,
          //front
          1,1,1,
          1,0,1,
          0,0,1,
          0,1,1,
          //riht
          1,0,0,
          1,0,1,
          1,1,1,
          1,1,0,
          //left
          0,1,1,
          0,0,1,
          0,0,0,
          0,1,0,
          //top
          0,1,1,
          0,1,0,
          1,1,0,
          1,1,1,
          //btm
          1,0,1,
          1,0,0,
          0,0,0,
          0,0,1
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
        setTexCoords( *ResourceManager::get()->m_Atlas, 0,0);
        normals =
        {
            //back
            0,0, -1,
            0,0, -1,
            0,0, -1,
            0,0, -1,
            //front
            0,0,1,
            0,0,1,
            0,0,1,
            0,0,1,
            //riht
            1,0,0,
            1,0,0,
            1,0,0,
            1,0,0,
            //left
            -1,0,0,
            -1,0,0,
            -1,0,0,
            -1,0,0,
            //top
            0,1,0,
            0,1,0,
            0,1,0,
            0,1,0,
            //btm
            0,-1,0,
            0,-1,0,
            0,-1,0,
            0,-1,0
        };


    }

    Mesh *clone() const override
    {
        return new Cube(*this);
    }

    Cube& setTexCoords(const TextureAtlas& atlas, int x, int y) override
    {
        auto side = atlas.getTexture(x,y);

        std::vector<GLfloat> texCoord;
        textureCoords.clear();
        for(int i =0; i < 6; i++)
            texCoord.insert(texCoord.end(),side.begin(),side.end());

        textureCoords = texCoord;
        return *this;
    }

};

#endif // CUBE_H
