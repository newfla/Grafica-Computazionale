#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include"mesh.h"
#include <math.h>
//WINDOW PARAM
float width=600, heigth=600;
float rotate[2]={0,0};
int windowPos[2]={383,154};
double lookParam[6]={0,1,-1,+0.1,0.15,0.4};
double distance=lookParam[2]-lookParam[5];
int degree[2]={0,0};
Mesh::Figure casa;

void redraw(void){
    //CLEAR
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
      // glOrtho(-1,1,-1,1,1,50);
        gluPerspective(90,1,0.1, 4);
    //REGOLAZIONE PUNTO DI VISTA
        double sinRot, cosRot;
        sinRot=sin((double)degree[0]* M_PI/180.0);
        cosRot=cos((double)degree[0]*M_PI/180.0);
        glPushMatrix();
            gluLookAt(lookParam[0]+(cosRot*distance),lookParam[1],lookParam[2]+(sinRot*distance),lookParam[3],lookParam[4],lookParam[5],0,1,0);    
            casa.draw();
        glPopMatrix();
    glFlush();
}

void keyboardListener(unsigned char key, int x, int y){
    switch (key){
        case 'A':
        case 'a':
            degree[0]=((int)degree[0]-5)%360;
            break;

        case 'S':
        case 's':
            lookParam[1]+=0.1;
            break;

        case 'D':
        case 'd':
            degree[0]=((int)degree[0]+5)%360;
            break;

        case 'W':
        case 'w':
            lookParam[1]-=0.1;
            break;
    }
   glutPostRedisplay();
}

void mouseListener(int button, int state, int x, int y){
     //   glutPostRedisplay();
    }

int main(int argc, char* argv[]){
    //INIT GLUT
        glutInit(&argc,argv); 
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH);
        glutInitWindowPosition(windowPos[0],windowPos[1]);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Casetta_Mesh");
        glutKeyboardFunc(keyboardListener);
        glutMouseFunc(mouseListener);
        glutDisplayFunc(redraw);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING | GL_LIGHT0 );
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glShadeModel(GL_FLAT);
        

    //DISPLAY    
        glutMainLoop();

    return 0;
}