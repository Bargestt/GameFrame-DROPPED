#include "debugelements.h"

DebugElements::DebugElements()
{
//    model.addData(
//                {
//                    {//vertices
//                        -0.5,  0,  0,
//                         0.5,  0,  0,
//                         0,   0, 5,
//                    },
//                    {  //indeces
//                        0,1,2,

//                    },
//                    {   //texture

//                    }
//                }
//                );
    model.genVAO();
    vbo = model.addVBO(3,
                 {
                            -0.1,  0,  0,
                             0.1,  0,  0,
                             0,     0,  2,
                },
                 GL_DYNAMIC_DRAW
                 );
    model.addEBO({   0,1,2, } );

}

void DebugElements::loadShader(const char *vertexPath, const char *fragmentPath)
{
    shader.load(vertexPath,fragmentPath);
}

void DebugElements::addArrow(const Arrow& arrow)
{
    arrows.push_back( arrow );
}

void DebugElements::render(const Camera &camera)
{
    if(!arrows.empty())
    {
        shader.use();
        shader.setProjectionView(camera.getProjectionlViewMatrix());


        model.bindVAO();


        for(Arrow& arrow : arrows) {

            glm::quat orient;
            glm::mat4 m, scale;

            scale = glm::scale(scale,glm::vec3( arrow.baseWidth, 1.0f, 1.0f ));

            m = glm::translate(m, arrow.position);

            orient *= glm::angleAxis(glm::radians(arrow.rotation.x),glm::vec3(1.0, 0.0, 0.0) * orient);
            orient *= glm::angleAxis(glm::radians(arrow.rotation.y),glm::vec3(0.0, 1.0, 0.0) * orient);
            orient *= glm::angleAxis(glm::radians(arrow.rotation.z),glm::vec3(0.0, 0.0, 1.0) * orient);

            shader.setModel( m * glm::mat4_cast(orient) * scale );
            shader.setVec("color", arrow.color);

            glDrawElements(GL_TRIANGLES, model.getIndecesCount(), GL_UNSIGNED_INT,0);
        }
    }
    arrows.clear();

}
