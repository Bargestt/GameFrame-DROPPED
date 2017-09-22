#ifndef ENTITY_H
#define ENTITY_H

#include <GLFW/glfw3.h>
#include <glm.h>
#include <vector>
#include <string>

struct Entity{

    glm::vec3 position;
    glm::vec3 rotation;    
    glm::vec3 scale;
    glm::vec2 texTile;

    Entity() : rotation(0,0,0), scale(1.0f,1.0f,1.0f), texTile(0,0)
    {   }
    Entity(const glm::vec3& pos) :
        position(pos), scale(1.0f,1.0f,1.0f), texTile(0,0)
    {    }
    Entity(const glm::vec3& pos, const glm::vec3& rot):
        position(pos), rotation(rot), scale(1.0f,1.0f,1.0f), texTile(0,0)
    {    }
    Entity(const glm::vec3& pos, const glm::vec3& rot, const glm::vec2& tile):
        position(pos), rotation(rot), scale(1.0f,1.0f,1.0f), texTile(tile)
    {    }
    Entity(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scal):
        position(pos), rotation(rot), scale(scal), texTile(0,0)
    {    }
    Entity(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scal, const glm::vec2& tile):
        position(pos), rotation(rot), scale(scal), texTile(tile)
    {    }


};
struct EntityExt : public Entity
{


};

struct TextObject
{
    std::string m_Text;
    GLfloat X;
    GLfloat Y;
    GLfloat m_Scale;
    glm::vec3 m_Color;
    TextObject(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) :
        m_Text(text), X(x), Y(y), m_Scale(scale), m_Color(color)
    {   }
};
struct Triangle
{
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;

    std::vector<GLfloat> toVector()
    {        return { p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, };    }
};



struct PlaneR
{
    float x1,y1,z1,  x2,y2, z2;

    glm::vec3 topLeft(){ return { x1,y1,z1 }; }
    glm::vec3 bottomLeft(){ return { x1,y2,z1 };  }
    glm::vec3 topRight(){ return { x2,y1,z2 };  }
    glm::vec3 bottomRight(){ return { x2,y2,z2 };  }

    glm::mat4 matrix()
    {
        glm::mat4 scale, rotate, translate, mat;

        scale = glm::scale(scale, glm::vec3(
                                             -glm::distance(topLeft(),topRight()),
                                             -glm::distance(topLeft(),bottomLeft()) ,
                                             -glm::distance(topLeft(),topRight()) ));
        translate = glm::translate(translate, topLeft() );

        glm::vec3 angles = {0,0,0};


        angles.y = -atan2f( z1 - z2,x1 - x2 ) ;

        rotate = glm::rotate( rotate, angles.y, {0.0f, 1.0f, 0.0f});


        return translate*scale*rotate;
    }

};




#endif // ENTITY_H
