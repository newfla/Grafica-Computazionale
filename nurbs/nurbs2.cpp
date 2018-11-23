#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../utility/mesh.h"
using namespace Mesh;

//WINDOW PARAM
    float width=700, heigth=700;

//NURB CURVE
    NurbsCurve curve(50,2);
void redraw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glScalef(0.2,0.2,0.2);
    curve.drawCurve();
    glFlush();
}

int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Nurbs_2");
        glutDisplayFunc(redraw);

    //INIT NURBS OBJ

        curve.addCheckpoint(1,2,0,1);
        curve.addCheckpoint(1,3,0,0.5);

        curve.addCheckpoint(3,3,0,0.5);
        curve.addCheckpoint(3,2,0,1);

        curve.addCheckpoint(3,1,0,0.5);
        curve.addCheckpoint(1,1,0,0.5);

        curve.addCheckpoint(1,2,0,1);

        curve.addKnot(0);
        curve.addKnot(0);
        curve.addKnot(0);

        curve.addKnot(0.25);

        curve.addKnot(0.5);
        curve.addKnot(0.5);

        curve.addKnot(0.75);

        curve.addKnot(1);
        curve.addKnot(1);
        curve.addKnot(1);

  
    
    glutMainLoop();
    return 0;
}
