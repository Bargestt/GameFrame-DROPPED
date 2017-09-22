#include "lightsource.h"

LightSource::LightSource() : m_LightColor(1,1,1), m_Position(0,0,0)
{    
}

LightSource::LightSource(glm::vec3 position, glm::vec3 color) : m_LightColor(color)
{
    m_Position.x = position.x;
    m_Position.y = position.y;
    m_Position.z = position.z;
}

void LightSource::move(float dx, float dy, float dz)
{
    m_Position.x += dx;
    m_Position.y += dy;
    m_Position.z += dz;
}



void LightSource::setColor(float r, float g, float b)
{
    m_LightColor.x = r;
    m_LightColor.y = g;
    m_LightColor.z = b;
}

glm::vec3 LightSource::getColor() const
{
    return m_LightColor;
}

glm::vec3 LightSource::getPosition() const
{
    return m_Position;
}

void LightSource::setPosition(float x, float y, float z)
{
    m_Position.x = x;
    m_Position.y = y;
    m_Position.z = z;
}

void LightSource::applyToShader(const Shader &shader) const
{
    shader.use();
    shader.setVec("lightPos", m_Position);
    shader.setVec("lightColor", m_LightColor);
}
