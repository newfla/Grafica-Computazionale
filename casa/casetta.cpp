#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include"mesh.h"
#include <math.h>
using namespace std;

//WINDOW PARAM
    float width=700, heigth=700;
    float rotate[2]={0,0};
    int windowPos[2]={383,154};
//CAMERA PARAM
    double center[3]={6.5,7.1,7.5};
    double camera[3]={6.5,7.1,2};
    double up_vector[3]={0,1,0};
    double angle[2]={0,0};
    float plane[2]={1,10};
    double dist=center[2]-camera[2];

//OUR HOUSE
    Mesh::Figure casa;

void redraw(void){
    //CLEAR
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(150,width/heigth,plane[0], plane[1]);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


    //REGOLAZIONE PUNTO DI VISTA
        glPushMatrix();
            gluLookAt(camera[0],camera[1],
            camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]);       
            casa.draw();
        glPopMatrix();
    glFlush();
}

void keyboardListener(unsigned char key, int x, int y){
    switch (key){
        case 'A':
        case 'a':
            angle[0]-=2;
            break;

        case 'S':
        case 's':
        angle[1]-=2;
            break;

        case 'D':
        case 'd':
            angle[0]+=2;
            break;

        case 'W':
        case 'w':
            angle[1]+=2;
            break;
    }
    //Rotazione intorno all'oggetto;
    camera[0]=center[0]+(dist*cos(angle[0]*((double)M_PI/180.0)));
    camera[2]=center[2]+(dist*sin(angle[0]*((double)M_PI/180.0)));

    //Guardare dall'alto e dal basso l'oggetto entro i 60gradi
    if(angle[1]<-60.0)
        angle[1]=-60.0;
    else if(angle[1]>60.0)
        angle[1]=60;
    if(angle[1]!=0)
        camera[1]=center[1]+(dist*sin(angle[1]*((double)M_PI/180.0)));

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