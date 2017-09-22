#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

#include <glm.h>

class Camera;

struct Entity;
struct Config;


namespace mathfunc {

    glm::mat4 makeModelMatrix(const Entity& entity);
    glm::mat4 makeModelMatrix2(const Entity& entity);
    glm::mat4 makeModelMatrix3(const Entity& entity);


    glm::mat4 makeModelMatrix_Translation(const Entity& entity);


    glm::mat4 makeViewMatrix(const Camera& camera);

    glm::mat4 makeProjectionMatrix(const Config& config);

}
#endif // MATRIXFUNCTIONS_H
