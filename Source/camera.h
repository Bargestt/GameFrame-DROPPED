#ifndef CAMERA_H
#define CAMERA_H

#include <entity.h>
#include <MathFunctions/matrixfunctions.h>
#include <config.h>

#include <iostream>

class Camera : public Entity
{    
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ProjectionVIewMatrix;
    glm::mat4 m_OrthoMatrix;

    Config m_Config;

    const Entity* m_pHolder;

public:
    Camera(const Config& set);
    Camera(const Camera& other);

    void updateMatrices();

    const glm::mat4& getViewMatrix() const noexcept;
    const glm::mat4& getProjectionlMatrix() const noexcept;
    const glm::mat4& getProjectionlViewMatrix() const noexcept;
    const glm::mat4& getOrthoMatrix() const noexcept;

    void attach(const Entity& entity);
    void detach();

    Camera reflectionCam( float height) const;

};

#endif // CAMERA_H
