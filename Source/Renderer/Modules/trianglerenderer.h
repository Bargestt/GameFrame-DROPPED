#ifndef TRIANGLERENDERER_H
#define TRIANGLERENDERER_H

#include <Renderer/Modules/basemodel.h>
#include <shader.h>

#include <ResourceManager/resourcemanager.h>

#include <glm/glm.hpp>

#include <camera.h>



class TriangleRenderer
{
    BaseModel model;
    GLuint vbo;
    Shader shader;

    std::vector<Triangle> triangles;
public:
    TriangleRenderer();

    void loadShader(const char *vertexPath, const char *fragmentPath);

    void add(const Triangle &tri);

    void render(const Camera &camera);
};

#endif // TRIANGLERENDERER_H
