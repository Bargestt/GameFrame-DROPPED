#include "skyboxrenderer.h"



SkyBoxRenderer::SkyBoxRenderer()
{

}

void SkyBoxRenderer::render(const Camera &camera)
{
    glDepthFunc(GL_LEQUAL);
    m_Shader.use();
    m_Shader.setProjection(camera.getProjectionlMatrix());
    m_Shader.setView( glm::mat4(glm::mat3( camera.getViewMatrix() )) );

    ResourceManager::get()->m_CubeMap.bind();

    m_Model.bindVAO();

    glDrawElements(GL_TRIANGLES, m_Model.getIndecesCount(), GL_UNSIGNED_INT,0);
    glDepthFunc(GL_LESS);
}

void SkyBoxRenderer::loadObject(const Mesh &mesh)
{
    m_Model.genVAO();

    m_Buffers[vericeBuffer] = m_Model.addVBO( 3, mesh.verticesPos );
    m_BufferSize[vericeBuffer] = mesh.verticesPos.size();

    if( mesh.indices.size() > 0 )
        m_Buffers[indicesBuffer] = m_Model.addEBO( mesh.indices );
    m_BufferSize[indicesBuffer] = mesh.indices.size();

    currentMesh = mesh.clone();
}
