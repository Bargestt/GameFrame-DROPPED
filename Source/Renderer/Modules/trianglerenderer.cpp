#include "trianglerenderer.h"



TriangleRenderer::TriangleRenderer()
{
    model.genVAO();
    vbo = model.addVBO(3, {1,1,1, 2,2,2, 3,3,3}, GL_DYNAMIC_DRAW);
}

void TriangleRenderer::loadShader(const char *vertexPath, const char *fragmentPath)
{
    shader.load(vertexPath, fragmentPath);
}

void TriangleRenderer::add(const Triangle &tri)
{
    triangles.push_back(tri);
}

void TriangleRenderer::render(const Camera &camera)
{
    if(!triangles.empty()){
        shader.use();

//        shader.setView(camera.getViewMatrix());
//        shader.setProjection(camera.getProjectionlMatrix());
        shader.setProjectionView(camera.getProjectionlViewMatrix());



        glm::mat4 modelMatrix, m2;
        for(Triangle& tri: triangles) {
            model.bindVAO();
            model.changeVBO(0, tri.toVector());

            shader.setModel(modelMatrix);

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
    triangles.clear();
}

