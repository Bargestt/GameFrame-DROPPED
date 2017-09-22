#ifndef COLLISIONPACKET_H
#define COLLISIONPACKET_H

#include <glm.h>
#include <Util/Collisions/collisioncheckfunc.h>

class CollisionPacket {
public:
    glm::vec3  eRadius; // ellipsoid radius
    // Information about the move being requested: (in R3)
    glm::vec3  R3Velocity;
    glm::vec3  R3Position;
    // Information about the move being requested: (in eSpace)
    glm::vec3  velocity;
    glm::vec3  normalizedVelocity;
    glm::vec3  basePoint;
    // Hit information
    bool foundCollision;
    double nearestDistance;
    glm::vec3  intersectionPoint;
};

#endif // COLLISIONPACKET_H
