#include "dynamicobject.h"

DynamicObject::DynamicObject()
{
    m_pAtlas = ResourceManager::get()->m_Atlas;
}

DynamicObject::DynamicObject(const Mesh &mesh)
{
    currentMesh = mesh.clone();
    loadObject(*currentMesh);
}

DynamicObject::~DynamicObject()
{
    clearMesh();
}
void DynamicObject::clearMesh()
{
    delete currentMesh;
}

void DynamicObject::changeObject(const Mesh &mesh)
{
    if(     m_BufferSize[vericeBuffer] <= mesh.verticesPos.size() &&
            m_BufferSize[textureBuffer] <= mesh.textureCoords.size() &&
            m_BufferSize[indicesBuffer] <= mesh.indices.size() &&
            m_BufferSize[normalsBuffer] <= mesh.normals.size())
    {
        m_Model.changeVBO(m_Buffers[vericeBuffer],mesh.verticesPos);
        m_Model.changeVBO(m_Buffers[textureBuffer],mesh.textureCoords);
        m_Model.changeVBO(m_Buffers[normalsBuffer],mesh.normals);

        m_Model.changeEBO(m_Buffers[indicesBuffer],mesh.indices);
    }
}

void DynamicObject::loadShader(const char *vertexPath, const char *fragmentPath)
{
    m_Shader.load(vertexPath, fragmentPath);
}

void DynamicObject::loadObject(const Mesh &mesh)
{
    m_Model.genVAO();

    m_Buffers[vericeBuffer] = m_Model.addVBO( 3, mesh.verticesPos );
    m_BufferSize[vericeBuffer] = mesh.verticesPos.size();

    if( mesh.textureCoords.size() > 0 )
        m_Buffers[textureBuffer] = m_Model.addVBO( 2, mesh.textureCoords,GL_DYNAMIC_DRAW );
    m_BufferSize[textureBuffer] = mesh.textureCoords.size();

    if( mesh.indices.size() > 0 )
        m_Buffers[indicesBuffer] = m_Model.addEBO( mesh.indices );
    m_BufferSize[indicesBuffer] = mesh.indices.size();

    if( mesh.normals.size() > 0 )
        m_Buffers[normalsBuffer] = m_Model.addVBO( 3, mesh.normals );
    m_BufferSize[normalsBuffer] = mesh.normals.size();

    currentMesh = mesh.clone();
}

void DynamicObject::setTextureCoords(const std::vector<GLfloat> &texCoords)
{
    m_Model.changeVBO( m_Buffers[textureBuffer], texCoords );
}

void DynamicObject::setTextureTile(int x, int y)
{
    if(m_pAtlas != nullptr && currentMesh != nullptr)
        setTextureCoords(currentMesh->setTexCoords( *m_pAtlas, x, y).textureCoords);
}

void DynamicObject::setLightSource(const LightSource &light)
{
    lightSource = &light;
}

void DynamicObject::add(const Entity &entity)
{
        m_Objects.push_back(entity);
}

void DynamicObject::render(const Camera &camera)
{
    if(!m_Objects.empty())
    {
        if(lightSource != nullptr){
            lightSource->applyToShader(m_Shader);
        }

        m_Shader.use();
        m_Shader.setProjection(camera.getProjectionlMatrix());
        m_Shader.setView(camera.getViewMatrix());

        m_pAtlas->bind();

        int lastx = 0, lasty = 0;
        for(Entity &obj : m_Objects)
        {
            glm::mat4 modelMatrix = mathfunc::makeModelMatrix3(obj);
            m_Shader.setModel(modelMatrix);

            if(lightSource != nullptr)
            {
                glm::mat3 normMat= glm::transpose(glm::inverse(camera.getViewMatrix() *modelMatrix));
                m_Shader.setMatrix("normalMat",3, glm::value_ptr(normMat));
            }

            m_Model.bindVAO();

            if( lastx != obj.texTile.x || lasty != obj.texTile.y)
                setTextureTile( obj.texTile.x, obj.texTile.y);
            else{
                lastx = obj.texTile.x;
                lasty = obj.texTile.y;
            }

            glDrawElements(GL_TRIANGLES, m_Model.getIndecesCount(), GL_UNSIGNED_INT,0);
        }
        m_Objects.clear();
    }
}



