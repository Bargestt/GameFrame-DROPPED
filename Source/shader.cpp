#include "shader.h"



Shader::Shader()
{

}

Shader::Shader(const char* vertexPath, const char* fragmentPath, bool filePath)
{
    load(vertexPath, fragmentPath, filePath);
}

void Shader::load(const char *vertexPath, const char *fragmentPath, bool filePath)
{
    std::string svertexCode, sfragmentCode;

    const char *vertexCode;
    const char *fragmentCode;

    if(filePath)
    {
        std::ifstream vertexFile, fragmentFile;
        vertexFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
        fragmentFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
        try
        {
            vertexFile.open(vertexPath,std::ios_base::in);
            fragmentFile.open(fragmentPath,std::ios_base::in);

            std::stringstream vertexStream, fragmentStream;

            vertexStream << vertexFile.rdbuf();
            fragmentStream << fragmentFile.rdbuf();

            vertexFile.close();
            fragmentFile.close();

            svertexCode   = vertexStream.str();
            sfragmentCode = fragmentStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

    }
    else
    {
        svertexCode = vertexPath;
        sfragmentCode = fragmentPath;
    }
    vertexCode = svertexCode.c_str();
    fragmentCode = sfragmentCode.c_str();

    //shader compilation
    int  success;
    char infoLog[512];

    unsigned int vertexShader;
    unsigned int fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);

    //проверка успешной компиляции шейдера
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    // fragment shader----------------------
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //shader programm ---------------------------------------------
    _ID = glCreateProgram();

    glAttachShader(_ID, vertexShader);
    glAttachShader(_ID, fragmentShader);
    glLinkProgram(_ID);

    glGetProgramiv(_ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAMM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(_ID);
    uniform_model = glGetUniformLocation(_ID, "model");
    uniform_view =  glGetUniformLocation(_ID, "view");
    uniform_projection = glGetUniformLocation(_ID, "projection");
    uniform_ProjectionView = glGetUniformLocation(_ID, "projectionview");

}

void Shader::use() const
{
    glUseProgram(_ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
     glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value1) const{
    glUniform1i(glGetUniformLocation(_ID, name.c_str()), value1);
}
void Shader::setInt(const std::string &name, int value1, int value2) const{
    glUniform2i(glGetUniformLocation(_ID, name.c_str()), value1, value2);
}
void Shader::setInt(const std::string &name, int value1, int value2, int value3) const{
    glUniform3i(glGetUniformLocation(_ID, name.c_str()), value1, value2, value3);
}
void Shader::setInt(const std::string &name, int value1, int value2, int value3, int value4) const{
    glUniform4i(glGetUniformLocation(_ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setFloat(const std::string &name, float value1) const{
    glUniform1f(glGetUniformLocation(_ID, name.c_str()), value1);
}
void Shader::setFloat(const std::string &name, float value1, float value2) const{
    glUniform2f(glGetUniformLocation(_ID, name.c_str()), value1, value2);
}
void Shader::setFloat(const std::string &name, float value1, float value2, float value3) const{
    glUniform3f(glGetUniformLocation(_ID, name.c_str()), value1, value2, value3);
}
void Shader::setFloat(const std::string &name, float value1, float value2, float value3, float value4) const{
    glUniform4f(glGetUniformLocation(_ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setMatrix(const std::string &name,int size, const float *matrix){
    if(size ==2)
        glUniformMatrix2fv(glGetUniformLocation(_ID, name.c_str()),1,GL_FALSE,matrix);
    else if(size ==3)
        glUniformMatrix3fv(glGetUniformLocation(_ID, name.c_str()),1,GL_FALSE,matrix);
    else if(size == 4)
        glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()),1,GL_FALSE,matrix);
}
void Shader::setVec(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(_ID, name.c_str()), x, y);
}

void Shader::setVec(const std::string &name, float x, float y,float z) const
{
    glUniform3f(glGetUniformLocation(_ID, name.c_str()), x, y, z);
}

void Shader::setVec(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(_ID, name.c_str()), x, y, z, w);
}

void Shader::setVec(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}


void Shader::setVec(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}

void Shader::setModel(const glm::mat4 &model) const
{
    glUniformMatrix4fv(uniform_model,1,GL_FALSE,glm::value_ptr(model));
}

void Shader::setView(const glm::mat4 &view) const
{
    glUniformMatrix4fv(uniform_view,1,GL_FALSE,glm::value_ptr(view));
}

void Shader::setProjection(const glm::mat4 &projection) const
{
    glUniformMatrix4fv(uniform_projection,1,GL_FALSE,glm::value_ptr(projection));
}

void Shader::setProjectionView(const glm::mat4 &projectionView) const
{
    glUniformMatrix4fv(uniform_ProjectionView,1,GL_FALSE,glm::value_ptr(projectionView));
}


