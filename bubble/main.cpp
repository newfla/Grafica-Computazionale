#if defined(_WIN32)
    #define path "bubble/shader/windows/"
#elif defined(__linux__)
    #define path "bubble/shader/linux/"
#endif

#include "ShaderUtility.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <random>

//VAR
    ShaderUtility::Shader *shaderSkybox, *shaderSphere;
    ShaderUtility::GlutListener *cameraListener;
    ShaderUtility::Utility3D *utility3D;
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<float> dist(0,1);
    std::vector<glm::vec3>positions;
    int max=500;


//TEXTURE PATH
    std::vector<std::string> getUrls(){
        return std::vector<std::string>{
            "bubble/texture/posx.jpg",
            "bubble/texture/negx.jpg",
            "bubble/texture/posy.jpg",
            "bubble/texture/negy.jpg",
            "bubble/texture/posz.jpg",
            "bubble/texture/negz.jpg",
        };
    }


//KEYBOARD-CAMERA LISTENER
    void keyboardListener(unsigned char key, int x, int y){
        cameraListener->keyboardListener(key,x,y);
        glutPostRedisplay();
    }


//MOUSE-CAMERA LISTENER
void mouseListener(int x, int y){
    cameraListener->mouseListener(x,y);
    glutPostRedisplay();
}


//SET INITIAL BUBBLES POSITION
    void buildStartPositions(){
        for(int i = 0; i < max; i++){
            glm::vec3 position;
            position.x = dist(engine)* 100 - 50;
		    position.y = dist(engine)* 100 - 50;
		    position.z = dist(engine)* 100 - 50;
            positions.push_back(position);
        }
    }


//ANIMATE BUBBLES
    void animation(){
    utility3D->updateTransVector();
    glutPostRedisplay();
}


//GLUT REDRAW CALLABCK
    void display(){

        //CLEAR
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //PERSPECTIVE SETUP
            float ratio=glutGet(GLUT_WINDOW_WIDTH)/glutGet(GLUT_WINDOW_HEIGHT);
            glm::mat4 projection=glm::perspective(glm::radians(45.f),ratio,0.1f,100.0f);
            glm::mat4 view=utility3D->getView(cameraListener);

        
        //DRAW BUBBLES            
            for(int i = 0; i < max; i++){
            
                shaderSphere->use();

                glm::mat4 model=glm::mat4(1.f);
                glm::vec3 animate=utility3D->getTransVector();

                model=glm::translate(model,positions[i]);
                model=glm::translate(model,animate);
                

                utility3D->setModelMatrix(shaderSphere,model);
                utility3D->setViewMatrix(shaderSphere,view);
                utility3D->setProjectionMatrix(shaderSphere,projection);
                utility3D->setCameraVector(shaderSphere,cameraListener);

                utility3D->bindSphere();
            }
            

        //DRAW SKYBOX
            glDepthFunc(GL_LEQUAL);
            shaderSkybox->use();
            view=glm::mat4(glm::mat3(view));

            utility3D->setViewMatrix(shaderSkybox,view);
            utility3D->setProjectionMatrix(shaderSkybox,projection);

            utility3D->bindSkyBox();

            glDepthFunc(GL_LESS);

        glFlush();

    }

    

    int main(int argc, char** argv) {

        //GLUT INIT
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_RGBA| GLUT_DEPTH);
            glutInitWindowPosition(460,20);
            glutInitWindowSize(1000,1000);
            glutCreateWindow("Soap_Bubble_Shading");
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
            glutKeyboardFunc(keyboardListener);
            glutPassiveMotionFunc(mouseListener);
            glutDisplayFunc(display);


        //GLAD INIT
            if (!gladLoadGL()){
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }


        //GL INIT
            glEnable(GL_DEPTH_TEST);


        //CAMERA LISTENER INIT
            cameraListener=new ShaderUtility::GlutListener();


        //SKYBOX SHADER INIT
            std:: stringstream ss, ss1;
            ss<<path<<"/skybox/vertex.glsl";
            ss1<<path<<"/skybox/fragment.glsl";
            shaderSkybox=new ShaderUtility::Shader(ss.str(),ss1.str());


        //SPHERE SHADER INIT
            std:: stringstream ss2, ss3;
            ss2<<path<<"/sphere/vertex.glsl";
            ss3<<path<<"/sphere/fragment.glsl";
            shaderSphere=new ShaderUtility::Shader(ss2.str(),ss3.str());
        

        //3D UTILITY INIT
            utility3D=new ShaderUtility::Utility3D();


        //LOAD CUBEMAP TEXTURE
            utility3D->loadTextureCubeMap(getUrls());

        
        //INIT SKYBOX CUBE
            utility3D->initCubeSkyBox();
            shaderSkybox->use();
            shaderSkybox->setInt("skybox", 0);


        //INIT SPHERE
            utility3D->initSphere();
            shaderSphere->use();
            shaderSphere->setInt("skybox",0);
            buildStartPositions();

        //TIMER FUNCTION MOVEMNT BUBBLE;
            glutIdleFunc(animation);


        //MAIN LOOP
            glutMainLoop();
}