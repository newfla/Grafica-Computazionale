#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H
#define  _USE_MATH_DEFINES 
#include<glad/glad.h>
#include <GL/glut.h>
#include"SOIL/SOIL.h"
#include <glm/ext.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include<vector>
#include <cmath>

namespace ShaderUtility{
    class Shader;
    class GlutListener;
    class Utility3D;
};

class ShaderUtility::Shader{
    public:
        Shader(std::string vertexPath, std::string fragmentPath);
        void use();
        void setBool(const std::string name, bool value) const;  
        void setInt(const std::string name, int value) const;   
        void setFloat(const std::string name, float value) const;
        void setVec3(const std::string name,glm::vec3 value)const;
        void setMat4(const std::string name,glm::mat4 value)const;

    private:
        unsigned int id;
        std::string loadFileCode(std::string pathFile);
        unsigned int compileShaderCode(std::string code, GLenum type);
        unsigned int linkShaderProgram(unsigned int vertex,unsigned int fragment);
};

class ShaderUtility::GlutListener{
    public:
        void keyboardListener(unsigned char key, int x, int y);
        void mouseListener(int x, int y);
        glm::vec3 getCamera();
        glm::vec3 getFocus();
    private:
        glm::vec3 focus=glm::vec3(0.,0.,3.);
        glm::vec3 camera=glm::vec3(0.,0.,12.);
        float cameraSpeed=0.04;

        void rotateView(float speed);
        void moveCamera(float speed);

};

class ShaderUtility::Utility3D{
    public:
        void loadTextureCubeMap(std::vector<std::string> urls);
        void initCubeSkyBox();
        void initSphere();
        void bindSkyBox();
        void bindSphere();
        void setModelMatrix(Shader* shader, glm::mat4 model);
        void setViewMatrix(Shader* shader, glm::mat4 view);
        void setProjectionMatrix(Shader* shader, glm::mat4 proj);
        void setCameraVector(Shader* shader, GlutListener* camera);
        glm::mat4 getView(GlutListener* camera);
        glm::vec3 getTransVector();
        void updateTransVector();

    private:
        glm::vec3 upVector=glm::vec3(0.,1.,0.);
        glm::vec4 perspective=glm::vec4(90,1,1,25);
        glm::vec2 anim=glm::vec2(0.,1.);
        unsigned int cubeMapTextureID, skyboxVAO, skyboxVBO, sphereVAO, sphereVBO;
        std::vector<short> sphereIndices;

        std::vector<float> buildSkyBoxVertices();
        std::vector<float>  buildSphereVerticesNormalsIndices(float radius, int rings, int sectors);

        
};

  
#endif