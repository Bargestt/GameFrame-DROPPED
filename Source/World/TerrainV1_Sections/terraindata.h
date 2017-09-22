#ifndef TERRAINDATA_H
#define TERRAINDATA_H

#include <Util/array_2d.h>

#include <glheader.h>
#include <glm.h>

#include <World/worldconstants.h>
#include <MathFunctions/mathfunctions.h>


class TerrainData
{
    using Array2D = Array2D_T<GLfloat, world_const::CHUNK_SIZE,world_const::CHUNK_SIZE>;
    using Array2Dvec3 = Array2D_T<glm::vec3, world_const::CHUNK_SIZE,world_const::CHUNK_SIZE>;
protected:    
    glm::vec3 m_Position;
    Array2D m_HeightMap;
    Array2Dvec3 m_ColorMap;
public:
    TerrainData();
    TerrainData(const Array2D& heightMap);
    TerrainData(const Array2D& heightMap, float x, float y);
    TerrainData(const Array2D& heightMap, const Array2Dvec3& colorMap, float x, float y);

    const Array2D& heightMap() const;
    const Array2Dvec3& colorMap() const;
    void setColorMap(const Array2Dvec3& colorMap);

    bool contains(const glm::vec2& point) const;

    glm::vec2 toLocal(const glm::vec2& globalPos) const;

    glm::vec3 position() const;
    glm::vec3 center() const;
    glm::ivec3 gridPosition() const;

    GLfloat heightAt(glm::vec2 globalPos) const;
    GLfloat heightAt_L(glm::vec2 localPos) const;

    GLfloat heightAt(int x_local, int z_local);

    void setHeightAt(glm::vec3 newHeight_global);

    static glm::vec3 colorByHeight(float height);
    static glm::vec3 s_Colors[5];

    enum color
    {
        SAND = 0,
        GRASS,
        ROCK,
        SNOW
    };
};



#endif // TERRAINDATA_H
