#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <glheader.h>

#include<vector>
#include <array>

#include <ResourceManager/textureatlas.h>

//#include <util/non_copyable.h>

//Содержит информацию о буферах,
//загружает, рубактирует, биндит буферы


struct Mesh{
    std::vector<GLfloat> verticesPos;
    std::vector<GLuint> indices;
    std::vector<GLfloat> textureCoords;
    std::vector<GLfloat> normals;

    Mesh(){}
    virtual ~Mesh()
    {
        verticesPos.clear();
        verticesPos.shrink_to_fit();
        indices.clear();
        indices.shrink_to_fit();
        textureCoords.clear();
        textureCoords.shrink_to_fit();
        normals.clear();
        normals.shrink_to_fit();
    }

    Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& ind,
              const std::vector<GLfloat>& texCoords, const std::vector<GLfloat>& norms ) :
        verticesPos(vertices), indices(ind), textureCoords(texCoords), normals(norms)
    { }
    Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& ind,
              const std::vector<GLfloat>& texCoords ) :
        verticesPos(vertices), indices(ind), textureCoords(texCoords)
    { }

    virtual Mesh* clone() const
    {
        return new Mesh(*this);
    }
    virtual Mesh& setTexCoords(const TextureAtlas& atlas, int x, int y)
    {
        textureCoords = atlas.getTexture(x,y);
        return *this;
    }

    virtual Mesh& calculateNormals()    { return *this;  }

};


class BaseModel
{
    GLuint VAO;
    unsigned int vbo_count =0;
    unsigned int indices_count =0;    

    std::vector<GLuint> buffers;

public:
    BaseModel() = default;
    BaseModel(const Mesh& data);
    ~BaseModel();

    BaseModel(BaseModel&& other);
    BaseModel& operator =(BaseModel&& other);


    void addData(const Mesh& data);
    void deleteData();

    void changeVBO(int buffer_number, std::vector<GLfloat> data);
    void changeEBO(int buffer_number, std::vector<GLuint> data);

    void bindVAO() const;
    int getIndecesCount() const;


    int addVBO(int dimesions, const std::vector<GLfloat> &data, GLenum drawType = GL_STATIC_DRAW);
    int addEBO(const std::vector<GLuint>& data, GLenum drawType = GL_STATIC_DRAW);
    void genVAO();
};

#endif // BASEMODEL_H
