#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include <Renderer/Modules/renderobject.h>
#include <Renderer/Modules/lightsource.h>

class DynamicObject : public RenderObject
{
protected:
    enum Buffers
    {
        textureBuffer,
        vericeBuffer,
        indicesBuffer,
        normalsBuffer
    };
    GLuint m_Buffers[4];
    GLuint m_BufferSize[4];

    Mesh* currentMesh = nullptr;
public:
    DynamicObject();
    DynamicObject(const Mesh &mesh);
    ~DynamicObject();

    void clearMesh();
    void changeObject(const Mesh &mesh);

    // RenderObject interface
public:
    void loadShader(const char *vertexPath, const char *fragmentPath) override;
    void loadObject(const Mesh &mesh) override;
    void setTextureCoords(const std::vector<GLfloat> &texCoords) override;
    void setTextureTile(int x, int y) override;
    void setLightSource(const LightSource& light) override;
    void add(const Entity &entity) override;
    void render(const Camera &camera) override;
};

#endif // DYNAMICOBJECT_H
