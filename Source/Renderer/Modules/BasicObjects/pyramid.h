#ifndef PYRAMID_H
#define PYRAMID_H

#include <Renderer/Modules/basemodel.h>
#include <ResourceManager/resourcemanager.h>

#include <glm.h>

struct Pyramid : public Mesh
{
    Pyramid(){
        verticesPos =
        {
            //bottom
            1,0,1,
            1,0,0,
            0,0,0,
            0,0,1,

            //top
            0.5f, 1, 0.5f
        };
        indices =
        {
            0,1,2,
            0,2,3,

            0,4,3,
            3,4,2,
            2,4,1,
            1,4,0
        };
        setTexCoords( *ResourceManager::get()->m_Atlas, 0,0);

        glm::vec3 p1 = {1,0,1};
        glm::vec3 p2 = {1,0,0};
        glm::vec3 p3 = {0,0,0};
        glm::vec3 p4 = {0,0,1};

        glm::vec3 p = {0.5f, 1, 0.5f};

        glm::vec3 n1 = -glm::normalize(glm::cross( p - p1, p2 - p1) +  glm::cross( p4 - p1, p - p1) + glm::cross( p2 - p1, p4 - p1));
        glm::vec3 n2 = -glm::normalize(glm::cross( p - p2, p3 - p2) + glm::cross( p1 - p2, p - p2) + glm::cross( p3 - p2, p1 - p2));
        glm::vec3 n3 = -glm::normalize(glm::cross( p - p3, p4 - p3) + glm::cross( p2 - p3, p - p3) + glm::cross( p4 - p3, p2 - p3));
        glm::vec3 n4 = -glm::normalize(glm::cross( p - p4, p1 - p4) + glm::cross( p3 - p4,p - p4) + glm::cross( p1 - p4, p3 - p4));

        normals.insert(normals.end(),{n1.x, n1.y, n1.z});
        normals.insert(normals.end(),{n2.x, n2.y, n2.z});
        normals.insert(normals.end(),{n3.x, n3.y, n3.z});
        normals.insert(normals.end(),{n4.x, n4.y, n4.z});
        normals.insert(normals.end(),{0, 1, 0});
    }
    Mesh *clone() const override
    {
        return new Pyramid(*this);
    }
    Pyramid& setTexCoords(const TextureAtlas& atlas, int x, int y) override
    {
        textureCoords = atlas.getTexture(x,y);
        textureCoords.push_back( atlas.getTextureTriangle(x,y).at(2) );
        textureCoords.push_back( atlas.getTextureTriangle(x,y).at(3) );
        return *this;
    }

};

#endif // PYRAMID_H
