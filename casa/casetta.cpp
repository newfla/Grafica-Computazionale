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
//CAMERA PARAM
    double camera[3]={0.25,0.35,1};
  //  double direction[3]={0,0,0};
    double center[3]={0.25,0.35,0.5};
    double up_vector[3]={0,1,0};
    float angle[2]={0,0};
    int plane[2]={1,4};

//OUR HOUSE
Mesh::Figure casa;

void redraw(void){
    //CLEAR
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        gluPerspective(120,width/heigth,plane[0], plane[1]);

    //REGOLAZIONE PUNTO DI VISTA
        glPushMatrix();
            gluLookAt(camera[0],camera[1],camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]);       
            casa.draw();
        glPopMatrix();
    glFlush();
}

void keyboardListener(unsigned char key, int x, int y){
    switch (key){
        case 'A':
        case 'a':
            angle[0]-=0.1;
            break;

        case 'S':
        case 's':
        angle[1]-=2;
            break;

        case 'D':
        case 'd':
            angle[0]+=0.1;
            break;

        case 'W':
        case 'w':
            angle[1]+=2;
            break;
    }
    //Rotazione intorno all'oggetto con y fermo;
    int dist=plane[1]-plane[0];
    camera[0]=dist*cos(angle[0]);
    camera[2]=dist*sin(angle[0]);
    if(angle[1]>60)
        angle[1]=60;
    else if(angle[1]<-60)
        angle[1]=-60;
    camera[1]=dist*cos(angle[1]*M_PI/180);
    std::cout<<angle[1]<<std::endl;
    //direction[0]=-cos(angle[0]);
    //direction[1]=-sin(angle[0]);

    glutPostRedisplay();
}
int main(int argc, char* argv[]){
    //INIT GLUT
        glutInit(&argc,argv); 
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH);
        glutInitWindowPosition(windowPos[0],windowPos[1]);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Casetta_Mesh");
        glutKeyboardFunc(keyboardListener);
        glutDisplayFunc(redraw);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glShadeModel(GL_FLAT);
        

    //DISPLAY    
        glutMainLoop();

    return 0;
}