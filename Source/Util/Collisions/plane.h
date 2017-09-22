#ifndef PLANE_H
#define PLANE_H

#include <glm.h>

class Plane {

public:
    float equation[4];
    glm::vec3 origin;
    glm::vec3 normal;

    Plane(const glm::vec3& origin1, const glm::vec3& normal1);
    Plane(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);

    bool isFrontFacingTo(const glm::vec3& direction) const;
    double signedDistanceTo(const glm::vec3& point) const;
};



#endif // PLANE_H
