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
    unsigned *image;
    GLsizei imageWidth, imageHeight, components;
    float anim[2]={0,1}, limit=9.5, coeff=3., speed=0.05;


GLvoid initTexture(const char* path){

    image=read_texture((char*)path, &imageWidth, &imageHeight, &components);

    GLsizei sWidth=256, sHeight=256;
    unsigned *sImage;
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    sImage = (unsigned *)malloc( sWidth*sHeight*4*sizeof( unsigned ) );
    gluScaleImage( GL_RGBA, imageWidth, imageHeight, GL_UNSIGNED_BYTE, image,sWidth, sHeight, GL_UNSIGNED_BYTE, sImage );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, sImage);
    glEnable( GL_TEXTURE_2D );
}

    void idleFunc(){
        if(anim[0]>limit*coeff){
            anim[1]*=-1.;
            anim[0]*=-1;
        }else if(anim[1]<0 && anim[0]>-0.5){
            cout<<"aa";
            anim[1]*=-1;
            anim[0]*=-1;
        }
        anim[0]+=(speed);
       // cout<<anim[0]<<endl<<"-----------------"<<endl;
        glutPostRedisplay();
    }


void redraw(void){
    //CLEAR
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();        

    //UPDATE WIDTH HEIGHT WINDOW
        width=glutGet(GLUT_WINDOW_WIDTH);
        height=glutGet(GLUT_WINDOW_HEIGHT);
        gluPerspective(cameraFOV,width/height,plane[0], plane[1]);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glScalef(anim[1],1,1);
        glTranslatef(-anim[1]*limit/2.,0,-12);
        glRotatef(4.*sinf(anim[0]),0,0,1);
        glTranslatef(anim[0]/coeff,0,(coeff/2.)*sinf(anim[0])); 
        
    glScalef(.5,.5,.5);
    glColor3f(1.,1.,1.);

        glBegin(GL_QUADS);
            glTexCoord2fv(t0); glVertex3fv(v0);
            glTexCoord2fv(t1); glVertex3fv(v1);
            glTexCoord2fv(t2); glVertex3fv(v2);
            glTexCoord2fv(t3); glVertex3fv(v3);
        glEnd();
    glutSwapBuffers();
}


void keyboardListener(unsigned char key, int x, int y){
    switch (key){
        default:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    //INIT GLUT
        glutInit(&argc,argv); 
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
        glutInitWindowPosition(windowPos[0],windowPos[1]);
        glutInitWindowSize(width,height);
        glutCreateWindow("Pesciolino");
        glutKeyboardFunc(keyboardListener);
        glutIdleFunc(idleFunc);
        glutDisplayFunc(redraw);

    //LOAD IMAGINE
        initTexture("texture/fish.rgba");


    //DISPLAY    
        glutMainLoop();

    return 0;
}