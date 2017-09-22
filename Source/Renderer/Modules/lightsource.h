#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm.h>
#include <shader.h>

class LightSource
{
    glm::vec3 m_LightColor;
    glm::vec3 m_Position;

public:
    LightSource();
    LightSource(glm::vec3 position, glm::vec3 color);

    void move(float dx, float dy, float dz);

    void setColor(float r, float g, float b);

    glm::vec3 getColor() const;
    glm::vec3 getPosition() const;
    void setPosition(float x, float y, float z);

    void applyToShader(const Shader& shader) const;
};

#endif // LIGHTSOURCE_H
