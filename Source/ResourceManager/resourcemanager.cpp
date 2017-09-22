#include "resourcemanager.h"

ResourceManager* ResourceManager::s_instance = nullptr;

ResourceManager::ResourceManager()
{    
    m_Atlas = new TextureAtlas();
    m_Atlas->setFormat(GL_REPEAT,GL_REPEAT, GL_NEAREST, GL_NEAREST);
    m_Atlas->loadFromFile("res/img/atlas.png");
    m_Atlas->setTileSize(128);


    m_TerrainTexture.setFormat(GL_REPEAT, GL_REPEAT,GL_NEAREST,GL_NEAREST);
    m_TerrainTexture.loadFromFile("res/img/dirt.png");

    std::vector<std::string> faces
        {
            "res/img/skybox/right.jpg",
            "res/img/skybox/left.jpg",
            "res/img/skybox/top.jpg",
            "res/img/skybox/bottom.jpg",
            "res/img/skybox/back.jpg",
            "res/img/skybox/front.jpg"
        };
    m_CubeMap.load(faces);
}

ResourceManager *ResourceManager::get()
{
    if(s_instance == nullptr)
        s_instance = new ResourceManager();

    return s_instance;
}
