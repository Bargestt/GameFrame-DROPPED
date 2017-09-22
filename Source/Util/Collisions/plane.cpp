#include "plane.h"

Plane::Plane(const glm::vec3& origin1, const glm::vec3& normal1) {
    this->normal = normal1;
    this->origin = origin1;

    equation[0] = normal.x;
    equation[1] = normal.y;
    equation[2] = normal.z;
    equation[3] = -(normal.x*origin.x + normal.y*origin.y + normal.z*origin.z);
}

// Construct from triangle:
Plane::Plane(const glm::vec3& p1,const glm::vec3& p2,const glm::vec3& p3)
{
    glm::vec3 v1 = p2-p1;
    glm::vec3 v2 = p3-p1;

    normal = glm::cross(v2, v1);
    normal = glm::normalize(normal);
    origin = p1;

    equation[0] = normal.x;
    equation[1] = normal.y;
    equation[2] = normal.z;
    equation[3] = -(normal.x*origin.x + normal.y*origin.y + normal.z*origin.z);
}
bool Plane::isFrontFacingTo(const glm::vec3& direction) const {
    //double dot = normal.dot(direction);
    double dot = glm::dot(normal, direction);
    return (dot <= 0);
}
double Plane::signedDistanceTo(const glm::vec3& point) const {
    //return (point.dot(normal)) + equation[3];
    return ( glm::dot(point, normal) + equation[3] );
}
