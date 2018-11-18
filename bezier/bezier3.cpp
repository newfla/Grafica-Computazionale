#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../utility/mesh.h"
using namespace Mesh;

//WINDOW PARAM
    float width=700, heigth=700;

//Point vector
    GLfloat cp[4][3] = {{ -4.0, -4.0, 0.0},
                        { -2.0, 4.0, 0.0},
                        { 2.0, -4.0, 0.0},
                        { 4.0, 4.0, 0.0}};

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    glScalef(0.3,0.3,1);
    glMapGrid1f(30, 0, 1); /*inizializza i valori equispaziati*/
    glEvalMesh1(GL_LINE, 0, 30); /*disegna la curva*/
    glFlush();
}
int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Bezier_3");
        glutDisplayFunc(redraw);

    //EVALUATORS
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &cp[0][0]);
        glEnable(GL_MAP1_VERTEX_3);

    glutMainLoop();
    return 0;
}
