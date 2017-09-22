#ifndef TERRAIN_H
#define TERRAIN_H


#include <functional>
#include <set>
#include <unordered_map>
#include <math.h>


#include <World/TerrainV1_Sections/terrainmap.h>
#include <World/TerrainV1_Sections/water.h>
#include <World/worldconstants.h>


#include <Renderer/Modules/lightsource.h>
#include <Renderer/masterrenderer.h>

#include<ResourceManager/resourcemanager.h>

//#include <Util/array_2d.h>


#include <shader.h>
#include <camera.h>
//#include <player.h>


class Terrain
{
    TerrainMap m_Map;

    std::set<TerrainSection*> renderList;


    //TEST
    TerrainSection* test;
    Water water;

    glm::vec3 cameraPos;

    int renderDist = 25;

    Shader m_Shader;

public:
    Terrain();
    ~Terrain();

    const TerrainMap& getMap() const;

    void update();

    void formRenderList();

    Point findSectionContaining(float x, float y) const;


    void render(MasterRenderer &rendrer, const Camera& camera);
};

#endif // TERRAIN_H
