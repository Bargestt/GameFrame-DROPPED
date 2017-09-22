#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <Renderer/Modules/basemodel.h>
#include <Renderer/Modules/lightsource.h>

#include <ResourceManager/resourcemanager.h>


#include <glm.h>

#include <camera.h>
#include <shader.h>
#include <entity.h>

class RenderObject
{
protected:
    BaseModel m_Model;
    Shader m_Shader;

    std::vector<Entity> m_Objects;

    const TextureAtlas* m_pAtlas = nullptr;
    const LightSource *lightSource = nullptr;

    virtual void setTextureCoords(  const std::vector<GLfloat>& texCoords ) = 0;
public:
    RenderObject()
    { m_pAtlas = ResourceManager::get()->m_Atlas; }

    virtual void loadShader( const char *vertexPath, const char *fragmentPath ) = 0;

    virtual void loadObject(const Mesh &mesh) = 0;

    void loadAtlas( const TextureAtlas* atlas ){ m_pAtlas = atlas; }

    virtual void setTextureTile(int x, int y) = 0;

    virtual void setLightSource(const LightSource& light) = 0;

    virtual void add( const Entity &entity ) = 0;

    virtual void render( const Camera &camera )= 0;
};

#endif // RENDEROBJECT_H
