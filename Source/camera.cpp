#include "camera.h"

Camera::Camera(const Config& set) : m_Config(set)
{
    position = {0, 0, -3.5};
    rotation = {0,0,0};

    m_pHolder = this; // чтобы не крашилась если не закреплена

    m_ProjectionMatrix = mathfunc::makeProjectionMatrix(m_Config);

    m_OrthoMatrix = glm::ortho(0.0f, static_cast<float>(m_Config.window_Width),
                               0.0f, static_cast<float>(m_Config.window_Height));
}

Camera::Camera(const Camera &other)
{
    position = other.position;
    rotation = other.rotation;
    m_pHolder = other.m_pHolder;
    m_Config = other.m_Config;
    m_OrthoMatrix = other.m_OrthoMatrix;
    m_ViewMatrix = other.m_ViewMatrix;
    m_ProjectionMatrix = other.m_ProjectionMatrix;
    m_ProjectionVIewMatrix = other.m_ProjectionVIewMatrix;
}

void Camera::updateMatrices()
{
    position = m_pHolder->position;
    rotation = m_pHolder->rotation;

    m_ViewMatrix = mathfunc::makeViewMatrix(*this);

    m_ProjectionVIewMatrix= m_ProjectionMatrix*m_ViewMatrix;

    //std::cout<<rotation.x<<":"<<rotation.y<<":"<<rotation.z<<":"<<std::endl;
}

const glm::mat4 &Camera::getViewMatrix() const noexcept
{
    return m_ViewMatrix;
}

const glm::mat4 &Camera::getProjectionlMatrix() const noexcept
{
    return m_ProjectionMatrix;
}

const glm::mat4 &Camera::getProjectionlViewMatrix() const noexcept
{
    return m_ProjectionVIewMatrix;
}

const glm::mat4 &Camera::getOrthoMatrix() const noexcept
{
    return m_OrthoMatrix;
}

void Camera::attach(const Entity &entity)
{
    m_pHolder = &entity;
}

void Camera::detach()
{
    m_pHolder = this;
}

Camera Camera::reflectionCam(float height) const
{
    Camera cam( *this);
    cam.position.y -= 2* (cam.position.y - height);


    cam.rotation.x =  -cam.rotation.x;
    return cam;
}
