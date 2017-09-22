#include "terrainsection.h"


TerrainSection::TerrainSection()
{

}
TerrainSection::TerrainSection(const Array2D& data) : m_TerrainData(data)
{    

}
TerrainSection::TerrainSection(const Array2D &data, float x, float y): m_TerrainData(data, x, y)
{

}

TerrainSection::TerrainSection(const TerrainSection::Array2D &data,
                               const TerrainSection::Array2Dvec3 &colorMap, float x, float y) :
    m_TerrainData(data,colorMap, x, y)
{

}

const TerrainData &TerrainSection::getData() const
{
    return m_TerrainData;
}
bool TerrainSection::isVisible() const
{
    return visible;
}

void TerrainSection::hide()
{
    visible = false;
}

void TerrainSection::show()
{
    visible = true;
}

void TerrainSection::freeBuffer()
{
    m_Model.deleteData();
    buffered = false;
}

void TerrainSection::genBuffer(unsigned LOD_level)
{    
    if(LOD_level > 4)
        LOD = 4;
    else
        LOD = LOD_level;
    generate();
}

int TerrainSection::getLOD_lvl()
{
    return LOD;
}

bool TerrainSection::isBuffered() const
{
    return buffered;
}

const TerrainData &TerrainSection::getData()
{
    return m_TerrainData;
}
void TerrainSection::render() const
{
    m_Model.bindVAO();
    glDrawElements(GL_TRIANGLES, m_Model.getIndecesCount(),GL_UNSIGNED_INT,0);
}

void TerrainSection::generate()
{
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> normales;

     generateVertices(vertices, indices,texCoords);
     generateNormals(vertices, normales);


    std::vector<GLfloat> verticesArr;
    for(glm::vec3 vertice : vertices)
    {
        verticesArr.push_back(vertice.x);
        verticesArr.push_back(vertice.y);
        verticesArr.push_back(vertice.z);
    }

    m_Model.genVAO();
    m_Model.addVBO(3,verticesArr);
    if(colorMap)
    {
        if(texCoords.size() >0)
            m_Model.addVBO(3,texCoords);
    }
    else
    {
        if(texCoords.size() >0)
            m_Model.addVBO(2,texCoords);
    }
    if(indices.size() >0)
        m_Model.addEBO(indices);
    if( normales.size() > 0 )
        m_Model.addVBO( 3, normales );

    buffered = true;
}


void TerrainSection::generateVertices(
        std::vector<glm::vec3> &vertices,
        std::vector<GLuint> &indices,
        std::vector<GLfloat> &textureCoordinates
        )
{
    using namespace world_const;

    auto& heightmap = m_TerrainData.heightMap();

    unsigned LOD_inc = pow(2, LOD);
    if(LOD_inc > world_const::BLOCK_NUMBER) LOD_inc = world_const::BLOCK_NUMBER;
    int increment = (LOD_inc == 0)? 1 : LOD_inc;

    if( colorMap)
    {
        auto& colorMap = m_TerrainData.colorMap();
        for(int y = 0; y < CHUNK_SIZE; y+= increment)
        {
            for(int x = 0; x < CHUNK_SIZE; x+= increment)
            {
                vertices.push_back( {
                                        x * BLOCK_SIZE,
                                        heightmap[ x ][ y ] ,
                                        y * BLOCK_SIZE
                                    } );
                glm::vec3 color = colorMap[x][y];
                //glm::vec3 color = TerrainData::colorByHeight(heightmap[x][y]);
                textureCoordinates.push_back(color.x);
                textureCoordinates.push_back(color.y);
                textureCoordinates.push_back(color.z);
            }
        }
    }
    else
    {
        for(int y = 0; y < CHUNK_SIZE; y+= increment)
        {
            for(int x = 0; x < CHUNK_SIZE; x+= increment)
            {
                vertices.push_back( {
                                        x * BLOCK_SIZE,
                                        heightmap[ x ][ y ] ,
                                        y * BLOCK_SIZE
                                    } );

                textureCoordinates.push_back(x);
                textureCoordinates.push_back(y);
            }
        }
    }

    int newSize = BLOCK_NUMBER/ increment + 1;
    for(int x = 0, xIndex = 0; x < newSize - 1; x++)
    {
        for(int y = 0, yIndex = 0; y < newSize - 1; y++)
        {
            indices.push_back(0 + xIndex + yIndex);
            indices.push_back(1 + xIndex + yIndex);
            indices.push_back(newSize + xIndex + yIndex);

            indices.push_back(1 + xIndex + yIndex);
            indices.push_back(newSize+1 + xIndex + yIndex);
            indices.push_back(newSize + xIndex + yIndex);

            yIndex += newSize;
        }
        xIndex++;
    }
}



void TerrainSection::generateNormals(
        const std::vector<glm::vec3> &vertices,
        std::vector<GLfloat> &normals )
{
    using namespace world_const;

    unsigned LOD_inc = pow(2, LOD);
    if(LOD_inc > world_const::BLOCK_NUMBER) LOD_inc = world_const::BLOCK_NUMBER;
    int increment = (LOD_inc == 0)? 1 : LOD_inc;
    unsigned newSize = BLOCK_NUMBER/ increment + 1;
    unsigned newArea = newSize*newSize;


    for(unsigned i=0; i < vertices.size(); i++)
    {
        glm::vec3 current = vertices.at(i);

        glm::vec3 left = { 0, 0, 0};
        glm::vec3 right = { 0, 0, 0};

        glm::vec3 top = { 0, 0, 0};
        glm::vec3 bottom = { 0, 0, 0};

        //check for border cases, so that you wont get vertices from another side of surface
        if(i >=1 &&  i % newSize != 0)
            left = vertices.at( i - 1  ) - current;

        if( i < newArea - 1  && (i +1 ) % newSize != 0)
            right = vertices.at( i + 1 ) - current;

        if( i >= newSize )
            top = vertices.at( i - newSize ) - current;

        if( i < newArea - newSize  )
            bottom = vertices.at( i + newSize ) - current;


        glm::vec3 crossProduct;

        crossProduct = glm::cross( top, left) + glm::cross( right, top ) + glm::cross( left, bottom ) + glm::cross( bottom, right );
        crossProduct = glm::normalize(crossProduct);

        normals.push_back(crossProduct.x);
        normals.push_back(crossProduct.y);
        normals.push_back(crossProduct.z);
    }
}

