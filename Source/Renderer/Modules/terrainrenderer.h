#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include <Renderer/Modules/basemodel.h>

#include <ResourceManager/resourcemanager.h>
#include <World/TerrainV1_Sections/terraindata.h>
#include <World/TerrainV1_Sections/terrain.h>
#include <World/TerrainV1_Sections/terrainsection.h>

#include <glm.h>

#include <camera.h>
#include <shader.h>
#include <entity.h>



class TerrainRenderer
{
    std::unordered_map<Point,TerrainSection> sections;

    std::vector<TerrainSection> renderers;
    std::vector<Point> poses;
    //std::array<std::array<TerrainSection, renderDist*2>, renderDist*2> m_Sect;
    //center == renderDist, max < renderDist*2

    //test : 1n + 2 lod
    float renderDist = 2;
    float LODdist;

    Shader m_Shader;
    const LightSource *lightSource = nullptr;
    Terrain* m_pTerrain = nullptr;
    glm::vec3 cameraPos = {0,0,0};
public:
    TerrainRenderer();
    void loadShader(const char *vertexPath, const char *fragmentPath);
    void loadObject(const Mesh &mesh);

    void anchorPos(const Point &anchorPos);
    void add(const Point &pos);
    void remove(const Point &pos);
    void update();

    void setTerrain(Terrain &terrain);
    void setLightSource(const LightSource& light);
    void render(const Camera &camera);
private:


};

#endif // TERRAINRENDERER_H
