#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include<vector>
#include <math.h>
#include "../utility/mesh.h"
using namespace Mesh;
using namespace std;

//WINDOW PARAM
    float width=700, heigth=700;

//BEZIER CURVE
    NurbsSurface* surface;

//CAMERA PARAM
    double center[3]={0,0,0};
    double camera[3]={0,4.33013,5};
    double up_vector[3]={0,1,0};
    double angle[2]={0,60};
    float plane[2]={1,20};
    double dist=camera[2]-center[2];

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

 //   cout<<camera[1]<<endl;
//    cout<<angle[1]<<endl;
    glutPostRedisplay();
}

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

   // glOrtho(-5.0, 5.0, -5.0,5.0, -5.0, 5.0);
   gluPerspective(120,width/heigth,plane[0], plane[1]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera[0],camera[1],
           camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]);  

    glRotatef(270,1,0,0);
    glScalef(0.7,0.7,0.7);
        surface->drawCurve();
    glFlush();
}


int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Nurbs_Surface_0");
        glutKeyboardFunc(keyboardListener);
        glutDisplayFunc(redraw);

    //GL INIT
        glEnable(GL_DEPTH_TEST);
    
    //NURBS SURFACE INIT
        surface=new NurbsSurface(GLU_LINE,5,10,GLU_DOMAIN_DISTANCE,4,4);

    //PUSH CONTROL POINTS
        surface->addCheckpoint(-3,-3,-3,1);
        surface->addCheckpoint(-3, -1,-3,.5);
        surface->addCheckpoint(-3, 1, -3,.5);
        surface->addCheckpoint(-3, 3, -3,1);

        surface->addCheckpoint(-1, -3, -3,1);
        surface->addCheckpoint(-1, -1, 3,.5);
        surface->addCheckpoint(-1, 1, 3,.5);
        surface->addCheckpoint(-1, 3, -3,1);

        surface->addCheckpoint(1, -3, -3,1);
        surface->addCheckpoint(1, -1, 3,.5);
        surface->addCheckpoint(1, 1, 3,.5);
        surface->addCheckpoint(1, 3, -3,1);

        surface->addCheckpoint(3, -3, -3,1.);
        surface->addCheckpoint(3, -1, -3,.5);
        surface->addCheckpoint(3, 1, -3,.5);
        surface->addCheckpoint(3, 3, -3,1);

    //PUSH KNOTS
        surface->addKnot(0.);
        surface->addKnot(0.);
        surface->addKnot(0.);
        surface->addKnot(0.);
        surface->addKnot(1.);
        surface->addKnot(1.);
        surface->addKnot(1.);
        surface->addKnot(1.);

    glutMainLoop();
    return 0;
}
