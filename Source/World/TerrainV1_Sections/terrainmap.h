#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include <unordered_map>


#include <World/TerrainV1_Sections/terrainsection.h>

#include <World/worldconstants.h>

#include <MathFunctions/mathfunctions.h>
#include <MathFunctions/hash.h>
#include <MathFunctions/perlin.hpp>



class TerrainMap
{
    using Array2D = Array2D_T<GLfloat, world_const::CHUNK_SIZE,world_const::CHUNK_SIZE>;
    using Array2Dvec3 = Array2D_T<glm::vec3, world_const::CHUNK_SIZE,world_const::CHUNK_SIZE>;

    std::unordered_map<Point, TerrainSection*> m_WorldMap;
public:
    TerrainMap();
    ~TerrainMap();

    const std::unordered_map<Point, TerrainSection*>& data() const;

    TerrainSection& addPieceAt(Array2D& heightMap, int p_x, int p_y);
    TerrainSection& getPieceAt(Point point);

    void setVertice(float x, float y_value, float z, bool finalize = false);
    glm::vec3 getVertice(float x, float y) const;

    static Point toGrid(float x, float y);


    static const Array2D generate(int gx, int gy, bool flat = false);
    static const Array2Dvec3 generateColors(int gx, int gy);
};

#endif // TERRAINMAP_H
