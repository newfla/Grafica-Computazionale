#include "ShaderUtility.h"

ShaderUtility::Shader::Shader(std::string vertexPath, std::string fragmentPath){
    
    //VAR DECLARATION
        unsigned int vertex, fragment;
        std::string vertexCode, fragmentCode; 


    //LOAD SHADER CODE
        vertexCode=loadFileCode(vertexPath);
        fragmentCode=loadFileCode(fragmentPath);

    
    //COMPILE CODE
        vertex=compileShaderCode(vertexCode,GL_VERTEX_SHADER);
        fragment=compileShaderCode(fragmentCode,GL_FRAGMENT_SHADER);


    //LINK SHADER PROGRAM
        id=linkShaderProgram(vertex,fragment);


    //CLEAN-UP
        glDeleteShader(vertex);
        glDeleteShader(fragment);
}


std::string  ShaderUtility::Shader::loadFileCode(std::string pathFile){
    std:: string output;
    std::ifstream shaderFile;

    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try{
        shaderFile.open(pathFile);
        std::stringstream stream;
        stream<<shaderFile.rdbuf();
        shaderFile.close();
        output=stream.str();
    }
    catch(std::ifstream::failure e){
         std::cout << "ERROR::SHADER::FILE: "<< pathFile<<" NOT_SUCCESFULLY_READ" << std::endl;
    }

    return output;
}


unsigned int ShaderUtility::Shader::compileShaderCode(std::string code, GLenum type){

    //VAR DECLARATION
        char infoLog[512];
        unsigned int output;
        int success;
        const char *cStr;

    
    //COMPILE SHADER
        output=glCreateShader(type);
        cStr=code.c_str();
        glShaderSource(output,1,&cStr ,NULL);
        glCompileShader(output);

    
    //CHECK COMPILE ERRORS
        glGetShaderiv(output, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(output, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

    return output;    
}


unsigned int ShaderUtility::Shader::linkShaderProgram(unsigned int vertex,unsigned int fragment){
    
    //VAR DECLARATION
        unsigned int output;
        int success;
        char infoLog[512];

    //LINK AND BUILD SHADER PROGRAM
        output=glCreateProgram();
        glAttachShader(output,vertex);
        glAttachShader(output,fragment);
        glLinkProgram(output);


    //CHECK LINKING ERRORS
        glGetProgramiv(output, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(output, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }


    return output;
}


void ShaderUtility::Shader::use(){ 
    glUseProgram(id);
} 


void ShaderUtility::Shader::setBool(const std::string name, bool value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); 
}  


void ShaderUtility::Shader::setInt(const std::string name, int value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
}  


void ShaderUtility::Shader::setFloat(const std::string name, float value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
}