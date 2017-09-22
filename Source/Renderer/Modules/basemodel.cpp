#include "basemodel.h"


BaseModel::BaseModel(const Mesh &data)
{
    addData(data);
}
BaseModel::~BaseModel()
{
    deleteData();
}

BaseModel::BaseModel(BaseModel &&other) :
    VAO                     (other.VAO),
    vbo_count          (other.vbo_count),
    indices_count    (other.indices_count),    
    buffers                (std::move(other.buffers))
{
    other.VAO = 0;
    other.vbo_count =0;
    other.indices_count = 0;

}

BaseModel &BaseModel::operator =(BaseModel &&other)
{
    VAO = other.VAO;
    vbo_count = other.vbo_count;
    indices_count = other.indices_count;    
    buffers = std::move(other.buffers);

    other.VAO = 0;
    other.vbo_count =0;
    other.indices_count = 0;

    return *this;
}

void BaseModel::addData(const Mesh &data)
{
    genVAO();

    addVBO(3,data.verticesPos);
    if(data.textureCoords.size() >0)
        addVBO(2,data.textureCoords);
    if(data.indices.size() >0)
        addEBO(data.indices);
    if( data.normals.size() > 0 )
        addVBO( 3, data.normals );
}


void BaseModel::deleteData()
{
    glDeleteVertexArrays(1,&VAO);

    glDeleteBuffers(buffers.size(), buffers.data());
    buffers.clear();

    vbo_count =0;
    indices_count =0;
    VAO =0;
}

void BaseModel::changeVBO(int buffer_number, std::vector<GLfloat> data)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer_number]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*data.size(), data.data() );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseModel::changeEBO(int buffer_number, std::vector<GLuint> data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[buffer_number]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLfloat)*data.size(), data.data() );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    indices_count = data.size();
}



void BaseModel::bindVAO() const
{
    glBindVertexArray(VAO);
}

int BaseModel::getIndecesCount() const
{
    return indices_count;
}



int BaseModel::addVBO(int dimesions,const std::vector<GLfloat>& data, GLenum drawType)
{
    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.size(), data.data(),drawType);

    glVertexAttribPointer( vbo_count, dimesions, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0 );
    glEnableVertexAttribArray( vbo_count++ );

    buffers.push_back(VBO);
    return buffers.size() - 1;
}
int BaseModel::addEBO(const std::vector<GLuint> &data, GLenum drawType)
{
    GLuint EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*data.size(), data.data(), drawType);

    indices_count = data.size();
    buffers.push_back(EBO);
    return buffers.size()-1;
}
void BaseModel::genVAO()
{
    if(VAO != 0)
        deleteData();
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
}
