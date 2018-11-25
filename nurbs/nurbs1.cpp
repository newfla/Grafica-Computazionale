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
    NurbsCurve curve(50,3);

GLvoid printError(GLenum errorCode){
    const GLubyte* estring;
    estring=gluErrorString(errorCode);
    std::cout<<estring<<std::endl;
}


void redraw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glScalef(0.1,0.1,0.1);
    curve.drawCurve();
    glFlush();
}

int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Nurbs_1");
        glutDisplayFunc(redraw);

    //INIT NURBS OBJ

        curve.addCheckpoint(-4.0,-4.0,0.0,1.0);

        curve.addCheckpoint(-2.0,4.0,0.0,5.0);

        curve.addCheckpoint(2.0,-4.0,0.0,1.0);
        
        curve.addCheckpoint(4.0,4.0,0.0,1.0);


        

        curve.addKnot(0.0);
        curve.addKnot(0.0);
        curve.addKnot(0.0);
        curve.addKnot(0.0);
        curve.addKnot(1.0);
        curve.addKnot(1.0);
        curve.addKnot(1.0);
        curve.addKnot(1.0);
        
  
    
    glutMainLoop();
    return 0;
}
