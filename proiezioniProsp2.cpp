#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<cstdlib>
#include<time.h>


bool fovB=false, aspectB=false, rotate=false;
double fov=90, aspect=1/*6.0/9.0*/, nearVal=1, farVal=5;
float width=600, heigth=600, angleX=20, angleY=20;
int xOld=0, yOld=0;

void redraw(void){
    float lati=8;
    float raggio=0.5;
    float step=360/lati;
    float radians=3.14/180;
    float z1=-0.5,z2=-1.0;
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluPerspective(fov,aspect,nearVal,farVal);
    glTranslatef(0.0,0.0,-3.0);

   //GESTIONE ROTAZIONE ACCUMULATA
    glRotatef(-angleY,1.0,0.0,0.0);
    glRotatef(-angleX,0.0,1.0,0.0);

    //PRIMA BASER
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0.2,0.2,z1);
        for(float i=0; i<=500; i+=step){
            glVertex3f(cos(i*radians)*raggio,sin(i*radians)*raggio,z1);
        }
    glEnd();

    //SECONDA BASE
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0.2,0.2,z2);
        for(float i=0; i<=500; i+=step){
            glVertex3f(cos(i*radians)*raggio,sin(i*radians)*raggio,z2);
        }
    glEnd();

    //RETTANGOLI LATERALI
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.0,1.0,0.0);
        bool z=true;
        for(float i=0; i<=500; i+=step)
        {
            glVertex3f(cos(i*radians)*raggio,sin(i*radians)*raggio,z2);
            glVertex3f(cos(i*radians)*raggio,sin(i*radians)*raggio,z1);
        }
    glEnd();
    glFlush();

}

void keyboardListener(unsigned char key, int x, int y){
        switch(key){

        case 'A':
        case 'a':
            aspectB=!aspectB;
            fovB=false;
            rotate=false;
            break;

        case 'F':
        case 'f':
            fovB=!fovB;
            aspectB=false;
            rotate=false;
            break;

        case 'R':
        case 'r':
            rotate=!rotate;
            fov=false;
            aspect=false;
            break;
        }
}

void mouseMotionListener(int x, int y){
    if(xOld==0 && yOld==0){
            xOld=x;
            yOld=y;
            return;
        }
    if (rotate){
        angleX+=2.0*(x-xOld);
        angleY+=2.0*(y-yOld);
        printf("angleX: %f, angleY: %f\n",angleX,angleY);
    }
    else if (fovB){
        double old=fov;
        fov+=(y-yOld);
        printf("oldFov: %f, fov: %f\n",old,fov);
    }
    else if (aspectB){
        double old=aspect;
        aspect+=(float)(y-yOld);
        printf("oldAsp: %f, asp: %f\n",old,aspect);
    }
    xOld=x;
    yOld=y;
    glutPostRedisplay();
}


int main(int argc, char* argv[]){
    glutInit(&argc,argv); //INIT GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(383,154);
    glutInitWindowSize(width,heigth);
    glutCreateWindow("Esercizio 1"); //CREO UNA FINESTRA
    glutDisplayFunc(redraw); //PER RIDISEGNARE  QUANDO OPENGL CHIEDE USA REDRAW
    glutKeyboardFunc(keyboardListener);
    glutMotionFunc(mouseMotionListener);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

