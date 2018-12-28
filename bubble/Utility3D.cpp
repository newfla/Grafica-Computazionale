#include"ShaderUtility.h"


glm::mat4 ShaderUtility::Utility3D::getView(ShaderUtility::GlutListener* camera){
    return glm::lookAt(camera->getCamera(),camera->getFocus(),upVector);
}


void ShaderUtility::Utility3D::loadTextureCubeMap(std::vector<std::string> urls){

    //VAR DECLARATION
        int width, height, nrChannels;


    //BIND OPENGL TEXTURE ID
        glGenTextures(1,&cubeMapTextureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);


    //LOAD AND STORE TEXTURE
        for (unsigned int i = 0; i < urls.size(); i++){

            unsigned char *image=image=SOIL_load_image(urls[i].c_str(),&width,&height,&nrChannels,SOIL_LOAD_RGB);
            
            if(image)
                 glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            else
                std::cout << "Cubemap texture failed to load at path: " << urls[i] << std::endl;

            SOIL_free_image_data(image);
        }

    //AUTO GEN TEXTURE MAPM_PING
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);   
}


void ShaderUtility::Utility3D::initCubeSkyBox(){

    //BUILD CUBE SKYBOX VERTICES
        std::vector<float> skyboxVertices=buildSkyBoxVertices();
    

    //SETUP VBO VBA
        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*skyboxVertices.size(), &skyboxVertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

}


void ShaderUtility::Utility3D::initSphere(){
    //BUILD
        std::vector<float> sphereVertices=buildSphereVerticesNormalsIndices(1,32,16);

    //SETUP VBO VBA
        glGenVertexArrays(1, &sphereVAO);
        glGenBuffers(1, &sphereVBO);
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sphereVertices.size(), &sphereVertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}


std::vector<float> ShaderUtility::Utility3D::buildSkyBoxVertices(){
    return std::vector<float>{
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

}


std::vector<float> ShaderUtility::Utility3D::buildSphereVerticesNormalsIndices(float radius, int rings, int sectors){
    //VAR DECLARATION
        std::vector<float> sphereVertices;
        float const R = 1./(float)(rings-1);
        float const S = 1./(float)(sectors-1);


    //MAX VECTORS SIZE (PERFORMANCE TIP)
        sphereVertices.resize(2*rings * sectors * 3);
        sphereIndices.resize(rings * sectors * 4);


    //ITRERATORS
        std::vector<float>::iterator v = sphereVertices.begin();
        std::vector<short>::iterator i = sphereIndices.begin();


    //VERTICES AND NORMALS
        for(int r = 0; r < rings; r++){

            for(int s  = 0; s < sectors; s++) {

                float const y = sin( -M_PI_2 + M_PI * r * R );
                float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
                float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );


                *v++ = x * radius;
                *v++ = y * radius;
                *v++ = z * radius;

                *v++ = x;
                *v++ = y;
                *v++ = z;
            }
        }


    //INDICES        
        for(int r = 0; r < rings; r++){

            for(int s = 0; s < sectors; s++) {

                *i++ = r * sectors + s;
                *i++ = r * sectors + (s+1);
                *i++ = (r+1) * sectors + (s+1);
                *i++ = (r+1) * sectors + s;
            }
        }

    return sphereVertices;
}


void ShaderUtility::Utility3D::bindSkyBox(){
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


void ShaderUtility::Utility3D::bindSphere(){
    glBindVertexArray(sphereVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);
    glDrawElements(GL_QUADS, sphereIndices.size(), GL_UNSIGNED_SHORT, &sphereIndices[0]);
    glBindVertexArray(0);
}


void ShaderUtility::Utility3D::setModelMatrix(Shader* shader, glm::mat4 model){
    shader->setMat4("model",model);
}


void ShaderUtility::Utility3D::setViewMatrix(Shader* shader, glm::mat4 view){
    shader->setMat4("view",view);
}


void ShaderUtility::Utility3D::setProjectionMatrix(Shader* shader, glm::mat4 proj){
    shader->setMat4("proj",proj);
}


void ShaderUtility::Utility3D::setCameraVector(Shader* shader,ShaderUtility::GlutListener* camera){
    shader->setVec3("cameraPos",camera->getCamera());
}


glm::vec3 ShaderUtility::Utility3D::getTransVector(){
    return glm::vec3(sinf(anim.x)/2.,anim.x,0.f);
}


void ShaderUtility::Utility3D::updateTransVector(){
    glm::vec3 trans=glm::vec3(0.);
    if(anim.x>7.){
       // anim.y*=-1;
       anim.x=-7.f;
       return;
    }
    else if(anim.x<-7.f)
        anim.y*=-1;
    anim.x+=0.008*anim.y;
}