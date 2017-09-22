#include "terrain.h"


Terrain::Terrain()
{    
    m_Shader.load("D:/1Projects/QT/GameFrame/res/shader/GameShaders/TerrainShader.vert",
                       "D:/1Projects/QT/GameFrame/res/shader/GameShaders/TerrainShader.frag");
}

Terrain::~Terrain()
{

}

TerrainMap &Terrain::getMap()
{
    return m_Map;
}

void Terrain::update()
{
    formRenderList();

}

void Terrain::formRenderList()
{    
    glm::ivec3 gridpos;
    gridpos.x = floor(cameraPos.x / world_const::BLOCK_NUMBER);
    gridpos.z = floor(cameraPos.z / world_const::BLOCK_NUMBER);

    int maxListSize = (renderDist+1) * (renderDist+1);

    if(sectionsRender.size() < maxListSize)
    {
        for(int y = -renderDist; y <= renderDist; y++ )
        {
            for(int x = -renderDist; x <= renderDist; x++ )
            {
                sectionsRender.push_back( TerrainRend( &m_Map.getPieceAt( {gridpos.x + x, gridpos.z + y } ) ));
                sectionsRender.back().createBuffer();
            }
        }
    }

    for( auto it =sectionsRender.begin(); it != sectionsRender.end(); it++)
    {
        glm::vec3 pos  = (*it).getData()->center();
        if( glm::length(pos - cameraPos) > renderDist*world_const::BLOCK_NUMBER){
            sectionsRender.erase(it);
        }
    }
}

bool Terrain::tryAddToRender(const TerrainData &data)
{


}

Point Terrain::findSectionContaining(float x, float y) const
{
    return Point( floor(x / world_const::BLOCK_NUMBER),
                                    floor(y / world_const::BLOCK_NUMBER) );
}


void Terrain::render(MasterRenderer &rendrer, const Camera& camera)
{
    cameraPos = camera.position;
    rendrer.getLightSource().applyToShader(m_Shader);
    m_Shader.use();
    m_Shader.setProjectionView(camera.getProjectionlViewMatrix());
    m_Shader.setView(camera.getViewMatrix());

    ResourceManager::get()->m_TerrainTexture.bind();

    glm::mat4 base;
    for(auto& section : sectionsRender)
    {        
        //const TerrainSection& section = terr.second;
        glm::mat4 modelMatrix = glm::translate(base, section.getData()->position());
        m_Shader.setModel(modelMatrix);

        glm::mat3 normMat= glm::transpose(glm::inverse(camera.getViewMatrix() *modelMatrix));
        m_Shader.setMatrix("normalMat",3, glm::value_ptr(normMat));

        section.render();
    }
}

