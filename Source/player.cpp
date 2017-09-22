#include "player.h"

Player::Player()
{
    maxSpeed = 16;

    position = {0, 0, 3.5};
    rotation = {0,0,0};
    //flags |= noclip;

    velocity = {0,0,0};

    collisionPackage = new CollisionPacket();
    collisionPackage->eRadius = glm::vec3(1,1,1);
}
void Player::connectToterrain(const Terrain &world)
{
    this->m_pTerrain = &world;
}

void Player::update(float dt)
{
    m_Status = "X: "+std::to_string(position.x) + "Y: " + std::to_string(position.z) + "Z: " + std::to_string(position.y) ;


//    velocity.x = dx*dt;
//    velocity.y = dy*dt;
//    velocity.z = dz*dt;

   if(flags ^ noclip)
   {
       if(m_pTerrain != nullptr)
       {
           glm::vec2 pos;
           pos.x = position.x;
           pos.y = position.z;
           glm::vec3  current = m_pTerrain->getMap().getVertice(pos.x,pos.y);

           if(current.y + 1 >= position.y){
               position.y = 1 +  current.y;
           }
           else
               velocity.y += fallSpeed;

           m_Status += "      P: " + std::to_string(current.y)  +
                   " C: "+ std::to_string((int)current.x) + " : "  + std::to_string((int)current.z);
       }
   }

//   collideAndSlide(velocity, {0,0,0});
//   velocity.y = -5;
//    collideAndSlide(velocity, {0,0,0}, true);
   //moveTo(velocity + position);
   float len = glm::length2(velocity);
   if( len > maxSpeed)
   {
       velocity = glm::normalize(velocity)*sqrtf(len);
   }
   position +=velocity*dt;

}

void Player::moveTo(const glm::vec3 &pos)
{
    glm::vec3 direction = pos - position;
    if(glm::length2(direction) < 0.01) return;
    velocity  = glm::normalize(direction)*maxSpeed;
}

void Player::handleInput(GLFWwindow *window)
{
    keyboardInput(window);
    mouseMove(window);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        maxSpeed = runSpeed;
    }
    else
        maxSpeed = walkSpeed;
}

std::__cxx11::string &Player::statusStr()
{
    return m_Status;
}





void Player::mouseMove(GLFWwindow *window)
{
    static double xpos, ypos;    

    glfwGetCursorPos(window,&xpos,&ypos);
    static double lastx = xpos,lasty=ypos;

    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos; // reversed since y-coordinates range from bottom to top
    lastx = xpos;
    lasty = ypos;

    float sensitivity = 0.15f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    rotation.x -= yoffset;
    rotation.y += xoffset;


    if(rotation.x > 89.0f)
      rotation.x =  89.0f;
    if(rotation.x < -89.0f)
      rotation.x = -89.0f;

    if(rotation.y > 359.9999f)
      rotation.y =  0.0f;
    if(rotation.y < -359.9999f)
      rotation.y = 0.0f;
}

void Player::keyboardInput(GLFWwindow *window)
{
    int dx =0, dy=0,dz=0;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        dz += maxSpeed*(sin(glm::radians(rotation.y-90)));
        dx += maxSpeed*(cos(glm::radians(rotation.y-90)));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
            dz -= maxSpeed*(sin(glm::radians(rotation.y-90)));
            dx -= maxSpeed*(cos(glm::radians(rotation.y-90)));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        dz -= maxSpeed*(sin(glm::radians(rotation.y)));
        dx -= maxSpeed*(cos(glm::radians(rotation.y)));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        dz += maxSpeed*(sin(glm::radians(rotation.y)));
        dx += maxSpeed*(cos(glm::radians(rotation.y)));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        dy = maxSpeed;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        dy = -maxSpeed;

    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
    {
        position = glm::vec3(0,0,0);
    }

    velocity.x = dx;
    velocity.y = dy;
    velocity.z = dz;

}



//void Player::collideAndSlide(const glm::vec3 &vel,
//                                      const glm::vec3 &gravity, bool grav)
//{
//    // Do collision detection:
//    collisionPackage->R3Position = position;
//    collisionPackage->R3Velocity = vel;
//    // calculate position and velocity in eSpace
//    glm::vec3 eSpacePosition = collisionPackage->R3Position/
//            collisionPackage->eRadius;
//    glm::vec3 eSpaceVelocity = collisionPackage->R3Velocity/
//            collisionPackage->eRadius;
//    // Iterate until we have our final position.
//    collisionRecursionDepth = 0;
//    glm::vec3 finalPosition = collideWithWorld(eSpacePosition,
//                                            eSpaceVelocity);


//    // Add gravity pull:

//    // To remove gravity uncomment from here .....
//    // Set the new R3 position (convert back from eSpace to R3
////    collisionPackage->R3Position = finalPosition*collisionPackage->eRadius;
////    collisionPackage->R3Velocity = glm::vec3(0,0,0);
////    eSpaceVelocity = glm::vec3(0,0,0)/collisionPackage->eRadius;
////    collisionRecursionDepth = 0;
////    glm::vec3 temp = collideWithWorld(finalPosition, eSpaceVelocity);
////    if(glm::length2(temp - finalPosition) > 3)
////        finalPosition = temp;
//    // ... to here
//    // Convert final result back to R3:
//    finalPosition = finalPosition*collisionPackage->eRadius;
//    // Move the entity (application specific function)

//    if(grav)
//    {
//        if(fabsf(glm::length2(finalPosition - collisionPackage->R3Position)) < 5)
//        {
//            finalPosition =             collisionPackage->R3Position;
//        }
//    }

//    //position = finalPosition;
//    moveTo(finalPosition);
//}

//// Set this to match application scale..
//const float unitsPerMeter = 100.0f;

//glm::vec3 Player::collideWithWorld(const glm::vec3& pos,
//                                         const glm::vec3& vel)
//{
//    // All hard-coded distances in this function is
//    // scaled to fit the setting above..
//    float unitScale = unitsPerMeter / 100.0f;
//    float veryCloseDistance = veryCloseDistance = 0.005f * unitScale;
//    // do we need to worry?
//    if (collisionRecursionDepth>5)
//        return pos;
//    // Ok, we need to worry:
//    collisionPackage->velocity = vel;

//    collisionPackage->normalizedVelocity = vel;
//    collisionPackage->normalizedVelocity = glm::normalize(collisionPackage->normalizedVelocity);
//    collisionPackage->basePoint = pos;
//    collisionPackage->foundCollision = false;

//    // Check for collision (calls the collision routines)
//    // Application specific!!

//    PlaneR rect = { -1,15,-5,  7,10,5 };
//    mathfunc::checkTriangle(collisionPackage,rect.topLeft(),rect.topRight(),rect.bottomRight());
//    mathfunc::checkTriangle(collisionPackage,rect.topLeft(),rect.bottomLeft(),rect.bottomRight());

//    //m_pTerrain->checkCollisions(collisionPackage);

////     auto triangles = m_pTerrain->getTrianglesInBox(position - 0.5f, glm::vec3(1,1,1));
////     for(Triangle& tri : triangles)
////     {
////         mathfunc::checkTriangle(collisionPackage,tri.p1,tri.p2, tri.p3);
////     }

//    mathfunc::checkTriangle(collisionPackage,
//                            m_pTerrain->getVertice(position.x + 1, position.z - 1),
//                            m_pTerrain->getVertice(position.x + 1, position.z + 1),

//                            m_pTerrain->getVertice(position.x - 1, position.z)
//                            );
//    mathfunc::checkTriangle(collisionPackage,
//                            m_pTerrain->getVertice(position.x - 1, position.z - 1),
//                            m_pTerrain->getVertice(position.x - 1, position.z + 1),

//                            m_pTerrain->getVertice(position.x +1, position.z)
//                            );

//    // If no collision we just move along the velocity
//    if (collisionPackage->foundCollision == false) {
//        return pos + vel;
//    }


//    // *** Collision occured ***
//    // The original destination point
//    glm::vec3 destinationPoint = pos + vel;
//    glm::vec3 newBasePoint = pos;
//    // only update if we are not already very close
//    // and if so we only move very close to intersection..not
//    // to the exact spot.
//    if (collisionPackage->nearestDistance>=veryCloseDistance)
//    {
//        glm::vec3 V = vel;
//        V = glm::normalize(V) * (float)( collisionPackage->nearestDistance - veryCloseDistance );
//        newBasePoint = collisionPackage->basePoint + V;
//        // Adjust polygon intersection point (so sliding
//        // plane will be unaffected by the fact that we
//        // move slightly less than collision tells us)
//        V = glm::normalize(V);
//        collisionPackage->intersectionPoint -=
//                veryCloseDistance * V;
//    }
//    else
//        return newBasePoint - vel;
//    // Determine the sliding plane
//    glm::vec3 slidePlaneOrigin = collisionPackage->intersectionPoint;
//    glm::vec3 slidePlaneNormal =  newBasePoint - collisionPackage->intersectionPoint;

//    slidePlaneNormal = glm::normalize(slidePlaneNormal);
//    Plane slidingPlane(slidePlaneOrigin,slidePlaneNormal);
//    // Again, sorry about formatting.. but look carefully ;)
//    glm::vec3 newDestinationPoint = destinationPoint -
//            (float)slidingPlane.signedDistanceTo(destinationPoint)*  slidePlaneNormal;
//    // Generate the slide vector, which will become our new
//    // velocity vector for the next iteration
//    glm::vec3 newVelocityVector = newDestinationPoint -
//            collisionPackage->intersectionPoint;
//    // Recurse:
//    // dont recurse if the new velocity is very small
//    if ( glm::length(newVelocityVector) < veryCloseDistance) {
//        return newBasePoint;
//    }
//    collisionRecursionDepth++;
//    return collideWithWorld(newBasePoint,newVelocityVector);
//}


