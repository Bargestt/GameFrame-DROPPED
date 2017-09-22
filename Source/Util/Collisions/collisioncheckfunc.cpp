#include "collisioncheckfunc.h"

#include <Util/Collisions/collisionpacket.h>

void mathfunc::checkTriangle(CollisionPacket* colPackage,
                   const glm::vec3& p1,const glm::vec3& p2,const glm::vec3& p3){
    // Make the plane containing this triangle.
    Plane trianglePlane(p1,p2,p3);
    // Is triangle front-facing to the velocity vector?
    // We only check front-facing triangles
    // (your choice of course)
    if (trianglePlane.isFrontFacingTo(
                colPackage->normalizedVelocity)) {

        // Get interval of plane intersection:
        double t0, t1;
        bool embeddedInPlane = false;
        // Calculate the signed distance from sphere
        // position to triangle plane
        double signedDistToTrianglePlane =
                trianglePlane.signedDistanceTo(colPackage->basePoint);

        // cache this as we’re going to use it a few times below:
        float normalDotVelocity =  glm::dot( trianglePlane.normal, colPackage->velocity);

        // if sphere is travelling parrallel to the plane:
        if (normalDotVelocity == 0.0f) {
            if (fabs(signedDistToTrianglePlane) >= 1.0f) {
                // Sphere is not embedded in plane.
                // No collision possible:
                return;
            }
            else {
                // sphere is embedded in plane.
                // It intersects in the whole range [0..1]
                embeddedInPlane = true;
                t0 = 0.0;
                t1 = 1.0;
            }

        }
        else {
            // N dot D is not 0. Calculate intersection interval:
            t0=(-1.0-signedDistToTrianglePlane)/normalDotVelocity;
            t1=( 1.0-signedDistToTrianglePlane)/normalDotVelocity;
            // Swap so t0 < t1
            if (t0 > t1) {
                double temp = t1;
                t1 = t0;
                t0 = temp;
            }
            // Check that at least one result is within range:
            if (t0 > 1.0f || t1 < 0.0f) {
                // Both t values are outside values [0,1]
                // No collision possible:
                return;
            }
            // Clamp to [0,1]
            if (t0 < 0.0) t0 = 0.0;
            if (t1 < 0.0) t1 = 0.0;
            if (t0 > 1.0) t0 = 1.0;
            if (t1 > 1.0) t1 = 1.0;
        }
        // OK, at this point we have two time values t0 and t1
        // between which the swept sphere intersects with the
        // triangle plane. If any collision is to occur it must
        // happen within this interval.
        glm::vec3 collisionPoint;
        bool foundCollison = false;
        float t = 1.0;
        // First we check for the easy case - collision inside
        // the triangle. If this happens it must be at time t0
        // as this is when the sphere rests on the front side
        // of the triangle plane. Note, this can only happen if
        // the sphere is not embedded in the triangle plane.

        if (!embeddedInPlane) {
            glm::vec3 planeIntersectionPoint = (colPackage->basePoint - trianglePlane.normal);
            planeIntersectionPoint.x +=  t0*colPackage->velocity.x;
            planeIntersectionPoint.y +=  t0*colPackage->velocity.y;
            planeIntersectionPoint.z +=  t0*colPackage->velocity.z;

            if ( checkPointInTriangle( planeIntersectionPoint,   p1,p2,p3 ) )
            {
                foundCollison = true;
                t = t0;
                collisionPoint = planeIntersectionPoint;
            }
        }
        // if we haven’t found a collision already we’ll have to
        // sweep sphere against points and edges of the triangle.
        // Note: A collision inside the triangle (the check above)
        // will always happen before a vertex or edge collision!
        // This is why we can skip the swept test if the above
        // gives a collision!
        if (foundCollison == false)
        {
            // some commonly used terms:
            glm::vec3 velocity = colPackage->velocity;
            glm::vec3 base = colPackage->basePoint;
            float velocitySquaredLength = glm::length2(velocity);
            float a,b,c; // Params for equation
            float newT;
            // For each vertex or edge a quadratic equation have to
            // be solved. We parameterize this equation as
            // a*t^2 + b*t + c = 0 and below we calculate the
            // parameters a,b and c for each test.
            // Check against points:
            a = velocitySquaredLength;
            // P1
            b = 2.0*( glm::dot( velocity, (base-p1) ) );
            c = glm::length2(p1-base) - 1.0;
            if (getLowestRoot(a,b,c, t, &newT))
            {
                t = newT;

                foundCollison = true;
                collisionPoint = p1;
            }
            // P2
            b = 2.0*( glm::dot( velocity, (base-p2) ) );
            c = glm::length2(p2-base) - 1.0;
            if (getLowestRoot(a,b,c, t, &newT))
            {
                t = newT;
                foundCollison = true;
                collisionPoint = p2;
            }
            // P3
            b = 2.0*(  glm::dot(velocity, (base-p3)) );
            c = glm::length2(p3-base) - 1.0;
            if (getLowestRoot(a,b,c, t, &newT))
            {
                t = newT;
                foundCollison = true;
                collisionPoint = p3;
            }
            // Check agains edges:
            // p1 -> p2:
            glm::vec3 edge = p2-p1;
            glm::vec3 baseToVertex = p1 - base;
            float edgeSquaredLength = glm::length2(edge);
            float edgeDotVelocity = glm::dot(edge, velocity);
            float edgeDotBaseToVertex = glm::dot( edge, baseToVertex );
            // Calculate parameters for equation
            a = edgeSquaredLength*-velocitySquaredLength +
                    edgeDotVelocity*edgeDotVelocity;
            b = edgeSquaredLength*(2* glm::dot( velocity, baseToVertex))-
                    2.0*edgeDotVelocity*edgeDotBaseToVertex;
            c = edgeSquaredLength*(1-glm::length2(baseToVertex))+
                    edgeDotBaseToVertex*edgeDotBaseToVertex;
            // Does the swept sphere collide against infinite edge?

            if (getLowestRoot(a,b,c, t, &newT)) {
                // Check if intersection is within line segment:
                float f=(edgeDotVelocity*newT-edgeDotBaseToVertex)/
                        edgeSquaredLength;
                if (f >= 0.0 && f <= 1.0) {
                    // intersection took place within segment.
                    t = newT;
                    foundCollison = true;
                    collisionPoint = p1 + f*edge;
                }
            }
            // p2 -> p3:
            edge = p3-p2;
            baseToVertex = p2 - base;
            edgeSquaredLength = glm::length2(edge);
            edgeDotVelocity = glm::dot(edge, velocity);
            edgeDotBaseToVertex = glm::dot(edge, baseToVertex);
            a = edgeSquaredLength*-velocitySquaredLength +
                    edgeDotVelocity*edgeDotVelocity;
            b = edgeSquaredLength*(2*glm::dot(velocity, baseToVertex))-
                    2.0*edgeDotVelocity*edgeDotBaseToVertex;
            c = edgeSquaredLength*(1-glm::length2(baseToVertex))+
                    edgeDotBaseToVertex*edgeDotBaseToVertex;
            if (getLowestRoot(a,b,c, t, &newT)) {
                float f=(edgeDotVelocity*newT-edgeDotBaseToVertex)/
                        edgeSquaredLength;
                if (f >= 0.0 && f <= 1.0) {
                    t = newT;
                    foundCollison = true;
                    collisionPoint = p2 + f*edge;
                }
            }
            // p3 -> p1:
            edge = p1-p3;
            baseToVertex = p3 - base;
            edgeSquaredLength = glm::length2(edge);
            edgeDotVelocity = glm::dot(edge, velocity);

            edgeDotBaseToVertex = glm::dot(edge, baseToVertex);
            a = edgeSquaredLength*-velocitySquaredLength +
                    edgeDotVelocity*edgeDotVelocity;
            b = edgeSquaredLength*(2*glm::dot(velocity, baseToVertex))-
                    2.0*edgeDotVelocity*edgeDotBaseToVertex;
            c = edgeSquaredLength*(1-glm::length2(baseToVertex))+
                    edgeDotBaseToVertex*edgeDotBaseToVertex;
            if (getLowestRoot(a,b,c, t, &newT)) {
                float f=(edgeDotVelocity*newT-edgeDotBaseToVertex)/
                        edgeSquaredLength;
                if (f >= 0.0 && f <= 1.0) {
                    t = newT;
                    foundCollison = true;
                    collisionPoint = p3 + f*edge;
                }
            }
        }
        // Set result:
        if (foundCollison == true) {
            // distance to collision: ’t’ is time of collision
            float distToCollision = t*colPackage->velocity.length();
            // Does this triangle qualify for the closest hit?
            // it does if it’s the first hit or the closest
            if (colPackage->foundCollision == false ||
                    distToCollision < colPackage->nearestDistance) {
                // Collision information nessesary for sliding
                colPackage->nearestDistance = distToCollision;
                colPackage->intersectionPoint=collisionPoint;
                colPackage->foundCollision = true;
            }
        }
    } // if not backface
}


