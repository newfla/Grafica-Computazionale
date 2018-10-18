#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


int stati[2];
float zoom[2]={0,0};
bool rotate=false, scale=false, move=false;
float width=600, heigth=600;

void checkMouse(){
    //CHECK rotation
    if (rotate){
        if (stati[0]==GLUT_DOWN)
             glRotatef(0.012,0,0,1);
        if(stati[1]==GLUT_DOWN)
            glRotatef(-0.012,0,0,1);
    }
    glutPostRedisplay();
}

void mouseListener(int button, int state, int x, int y){
    //Save left right button state
    switch (button){
        case GLUT_LEFT_BUTTON:
            stati[0]=state;
            break;

        case GLUT_RIGHT_BUTTON:
            stati[1]=state;
            break;
    }
}

void mouseMotionPassiveListener(int x, int y){
   if (zoom[0]==0)
        zoom[0]=(2.0*(float)y)/600.0;
    else
        zoom[1]=(2.0*(float)y)/600.0;;
  if (scale){
        //600:2=cord:x
        float scaleFactor=zoom[0]-zoom[1];
        glScalef(1+scaleFactor,1+scaleFactor,0);
        zoom[0]=zoom[1];
    }
}

void mouseMotionListener(int x, int y){
   float xTranslate=(2.0*(float)x)/width,
        yTranslate=(2.0*(float)y)/heigth;
        printf("%f, %f\n",xTranslate-1, yTranslate-1);
    if (move && stati[0]==GLUT_DOWN){
        glLoadIdentity();
        glTranslatef(xTranslate-1,-(yTranslate-1),0);
    }
}


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
            glTranslatef(-0.1,0,0);
            break;
        case (GLUT_KEY_UP):
            glTranslatef(0,0.1,0);
            break;
        case(GLUT_KEY_RIGHT):
            glTranslatef(0.1,0,0);
            break;
        case(GLUT_KEY_DOWN):
            glTranslatef(0,-0.1,0);
            break;
    }
    glutPostRedisplay();
}

void keyListener(unsigned char key, int x, int y){
        switch(key){
        case 'w':
            glScalef(1.1,1.1,0);
            break;

        case 's':
            glScalef(0.9,0.9,0);
            break;

        case 'a':
            glRotatef(2,0,0,1);
            break;

        case 'd':
            glRotatef(-2,0,0,1);
            break;

        case 'r':
            rotate=!rotate;      
            break;  

        case 'z':
            scale=!scale;
            break;

        case 'm':
            move=!move;
            break;
        }
        glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(width,heigth);
    glutCreateWindow("");
    glutDisplayFunc(redraw);
    glutSpecialFunc(specialKeyListener);
    glutKeyboardFunc(keyListener);
    glutMouseFunc(mouseListener);
    glutPassiveMotionFunc(mouseMotionPassiveListener);
    glutMotionFunc(mouseMotionListener);
    glutIdleFunc(checkMouse);
    for (int i=0; i<2; i++)
        stati[i]=GLUT_UP;
    glutMainLoop();
    return 0;
}
