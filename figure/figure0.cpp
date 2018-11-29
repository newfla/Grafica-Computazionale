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

//BEZIER CURVE
    GluSolidFigure figura(GLU_FILL,GLU_OUTSIDE,GLU_FLAT);

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-5.0, 5.0, -5.0,5.0, -5.0, 5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   /* glPushMatrix();
        glRotatef(180.0, 1.0, 1.0, 1.0);
            figura.drawSphere(0.75,15,10);
    glPopMatrix();*/
    glutSolidTeapot(2);
    glFlush();
}


int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Figure_0");
        glutDisplayFunc(redraw);

    //GL INIT
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);


    glutMainLoop();
    return 0;
}
