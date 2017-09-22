#ifndef PLAYER_H
#define PLAYER_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <entity.h>
#include <World/TerrainV1_Sections/terrain.h>

#include <Util/Collisions/collisionpacket.h>


struct Stats
{
    float maxSpeed = 100;
    float walkSpeed = 7;
    float runSpeed = 100;

    float fallSpeed = -5;
};

class Player : public Entity
{
    Stats stat;
    enum Flags : unsigned char
    {
         onGround = 0x1, // hex for 0000 0001
         inAir = 0x2, // hex for 0000 0010
         noclip = 0x4, // hex for 0000 0100
         option4 = 0x8 // hex for 0000 1000
    };

    float maxSpeed = stat.maxSpeed * stat.maxSpeed;

    float walkSpeed = stat.walkSpeed;
    float runSpeed = stat.runSpeed;

    float fallSpeed  = stat.fallSpeed;

    glm::vec3 velocity;

    unsigned char flags = 0;

    const Terrain* m_pTerrain = nullptr;

    std::string m_Status;


    CollisionPacket* collisionPackage;


    int collisionRecursionDepth;
public:



    Player();
    Player(GLFWwindow* window);

    void connectToterrain(const Terrain &world);

    void update(float dt);
    void moveTo(const glm::vec3& pos);

    void handleInput(GLFWwindow* window);

    std::string& statusStr();

private:

    void mouseMove(GLFWwindow *window);
    void keyboardInput(GLFWwindow *window);


//    void collideAndSlide(const glm::vec3 &vel,
//                                          const glm::vec3 &gravity, bool grav = false);
//    glm::vec3 collideWithWorld(const glm::vec3& pos,
//                                             const glm::vec3& vel);
};

#endif // PLAYER_H
