#include "terraindata.h"

glm::vec3 TerrainData::s_Colors[] =
{
    { 0.76f, 0.698f, 0.50f },
    { (float)0/255,(float)92/255,(float)9/255 },
    { 0.4716f,	0.5042f, 0.5434f},
    { 0.9f, 0.9f, 0.9f},
    { 0,0,0}
};

TerrainData::TerrainData() : m_Position(0,0,0)
{   
    for(int i =0; i< world_const::CHUNK_SIZE; i++)
        m_ColorMap[i].fill(glm::vec3(0,1,0));
}

TerrainData::TerrainData(const TerrainData::Array2D &heightMap) : TerrainData()
{
    m_HeightMap = heightMap;
    for(int i =0; i< world_const::CHUNK_SIZE; i++)
        m_ColorMap[i].fill(glm::vec3(0,1,0));
}
TerrainData::TerrainData(const TerrainData::Array2D &heightMap, float x, float y)
{
    m_HeightMap = heightMap;
    m_Position.x = x;
    m_Position.z = y;
    for(int i =0; i< world_const::CHUNK_SIZE; i++)
        m_ColorMap[i].fill(glm::vec3(0,1,0));
}

TerrainData::TerrainData(const TerrainData::Array2D &heightMap,
                                            const TerrainData::Array2Dvec3 &colorMap, float x, float y)
{
    m_HeightMap = heightMap;
    m_Position.x = x;
    m_Position.z = y;
    m_ColorMap = colorMap;
}

const TerrainData::Array2D &TerrainData::heightMap() const
{
    return m_HeightMap;
}

const TerrainData::Array2Dvec3 &TerrainData::colorMap() const
{
    return m_ColorMap;
}

void TerrainData::setColorMap(const TerrainData::Array2Dvec3 &colorMap)
{
    m_ColorMap = colorMap;
}

bool TerrainData::contains(const glm::vec2& point) const
{
    using namespace  world_const;
    if(     point.x >= m_Position.x &&
            point.y >= m_Position.z &&
            point.x - m_Position.x  <   CHUNK_SIZE  &&
            point.y - m_Position.z  <   CHUNK_SIZE
       )
        return true;
    return false;
}
glm::vec2 TerrainData::toLocal(const glm::vec2 &globalPos) const
{
    return { globalPos.x - m_Position.x, globalPos.y - m_Position.z };
}
glm::vec3 TerrainData::position() const
{
    return m_Position;
}

glm::vec3 TerrainData::center() const
{
    return
    {
        m_Position.x + world_const::CHUNK_SIZE/2,
        m_Position.y,
        m_Position.z + world_const::CHUNK_SIZE/2
    };
}

glm::ivec3 TerrainData::gridPosition() const
{
    return
    {
        floor(m_Position.x / world_const::CHUNK_SIZE),
        floor(m_Position.y / world_const::CHUNK_SIZE),
        floor(m_Position.z / world_const::CHUNK_SIZE)
    };
}


GLfloat TerrainData::heightAt(glm::vec2 globalPos) const
{
using namespace  world_const;

    if( !contains(globalPos) )
        return 0;

    float localX =  globalPos.x - m_Position.x;
    float localY =  globalPos.y - m_Position.z;

    return heightAt_L( glm::vec2(localX, localY) );
}

GLfloat TerrainData::heightAt_L(glm::vec2 localPos) const
{
    using namespace  world_const;

    if(  !(localPos.x >= 0  &&
            localPos.y >= 0  &&
            localPos.x  <   CHUNK_SIZE  &&
            localPos.y  <   CHUNK_SIZE)
       ) return 0;

    float gridSquareSize =  BLOCK_SIZE;

    int gridX = floor( localPos.x/ gridSquareSize );
    int gridY = floor( localPos.y/ gridSquareSize );

    float xCoord = fmod(localPos.x , gridSquareSize) / gridSquareSize;
    float yCoord = fmod(localPos.y , gridSquareSize) / gridSquareSize;

    float val;
    if(xCoord <= (1 - yCoord))
    {
        val = mathfunc::barryCentric
                (
                    glm::vec3( 0, m_HeightMap[gridX][gridY] ,0 ),
                    glm::vec3( 1, m_HeightMap[ gridX + 1 ][ gridY ] ,0 ),
                    glm::vec3( 0, m_HeightMap[ gridX ][ gridY + 1 ] ,1 ),
                    glm::vec2( xCoord, yCoord )
                );
    }
    else
    {
        val = mathfunc::barryCentric
                (
                    glm::vec3( 1, m_HeightMap[ gridX + 1 ][ gridY + 1 ] ,1 ),
                    glm::vec3( 1, m_HeightMap[ gridX + 1 ][ gridY ] ,0 ),
                    glm::vec3( 0, m_HeightMap[ gridX ][ gridY + 1 ] ,1 ),
                    glm::vec2( xCoord, yCoord )
                );
    }
    return val;
}

GLfloat TerrainData::heightAt(int x_local, int z_local)
{
    if(
            x_local >= 0 &&
            z_local >= 0 &&
            x_local  <   world_const::CHUNK_SIZE  &&
            z_local  <   world_const::CHUNK_SIZE
       )
        return m_HeightMap[x_local][z_local];
    else
        return 0;
}

void TerrainData::setHeightAt(glm::vec3 newHeight_global)
{
    glm::ivec3 newHeight_local = (glm::ivec3)(newHeight_global - m_Position);

    if(newHeight_local.x >= 0 &&
            newHeight_local.y >= 0 &&
            newHeight_local.x < world_const::CHUNK_SIZE &&
            newHeight_local.y < world_const::CHUNK_SIZE  )
        m_HeightMap[newHeight_local.x][newHeight_local.z] = newHeight_local.y;
}

glm::vec3 TerrainData::colorByHeight(float height)
{
    glm::vec3 color;

    if(height < 0.3)
        color = s_Colors[SAND];
    if(height >= 0.3 && height < 0.5)
        color = s_Colors[GRASS];
    if(height >= 0.5 && height < 0.8)
        color = s_Colors[ROCK];
    if(height >= 0.8 && height < 1)
        color = s_Colors[SNOW];
    return color;
}

