#include "terrain.h"


Terrain::Terrain()
{    
    m_Shader.load("res/shader/GameShaders/TerrainShaderColor.vert",
                       "res/shader/GameShaders/TerrainShaderColor.frag");

}

Terrain::~Terrain()
{

}

const TerrainMap &Terrain::getMap() const
{
    return m_Map;
}

void Terrain::update()
{


}

void Terrain::formRenderList()
{    
    glm::ivec3 gridpos;
    gridpos.x = floor(cameraPos.x / world_const::BLOCK_NUMBER);
    gridpos.z = floor(cameraPos.z / world_const::BLOCK_NUMBER);


    // мб сделать обсервера? слежеие за камерой и буферизация в зависимости от дальностии
    //for(TerrainSection* section : renderList)




    for(int z = -renderDist; z < renderDist; z++)
    {
        for(int x = -renderDist; x < renderDist; x++)
        {
            TerrainSection* ptr = &m_Map.getPieceAt( Point(gridpos.x + x, gridpos.z + z ));
            renderList.insert( ptr );
        }
    }
    for( auto it = renderList.begin() ; it != renderList.end(); it++)
    {
        glm::ivec3 pos = (*it)->getData().gridPosition();

        if( abs( pos.x - gridpos.x ) > renderDist + 1 ||
             abs( pos.z - gridpos.z ) > renderDist + 1 )
        {
            (*it)->freeBuffer();
            it = renderList.erase(it);
        }
        else
        {
            int distToPlayer = floor(glm::length( (*it)->getData().center() - cameraPos ) /
                    world_const::BLOCK_NUMBER);
            int desiredLOD = 0;
            if(distToPlayer <= 5) desiredLOD = 0;
            if(distToPlayer > 5 && distToPlayer <= 12) desiredLOD = 1;
            if(distToPlayer > 12 && distToPlayer <= 20) desiredLOD = 2;
             if(distToPlayer > 20)desiredLOD = 3;

            if( (*it)->getLOD_lvl() != desiredLOD) //distToPlayer
                (*it)->genBuffer(desiredLOD);
        }
    }


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
    for(TerrainSection* section : renderList)
    {
        glm::mat4 modelMatrix = glm::translate(base, section->getData().position());
        m_Shader.setModel(modelMatrix);

        glm::mat3 normMat= glm::transpose(glm::inverse(camera.getViewMatrix() *modelMatrix));
        m_Shader.setMatrix("normalMat",3, glm::value_ptr(normMat));

        section->render();
    }

    rendrer.getLightSource().applyToShader(water.m_Shader);
    water.m_Shader.use();

    water.m_Shader.setView(camera.getViewMatrix());
    water.m_Shader.setProjection(camera.getProjectionlMatrix());

    static float dt = 0, lastTime = 0;
    dt = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();

    water.m_Shader.setFloat("time",sin(dt));
    for(TerrainSection* section : renderList)
    {
        glm::mat4 modelMatrix = glm::translate(base, section->getData().position());
        modelMatrix = glm::translate(modelMatrix, {0,1,0});
        modelMatrix = glm::scale(modelMatrix, {world_const::BLOCK_NUMBER,1,world_const::BLOCK_NUMBER});
        water.m_Shader.setModel(modelMatrix);

        water.render(rendrer);
    }
}

