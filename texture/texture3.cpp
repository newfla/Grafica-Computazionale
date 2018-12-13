#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include"texture.c"
using namespace std;
//WINDOW PARAM
    float width=700, height=700;
    float rotate[2]={0,0};
    int windowPos[2]={383,154};

//CAMERA PARAM
    double center[3]={0,0,1};
    double camera[3]={0,0,3};
    double up_vector[3]={0,1,0};
    double angle[2]={0,0};
    float plane[2]={1,50};
    float cameraFOV=45.;
    double dist=center[2]-camera[2];
    float cameraSpeed=0.1;

//VERTEX PARAM
    float v0[3] = { -1.5, -1.0, 0.0 };
    float v1[3] = { 1.5, -1.0, 0.0 };
    float v2[3] = { 1.5, 1.0, 0.0 };
    float v3[3] = { -1.5, 1.0, 0.0 };
    float t0[2] = { 0.0, 0.0 };
    float t1[2] = { 1.0, 0.0 };
    float t2[2] = { 1.0, 1.0 };
    float t3[2] = { 0.0, 1.0 };

//FISH PARAM
    
    GLsizei imageWidth, imageHeight, components;
    float anim[2]={0,1}, limit=9.5, coeff=3., speed=0.05;
    GLuint texnames[2];


GLvoid initTexture(const char* path, int pos, bool mipMap){

    glBindTexture(GL_TEXTURE_2D,texnames[pos]);
    unsigned *image=read_texture((char*)path, &imageWidth, &imageHeight, &components);

    GLsizei sWidth=256, sHeight=256;
    unsigned *sImage;
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    sImage = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );
    gluScaleImage( GL_RGBA, imageWidth, imageHeight, GL_UNSIGNED_BYTE, image,sWidth, sHeight, GL_UNSIGNED_BYTE, sImage );
    if(mipMap){
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, imageWidth,imageHeight,GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, sImage);
    
    glEnable( GL_TEXTURE_2D );
}
void moveCamera(float speed){
    float vVector[3];
    vVector[0]=center[0]-camera[0];
    vVector[1]=center[1]-camera[1];
    vVector[2]=center[2]-camera[2];

    camera[0]+=vVector[0]*speed;
    camera[2]+=vVector[2]*speed;

    center[0]+=vVector[0]*speed;
    center[2]+=vVector[2]*speed;

}


void redraw(void){
    //CLEAR
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();        

    //UPDATE WIDTH HEIGHT WINDOW
        width=glutGet(GLUT_WINDOW_WIDTH);
        height=glutGet(GLUT_WINDOW_HEIGHT);
        gluPerspective(cameraFOV,width/height,plane[0], plane[1]);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(camera[0],camera[1],
            camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]);    
        
        glScalef(anim[1],1,1);
        glTranslatef(0,0,-12);
        glRotatef(4.*sinf(anim[0]),0,0,1);
        glTranslatef(anim[0]/coeff,0,0); 
        
    glScalef(.5,.5,.5);
    glColor3f(1.,1.,1.);

    glBindTexture(GL_TEXTURE_2D,texnames[1]);
        glutSolidSphere(2,50,50);
    glutSwapBuffers();
}


void keyboardListener(unsigned char key, int x, int y){
    switch (key){
        case 'W':
        case 'w':
            moveCamera(cameraSpeed);
            break;

        case 'S':
        case 's':
            moveCamera(-cameraSpeed);
            break;
        default:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    //INIT GLUT
        glutInit(&argc,argv); 
        glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowPosition(windowPos[0],windowPos[1]);
        glutInitWindowSize(width,height);
        glutCreateWindow("Sfera");
        glutKeyboardFunc(keyboardListener);
        glutDisplayFunc(redraw);

    //LOAD IMAGINE
        glGenTextures(2,texnames);
        initTexture("texture/fish.rgba",0,true);
        initTexture("texture/fisha.rgba",1,true);

    //INIT GL
        glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glEnable(GL_DEPTH_TEST);

    //DISPLAY    
        glutMainLoop();

    return 0;
}