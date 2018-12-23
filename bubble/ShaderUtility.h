#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H
#include<glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

namespace ShaderUtility{
    class Shader;
};

class ShaderUtility::Shader{
    public:
        Shader(std::string vertexPath, std::string fragmentPath);
        void use();
        void setBool(const std::string name, bool value) const;  
        void setInt(const std::string name, int value) const;   
        void setFloat(const std::string name, float value) const;

    private:
        unsigned int id;
        std::string loadFileCode(std::string pathFile);
        unsigned int compileShaderCode(std::string code, GLenum type);
        unsigned int linkShaderProgram(unsigned int vertex,unsigned int fragment);
};

  
#endif