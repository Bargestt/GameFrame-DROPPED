#ifndef TERRAINREND_H
#define TERRAINREND_H


#include <World/terraindata.h>
#include <Renderer/Modules/basemodel.h>

class TerrainRend
{
    const TerrainData* m_Data = nullptr;
    BaseModel m_Model;

    enum Buffers{
        Vertices = 0,   Indices,    Texture,    Normals,
        BufferCount
    };
    unsigned buffers[BufferCount];
    unsigned bufferSizes[BufferCount];

    bool visible = true;

    bool free = true;
    bool buffered = false;
public:
    TerrainRend();
    TerrainRend(const TerrainData *data);


    void setData(const TerrainData *data);
    const TerrainData* getData() const;

    bool validateBufferToData(const Mesh& mesh) const;

    void createBuffer();
    void loadData();

    void update();

    void render();

    bool isVisible() const;
    void setVisibility(bool state);

    bool isFree() const;
    void setFree(bool state);

    bool isBuffered() const;

private:
    void updateBuffer(const Mesh& mesh);

    static Mesh makeMesh(const TerrainData& data);


public:

    bool operator ==(const TerrainData& other);
    bool operator ==(const TerrainRend& other);


};

#endif // TERRAINREND_H
