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
    GLfloat w[4] ={ 1.0, 5.0, 1.0, 1.0};
    GLfloat cpw[4][4];


void calculate_cpw(){
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++){
           cpw[i][j]=cp[i][j]*w[i];
           cout<<cpw[i][j]<<endl;
        }
        cpw[i][3]=w[i];
        cout<<cpw[i][3]<<endl;
        cout<<"____"<<endl;
    }
    
}


void redraw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);

    glMapGrid1f(30, 0, 1); 
    glEvalMesh1(GL_LINE, 0, 30); 
    glFlush();
}
int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Bezier_4");
        glutDisplayFunc(redraw);

    //CALCULATE CPW
        calculate_cpw();    

glScalef(0.1,0.1,0.1);
    //EVALUATORS
        glMap1f(GL_MAP1_VERTEX_4, 0.0, 1.0, 4, 4, &cpw[0][0]);
        glEnable(GL_MAP1_VERTEX_4);

    glutMainLoop();
    return 0;
}
