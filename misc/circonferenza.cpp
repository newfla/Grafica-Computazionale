#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<cstdlib>
#include<time.h>

int max=1;
void redraw( void){
    float raggio=0.5;
    float radians=3.14/180;
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0,0.0,0.0);
        glVertex2d(0.0,0.0);
        glColor3f(0.0,0.0,1.0);
        for(int i=0; i<max; i++){
            glVertex2d(cos(i*radians)*raggio,sin(i*radians)*raggio);
        }
    glEnd();
    glFlush();

}

void keyboardListener(unsigned char key, int x, int y){
        switch(key){
        case ' ':
            if(max<361)
                max+=3;
            glutPostRedisplay();
            break;

        case 27:
            exit(1);
            break;
        }
}

int main(int argc, char* argv[]){
    glutInit(&argc,argv); //INIT GLUT
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(383,154);
    glutInitWindowSize(500,500);
    glutCreateWindow("Esercizio 1"); //CREO UNA FINESTRA
    glutDisplayFunc(redraw); //PER RIDISEGNARE  QUANDO OPENGL CHIEDE USA REDRAW
    glutKeyboardFunc(keyboardListener);
    glutMainLoop();
    return 0;
}

