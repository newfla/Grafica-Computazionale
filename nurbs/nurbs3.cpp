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
    NurbsCurve* curva;

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glScalef(0.1,0.1,0.1);
    curva->drawCurve();
    glFlush();
}

int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Nurbs_3");
        glutDisplayFunc(redraw);

    //INIT NURBS OBJ FROM FILE

        curva= new NurbsCurve("nurbs/NURBS_data3.json");      
  
    
    glutMainLoop();
    return 0;
}
