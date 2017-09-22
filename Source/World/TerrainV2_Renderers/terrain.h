#ifndef TERRAIN_H
#define TERRAIN_H


#include <functional>
#include <unordered_map>
#include <math.h>

#include <World/worldconstants.h>
#include <World/terrainsection.h>
#include <World/terrainmap.h>

#include <MathFunctions/hash.h>
#include <MathFunctions/perlin.hpp>
#include <Util/array_2d.h>
#include <Renderer/Modules/lightsource.h>
#include <Renderer/masterrenderer.h>
#include<ResourceManager/resourcemanager.h>
#include <World/terrainrend.h>

#include <Util/Collisions/collisionpacket.h>

#include <shader.h>
#include <camera.h>
//#include <player.h>




 // TODO: СДЕЛАЙ КАК БЫЛО! ЗАЕБАЛ!
class Terrain
{
    TerrainMap m_Map;

    std::vector<TerrainRend> sectionsRender;

    glm::vec3 cameraPos;

    int renderDist = 2;

    Shader m_Shader;

public:
    Terrain();
    ~Terrain();

    TerrainMap& getMap();

    void update();

    void formRenderList();
    bool tryAddToRender(const TerrainData& data);


    Point findSectionContaining(float x, float y) const;


    void render(MasterRenderer &rendrer, const Camera& camera);
};

#endif // TERRAIN_H
