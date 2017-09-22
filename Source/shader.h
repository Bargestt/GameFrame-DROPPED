#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.h>


class Shader
{
private:
    GLuint uniform_model;
    GLuint uniform_view;
    GLuint uniform_projection;
    GLuint uniform_ProjectionView;
public:
     unsigned int _ID;
     Shader();
    Shader(const char *vertexPath, const char *fragmentPath, bool filePath = true);
    void load(const char *vertexPath, const char *fragmentPath, bool filePath = true);

    void use() const;

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value1) const;
    void setInt(const std::string &name, int value1, int value2) const;
    void setInt(const std::string &name, int value1, int value2, int value3) const;
    void setInt(const std::string &name, int value1, int value2, int value3, int value4) const;
    void setFloat(const std::string &name, float value1) const;
    void setFloat(const std::string &name, float value1, float value2) const;
    void setFloat(const std::string &name, float value1, float value2, float value3) const;
    void setFloat(const std::string &name, float value1, float value2, float value3, float value4) const;

    void setMatrix(const std::string &name, int size, const float *matrix);

    void setVec(const std::string &name, float x, float y) const;
    void setVec(const std::string &name, float x, float y,float z) const;
    void setVec(const std::string &name, float x, float y, float z,float w) const;

    void setVec(const std::string &name, const glm::vec3 &value) const;
    void setVec(const std::string &name, const glm::vec4 &value) const;


    void setModel(const glm::mat4& model) const;
    void setView(const glm::mat4& view) const;
    void setProjection(const glm::mat4& projection) const;
    void setProjectionView(const glm::mat4& projectionView) const;

};



#endif // SHADER_H
