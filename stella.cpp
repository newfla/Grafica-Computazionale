#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


void redraw(){
    float raggio=0.55, raggio2=0.12, temp=raggio;
    float radians=3.14/180;
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1,1,1);
        glVertex2d(0.0,0.0);
        for(int i=0; i<=396; i+=36){
            printf("%d\n",i);
            if(temp==raggio)
                temp=raggio2;
            else
                temp=raggio;
            glVertex2d(cos(i*radians)*temp,sin(i*radians)*temp);
        }
    glEnd();
    glFlush();
}

void keyListener(int key, int x, int y){
    switch(key){
        case(GLUT_KEY_LEFT):
            //Traslazione
            break;
        case (GLUT_KEY_UP):
            //Rotazione
            break;
        case(GLUT_KEY_RIGHT):
            //Scale in grande
            break;
        case(GLUT_KEY_DOWN):
            //Scale in piccolo
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("");
    glutDisplayFunc(redraw);
    glutSpecialFunc(keyListener);
    glutMainLoop();
    return 0;
}
