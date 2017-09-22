#include "terrainrenderer.h"

TerrainRenderer::TerrainRenderer()
{
    for(int y = - renderDist; y < renderDist; y++)
    {
        for(int x = - renderDist; x < renderDist; x++)
        {
            poses.push_back({cameraPos.x + x, cameraPos.z + y});
        }
    }

}

void TerrainRenderer::loadShader(const char *vertexPath, const char *fragmentPath)
{
    m_Shader.load(vertexPath, fragmentPath);
}

void TerrainRenderer::loadObject(const Mesh &mesh)
{

}

void TerrainRenderer::anchorPos(const Point &anchorPos)
{


}

void TerrainRenderer::add(const Point &pos)
{
    if(m_pTerrain != nullptr)
    {
        auto it = sections.find(pos);
        if(it == sections.end())
        {
            //sections[pos] = TerrainSection(m_pTerrain->getPieceAt(pos));
        }
    }

}

void TerrainRenderer::remove(const Point &pos)
{
    sections.erase(pos);
}

void TerrainRenderer::update()
{



}

void TerrainRenderer::setTerrain(Terrain &terrain)
{
    m_pTerrain = &terrain;
}

void TerrainRenderer::setLightSource(const LightSource &light)
{
    lightSource = &light;
}

void TerrainRenderer::render(const Camera& camera)
{
    cameraPos = camera.position;
    update();

    m_Shader.use();

    m_Shader.setProjectionView(camera.getProjectionlViewMatrix());
    m_Shader.setView(camera.getViewMatrix());

    ResourceManager::get()->m_TerrainTexture.bind();

    glm::mat4 base;
    for(const auto& terr : sections)
    {
        const TerrainSection& section = terr.second;

        //glm::mat4 modelMatrix = glm::translate(base, section.getData()->position());
        //m_Shader.setModel(modelMatrix);

        if(lightSource != nullptr)
        {
            lightSource->applyToShader(m_Shader);
            //glm::mat3 normMat= glm::transpose(glm::inverse(camera.getViewMatrix() *modelMatrix));
            //m_Shader.setMatrix("normalMat",3, glm::value_ptr(normMat));
        }
        //section.render();
    }
}
