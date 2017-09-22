#ifndef WORLD_H
#define WORLD_H





#include <functional>
#include <unordered_map>


#include <Util/array_2d.h>
#include <World/TerrainV1_Sections/terrain.h>

#include <camera.h>
#include <player.h>





class World
{
    Terrain terrain;

    glm::vec3 playerPos;
public:
    World();

    void update();

    void fixedUpdate();

    void render(MasterRenderer &renderer,  const Camera& camera);

    Terrain &getTerrain();
};

#endif // WORLD_H
