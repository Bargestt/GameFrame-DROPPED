#include "terrainrend.h"

TerrainRend::TerrainRend()
{

}

TerrainRend::TerrainRend(const TerrainData *data)
{
    m_Data = data;
}



void TerrainRend::setData(const TerrainData* data)
{
    if( m_Data != data)
    {
        m_Data = data;
        //TODO: refresh
    }
}

const TerrainData *TerrainRend::getData() const
{
     return m_Data;
}

bool TerrainRend::validateBufferToData(const Mesh& mesh) const
{
    return
            ( mesh.verticesPos.size() == bufferSizes[Vertices] ) &&
            ( mesh.textureCoords.size() == bufferSizes[Texture] ) &&
            ( mesh.normals.size() == bufferSizes[Normals] ) &&
            ( mesh.indices.size() == bufferSizes[Indices] );
}

void TerrainRend::createBuffer()
{
    if(m_Data != nullptr){
        Mesh mesh = makeMesh(*m_Data);

        m_Model.genVAO();

        buffers[Vertices] = m_Model.addVBO(3,mesh.verticesPos, GL_DYNAMIC_DRAW);
        bufferSizes[Vertices] = mesh.verticesPos.size();

        buffers[Texture] = m_Model.addVBO(2,mesh.textureCoords, GL_DYNAMIC_DRAW);
        bufferSizes[Texture] = mesh.textureCoords.size();

        buffers[Normals] = m_Model.addVBO(3,mesh.normals, GL_DYNAMIC_DRAW);
        bufferSizes[Normals] = mesh.normals.size();

        buffers[Indices] = m_Model.addEBO(mesh.indices, GL_DYNAMIC_DRAW);
        bufferSizes[Indices] = mesh.indices.size();

        buffered = true;        
    }
}

void TerrainRend::loadData()
{
    if(m_Data != nullptr)
    {
        Mesh mesh = makeMesh(*m_Data);
        m_Model.changeVBO(buffers[Vertices], mesh.verticesPos);
        m_Model.changeVBO(buffers[Texture], mesh.textureCoords);
        m_Model.changeVBO(buffers[Normals], mesh.normals);
        m_Model.changeEBO(buffers[Indices], mesh.indices);
        free = false;
    }
}

void TerrainRend::update()
{
    if(visible == false)
        return;

}

void TerrainRend::render()
{
    if( visible == true && buffered == true ){
        m_Model.bindVAO();
        glDrawElements(GL_TRIANGLES, m_Model.getIndecesCount(),GL_UNSIGNED_INT,0);
    }
}

bool TerrainRend::isVisible() const
{
    return visible;
}

void TerrainRend::setVisibility(bool state)
{
    visible = state;
}

bool TerrainRend::isFree() const
{
    return free;
}
void TerrainRend::setFree(bool state)
{
    free = state;
}

bool TerrainRend::isBuffered() const
{
    return buffered;
}

Mesh TerrainRend::makeMesh(const TerrainData &data)
{
    using namespace world_const;

    Mesh mesh;
    std::vector<glm::vec3> vertices;

    auto& heightMap = data.heightMap();
    for(int y = 0; y < CHUNK_SIZE; y++)
    {
        for(int x = 0; x < CHUNK_SIZE; x++)
        {
            vertices.push_back( {
                                    x * BLOCK_SIZE,
                                    heightMap[ x ][ y ] ,
                                    y * BLOCK_SIZE
                                } );
            mesh.textureCoords.push_back(x);
            mesh.textureCoords.push_back(y);
        }
    }

    for(int x = 0, xIndex = 0; x < CHUNK_SIZE-1; x++)
    {
        for(int y = 0, yIndex = 0; y < CHUNK_SIZE-1; y++)
        {
            mesh.indices.push_back(0 + xIndex + yIndex);
            mesh.indices.push_back(1 + xIndex + yIndex);
            mesh.indices.push_back(CHUNK_SIZE + xIndex + yIndex);

            mesh.indices.push_back(1 + xIndex + yIndex);
            mesh.indices.push_back(CHUNK_SIZE+1 + xIndex + yIndex);
            mesh.indices.push_back(CHUNK_SIZE + xIndex + yIndex);

            yIndex += CHUNK_SIZE;
        }
        xIndex++;
    }

    for(unsigned i=0; i < vertices.size(); i++)
    {
        glm::vec3 current = vertices.at(i);

        glm::vec3 left = { 0, 0, 0};
        glm::vec3 right = { 0, 0, 0};

        glm::vec3 top = { 0, 0, 0};
        glm::vec3 bottom = { 0, 0, 0};

        //check for border cases, so that you wont get vertices from another side of surface
        if(i >=1 &&  i % CHUNK_SIZE != 0)
            left = vertices.at( i - 1  ) - current;

        if( i < CHUNK_AREA - 1  && (i +1 ) % CHUNK_SIZE != 0)
            right = vertices.at( i + 1 ) - current;

        if( i >= CHUNK_SIZE )
            top = vertices.at( i - CHUNK_SIZE ) - current;

        if( i < CHUNK_AREA - CHUNK_SIZE  )
            bottom = vertices.at( i + CHUNK_SIZE ) - current;


        glm::vec3 crossProduct;

        crossProduct = glm::cross( top, left) + glm::cross( right, top ) + glm::cross( left, bottom ) + glm::cross( bottom, right );
        crossProduct = glm::normalize(crossProduct);

        mesh.normals.push_back(crossProduct.x);
        mesh.normals.push_back(crossProduct.y);
        mesh.normals.push_back(crossProduct.z);
    }

    for(glm::vec3 vertice : vertices)
    {
        mesh.verticesPos.push_back(vertice.x);
        mesh.verticesPos.push_back(vertice.y);
        mesh.verticesPos.push_back(vertice.z);
    }

    return mesh;
}

bool TerrainRend::operator ==(const TerrainData &other)
{
    return m_Data == &other;
}

bool TerrainRend::operator ==(const TerrainRend &other)
{
    return m_Data == other.m_Data;
}
