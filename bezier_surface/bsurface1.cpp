#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include<vector>
#include <time.h>
#include "../utility/mesh.h"
using namespace Mesh;
using namespace std;

//WINDOW PARAM
    float width=700, heigth=700;

//BEZIER CURVE VECTOR PARAM
    vector<float> minz={0,0}, maxz={1,1},order={4,4};

//BEZIER CURVE
    BezierSurface surface(GL_LINE,order,minz,maxz);

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-5.0, 5.0, -5.0,5.0, -5.0, 5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

;
    glColor3f(0.,1.,0.);
    glRotatef(180.0, 1.0, 1.0, 1.0);
       surface.drawCurve();
    glFlush();
}


int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Bezier_Surface_1");
        glutDisplayFunc(redraw);

    //GL INIT
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_AUTO_NORMAL);
        glShadeModel(GL_FLAT);

    //PUSH CONTROL POINTS
        surface.addCheckpoint(0.,0.,0.,1.);
        surface.addCheckpoint(1,0.,.5,1.);
        surface.addCheckpoint(2.,0.,1.,1.);
        surface.addCheckpoint(3.,0.,0.,1.);

        surface.addCheckpoint(0.,1.,0.,1.);
        surface.addCheckpoint(1.,1.,3.,1.);
        surface.addCheckpoint(2.,1.,3.,1.);
        surface.addCheckpoint(3.,1.,0.,1.);

        surface.addCheckpoint(0.,2.,0.,1.);
        surface.addCheckpoint(1.,2.,3.,1.);
        surface.addCheckpoint(2.,2.,3.,1.);
        surface.addCheckpoint(3.,2.,0.,1.);

        surface.addCheckpoint(0.,3.,0.,1.);
        surface.addCheckpoint(1.,3.,1.,1.);
        surface.addCheckpoint(2.,3.,0.5,1.);
        surface.addCheckpoint(3.,3.,0.,1.);

    glutMainLoop();
    return 0;
}
