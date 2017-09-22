#ifndef COLLISIONCHECKFUNC_H
#define COLLISIONCHECKFUNC_H


#include <glm.h>
#include <glm/gtx/norm.hpp>
#include <MathFunctions/mathfunctions.h>
#include <Util/Collisions/plane.h>

class CollisionPacket;

namespace mathfunc {

    void checkTriangle(CollisionPacket* colPackage, const glm::vec3& p1,const glm::vec3& p2,const glm::vec3& p3);


}



#endif // COLLISIONCHECKFUNC_H
