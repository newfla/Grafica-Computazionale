#include"ShaderUtility.h"
void ShaderUtility::GlutListener::keyboardListener(unsigned char key, int x, int y){
    switch (key){
        case 'A':
        case 'a':
            rotateView(-cameraSpeed);
            break;

        case 'S':
        case 's':
            moveCamera(-cameraSpeed);
            break;

        case 'D':
        case 'd':
            rotateView(cameraSpeed);
            break;

        case 'W':
        case 'w':
            moveCamera(cameraSpeed);
            break;

        case 27:
            exit(0);
    }
}


void ShaderUtility::GlutListener::mouseListener(int x, int y){
    int midX=glutGet(GLUT_WINDOW_WIDTH)/2, midY=glutGet(GLUT_WINDOW_HEIGHT)/2;
    if(x==midX && y==midY) return;
    glutWarpPointer(midX,midY);
    float angleY = (float)( (midX - x) ) / 1000.;		
	float angleZ = (float)( (midY - y) ) / 1000.;
    focus[1]+=angleZ*2;

    if((focus[1] - camera[1]) > 8)  focus[1]= camera[1] + 8.;
	if((focus[1] - camera[1]) <-8)  focus[1]= camera[1] - 8.;
	
	rotateView(-angleY);

}


glm::vec3 ShaderUtility::GlutListener::getCamera(){
    return camera;
}

glm::vec3 ShaderUtility::GlutListener::getFocus(){
    return focus;
}



void ShaderUtility::GlutListener::rotateView(float speed){
    glm::vec3 vVector=glm::vec3(0.);
    vVector=focus-camera;
    focus[2] = (float)(camera[2] + sin(speed)*vVector[0] + cos(speed)*vVector[2]);
	focus[0] = (float)(camera[0] + cos(speed)*vVector[0] - sin(speed)*vVector[2]);
}

void ShaderUtility::GlutListener::moveCamera(float speed){
    glm::vec3 vVector=glm::vec3(0.);
    vVector=focus-camera;

    camera[0]+=vVector[0]*speed;
    camera[2]+=vVector[2]*speed;

    focus[0]+=vVector[0]*speed;
    focus[2]+=vVector[2]*speed;

}