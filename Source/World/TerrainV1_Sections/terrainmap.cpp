#include "terrainmap.h"

TerrainMap::TerrainMap()
{

}

TerrainMap::~TerrainMap()
{
    for(auto& pair : m_WorldMap)
    {
        delete pair.second;
    }
    m_WorldMap.clear();
}

const std::unordered_map<Point, TerrainSection*>&   TerrainMap::data() const
{
    return m_WorldMap;
}

TerrainSection &TerrainMap::addPieceAt(TerrainMap::Array2D &heightMap, int p_x, int p_y)
{
    Point pos = {p_x, p_y};
    auto map = m_WorldMap.find(pos);

    if(map != m_WorldMap.end()){
        delete map->second;
    }

    TerrainSection* piece = new TerrainSection( heightMap,
                                                                            p_x * world_const::BLOCK_NUMBER,
                                                                            p_y * world_const::BLOCK_NUMBER);
    m_WorldMap[pos] = piece;
    return *piece;
}

TerrainSection &TerrainMap::getPieceAt(Point point)
{
    auto map = m_WorldMap.find(point);
    if(map != m_WorldMap.end())
    {
        return  *map->second;
    }
    TerrainSection* piece = new TerrainSection(
                                             TerrainMap::generate( point.x, point.z ),
                                             TerrainMap::generateColors( point.x, point.z ),
                                             point.x*world_const::BLOCK_NUMBER,
                                             point.z*world_const::BLOCK_NUMBER);    
    m_WorldMap[point] = piece;
    return *piece;
}

void TerrainMap::setVertice(float x, float y_value, float z, bool finalize)
{
    //    int terraintX = floor(x / world_const::BLOCK_NUMBER);
    //    int terraintY = floor(z / world_const::BLOCK_NUMBER);

    //    auto pair = worldMap.find({ terraintX, terraintY});
    //    if(pair != worldMap.end())
    //    {
    //        pair->second->setHeightAt(  glm::vec3( (int)x, y_value, (int)z) );
    //    }
    //    else
    //    {
    //        TerrainSection& section = addPieceAt(terraintX,terraintY);
    //        section.setHeightAt( glm::vec3( (int)x, y_value, (int)z) );
    //    }
}

glm::vec3 TerrainMap::getVertice(float x, float y) const
{
    Point pos( floor(x / world_const::BLOCK_NUMBER),
                      floor(y / world_const::BLOCK_NUMBER) );

    auto it = m_WorldMap.find( pos );
    if( it != m_WorldMap.end())
    {
        TerrainSection* terrain = it->second;
        return glm::vec3(x, terrain->getData().heightAt({x,y}), y);
    }
    return {0,0,0};
}

Point TerrainMap::toGrid(float x, float y)
{
    return Point( floor(x / world_const::BLOCK_NUMBER),
                  floor(y / world_const::BLOCK_NUMBER) );
}

const TerrainMap::Array2D TerrainMap::generate(int gx, int gy, bool flat)
{
    using namespace  world_const;
    double frequency = 1.0;
    int octaves = 6;
    uint32_t seed = 12345;

    const siv::PerlinNoise perlin(seed), perlin2(seed*2);

    const double fx = CHUNK_SIZE / frequency;
    const double fy = CHUNK_SIZE / frequency;


    Array2D map;
    glm::vec3 posit = { BLOCK_NUMBER*gx, 0, BLOCK_NUMBER*gy };

    for(int y = 0; y < CHUNK_SIZE; y++){
        for(int x = 0; x < CHUNK_SIZE; x++){

            if(flat)
                map[x][y] = 1;
            else
            {
                map[x][y] =
                        45
                        * mathfunc::expProp(perlin.octaveNoise0_1( (posit.x + x) / fx, (posit.z +  y) / fy, octaves),
                                              -0.0000000105722, -0.08618227,-3.811733);
            }
            //y = 0.1052867 - 0.09327894*x + 2.396853*x^2 - 1.750194*x^3
            //y = 0.09029371 + 2.805503*x - 26.57663*x^2 + 85.42599*x^3 - 95.34382*x^4 + 35*x^5
            //y = -1.0572260000000001*10^-22 - (-0.08618227/-3.811733)*(1 - e^(+3.811733*x))
        }
    }
    return map;
}

const TerrainMap::Array2Dvec3 TerrainMap::generateColors(int gx, int gy)
{
    using namespace  world_const;
    double frequency = 1.0;
    int octaves = 6;
    uint32_t seed = 12345;

    const siv::PerlinNoise perlin(seed), perlin2(seed*2);

    const double fx = CHUNK_SIZE / frequency;
    const double fy = CHUNK_SIZE / frequency;


    Array2Dvec3 map;
    glm::vec3 posit = { BLOCK_NUMBER*gx, 0, BLOCK_NUMBER*gy };

    for(int y = 0; y < CHUNK_SIZE; y++){
        for(int x = 0; x < CHUNK_SIZE; x++){
                map[x][y] = TerrainData::colorByHeight
                        (
                            perlin.octaveNoise0_1
                            (
                                (posit.x + x) / fx,
                                (posit.z +  y) / fy,
                                octaves
                            )
                        );
        }
    }
    return map;
}
