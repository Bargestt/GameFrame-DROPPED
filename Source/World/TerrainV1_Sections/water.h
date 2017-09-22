#ifndef WATER_H
#define WATER_H

#include <glheader.h>
#include <glm.h>

#include <World/worldconstants.h>
#include <Renderer/Modules/basemodel.h>
#include <shader.h>
#include <Renderer/masterrenderer.h>

class Water
{
public:

    glm::vec3 m_Position = {0,0,0};
    BaseModel m_Model;
    Shader m_Shader;

    Water();

    void render(MasterRenderer& renderer);

};

#endif // WATER_H
