#define _USE_MATH_DEFINES
#include<iostream>
#include "../utility/mesh.h"
#include <math.h>
using namespace std;
using namespace Mesh;

//WINDOW PARAM
    float width=700, heigth=700;
    float rotate[2]={0,0};
    int windowPos[2]={383,154};
//CAMERA PARAM
    double center[3]={0,0,0};
    double camera[3]={0,4.5,5};
    double up_vector[3]={0,1,0};
    double angle[2]={0,60};
    float plane[2]={1,20};
    double dist=center[2]-camera[2];

//FIGURE array;
    GluSolidFigure *cilindro, *sfera, *disco, *partDisco;
void redraw(void){
    //CLEAR
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90,width/heigth,plane[0], plane[1]);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


    //REGOLAZIONE PUNTO DI VISTA
        glPushMatrix();
            gluLookAt(camera[0],camera[1],
            camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]); 
            glPushMatrix();
                glTranslatef(-2,1,0);
                glRotatef(270,1,0,0);
                cilindro->drawCylinder(0.5,0.25,0.75,10,10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-2,-3,0);
                sfera->drawSphere(0.5,10,10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(2,-3,0);
                glRotatef(270,1,0,0);
                disco->drawDisk(0.5,1,100,10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(2,1,0);
                glRotatef(270,1,0,0);
                partDisco->drawPartialDisk(0.5,1,100,10,20,60);
            glPopMatrix();
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
        angle[1]+=2;
            break;

        case 'D':
        case 'd':
            angle[0]+=2;
            break;

        case 'W':
        case 'w':
            angle[1]-=2;
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
        glutCreateWindow("Figure_Test");
        glutKeyboardFunc(keyboardListener);
        glutDisplayFunc(redraw);
    
    //GL INIT
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

    //FIGURES INIT
        cilindro=new GluSolidFigure(GL_FILL, GLU_OUTSIDE, GLU_SMOOTH);
        sfera=new GluSolidFigure(GL_FILL, GLU_OUTSIDE, GLU_SMOOTH);
        disco=new GluSolidFigure(GL_FILL, GLU_OUTSIDE, GLU_SMOOTH);
        partDisco=new GluSolidFigure(GL_FILL, GLU_OUTSIDE, GLU_SMOOTH);

    //DISPLAY    
        glutMainLoop();

    return 0;
}