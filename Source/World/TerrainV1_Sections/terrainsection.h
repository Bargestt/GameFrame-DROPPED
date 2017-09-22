#ifndef TERRAINSECTION_H
#define TERRAINSECTION_H

#include <World/TerrainV1_Sections/terraindata.h>
#include <Renderer/Modules/basemodel.h>

class TerrainSection
{
    BaseModel m_Model;
    TerrainData m_TerrainData;
    bool visible = false;
    bool buffered = false;
    bool colorMap = true;

    int LOD = -1;

public:    
    using Array2D = Array2D_T<GLfloat, world_const::CHUNK_SIZE,world_const::CHUNK_SIZE>;
    using Array2Dvec3 = Array2D_T<glm::vec3, world_const::CHUNK_SIZE,world_const::CHUNK_SIZE>;

    TerrainSection();
    TerrainSection(const Array2D& data);
    TerrainSection(const Array2D& data, float x, float y);
    TerrainSection(const Array2D& data,const Array2Dvec3& colorMap, float x, float y);

    const TerrainData& getData() const;
    bool isVisible() const;
    void hide();
    void show();

    void freeBuffer();
    void genBuffer(unsigned LOD_level = 0);
    int getLOD_lvl();
    bool isBuffered()const;

    const TerrainData& getData();

    void render() const;    

private:
    void generate();

    void generateVertices(
                                          std::vector<glm::vec3> &vertices,
                                          std::vector<GLuint> &indices,
                                          std::vector<GLfloat> &textureCoordinates
                                         );

    void generateNormals(
            const std::vector<glm::vec3> &vertices,
                         std::vector<GLfloat> &normals);



};

#endif // TERRAINSECTION_H
