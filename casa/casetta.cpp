#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include"mesh.h"

//WINDOW PARAM
float width=600, heigth=600;
float rotate[2]={0,0};
int windowPos[2]={383,154};
double lookParam[3]={0.1,0.15,-0.4};
Mesh::House casa;

void redraw(void){
    //CLEAR
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
    //REGOLAZIONE PUNTO DI VISTA
        glPushMatrix();
            gluLookAt(0,0,10,lookParam[0],lookParam[1],lookParam[2],0,1,0);    
            casa.draw();
        glPopMatrix();
    glFlush();
}

void keyboardListener(unsigned char key, int x, int y){
    switch (key){
    }
   // glutPostRedisplay();
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
        glEnable(GL_DEPTH_TEST| GL_LIGHTING | GL_LIGHT0);
        glShadeModel(GL_FLAT);

    //DISPLAY    
        glutMainLoop();

    return 0;
}