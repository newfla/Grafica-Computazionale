#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

float move_x=0,move_y=0, scaling=1,angle=0;
void redraw(){
    float raggio=0.55, raggio2=0.12, temp=raggio;
    float radians=3.14/180;
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1,1,1);
        glVertex2d(0.0,0.0);
        for(int i=0; i<=396; i+=36){
            if(temp==raggio)
                temp=raggio2;
            else
                temp=raggio;
            glVertex2d(cos(i*radians)*temp,sin(i*radians)*temp);
        }
    glEnd();
    glFlush();
}

void specialKeyListener(int key, int x, int y){
    switch(key){
        case(GLUT_KEY_LEFT):
            move_x-=0.1;
            glTranslatef(move_x,0,0);
            break;
        case (GLUT_KEY_UP):
            move_y+=0.1;
            glTranslatef(0,move_y,0);
            break;
        case(GLUT_KEY_RIGHT):
            move_x+=0.1;
            glTranslatef(move_x,0,0);
            break;
        case(GLUT_KEY_DOWN):
            move_y-=0.1;
            glTranslatef(0,move_y,0);
            break;
        default:
            printf("444");
    }
    glutPostRedisplay();
}

void keyListener(unsigned char key, int x, int y){
        switch(key){
        case 'w':
            scaling+=0.1;
            glScalef(scaling,scaling,0);
            break;

        case 's':
            scaling-=0.1;
            glScalef(scaling,scaling,0);
            break;

        case 'a':
            angle+=2;
            glRotatef(angle,0,0,1);
            break;

        case 'd':
            angle-=2;
            glRotatef(angle,0,0,1);
            break;
        }
        glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("");
    glutDisplayFunc(redraw);
    glutSpecialFunc(specialKeyListener);
    glutKeyboardFunc(keyListener);
    glutMainLoop();
    return 0;
}
