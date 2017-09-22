#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <ResourceManager/textureatlas.h>
#include <ResourceManager/cubemap.h>


class ResourceManager
{
public:
    static ResourceManager* get();

    TextureAtlas* m_Atlas;

    GTexture m_TerrainTexture;
    CubeMap m_CubeMap;

private:
    ResourceManager();
    static ResourceManager* s_instance;
};

#endif // RESOURCEMANAGER_H
