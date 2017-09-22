#include "world.h"




World::World()
{


}


void World::update()
{
    terrain.update();
}

void World::fixedUpdate()
{
    terrain.formRenderList();
}



void World::render(MasterRenderer &renderer, const Camera& camera)
{

    terrain.render(renderer, camera);




//                std::clock_t c_start  = std::clock();
//            std::clock_t c_end = std::clock();
//            std::cout<< 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms"<<std::endl;

}

Terrain &World::getTerrain()
{
    return terrain;
}
