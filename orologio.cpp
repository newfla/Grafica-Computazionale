#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<cstdlib>
#include<time.h>


bool prof=false, larg=false, alt=false, rotate=false, updatable=false;
double left=-1, right=1, bottom=-1, top=1, nearVal=1, farVal=5;
float width=600, heigth=600, angleMin=0, angleHour=0;
int xOld=0, yOld=0;
float radians=3.14/180, degrees=180/3.14, raggio=0.5;

void redraw(void){

    glClear(GL_COLOR_BUFFER_BIT);

    //CERCHIO
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(0.0,0.0);
        for(float i=0; i<=400; i++){
            glVertex2f(cos(i*radians)*raggio,sin(i*radians)*raggio);
        }
    glEnd();

    //LANCETTA ORE
    glPushMatrix();
    glRotatef(-angleHour,0.0,0.0,1.0);
        glBegin(GL_LINES);
            glColor3f(1.0,0.0,0.0);
            glVertex2f(0,0);
            glVertex2f(0,0+raggio-0.3);
        glEnd();
    glPopMatrix();

    //LANCETTA MINUTI
    glPushMatrix();
        glRotatef(angleMin,0.0,0.0,1.0);
        glBegin(GL_LINES);
            glColor3f(0.0,0.0,0.0);
            glVertex2f(0,0);
            glVertex2f(0,0+raggio-0.25);
        glEnd();
    glPopMatrix();

    glFlush();

}

void mouseMotionListener(int x, int y){
    if(xOld==0 && yOld==0){
            xOld=x;
            yOld=y;
            return;
        }
    //CALCOLO ANGOLO
    x-=xOld;
    y-=yOld;
    y*=-1;

   // printf("y: %d -- x:%d\n",y,x);
    float temp=atan2f(y,x);
    temp*=degrees;
    if(temp<0)
        temp+=360;
    temp=(int)temp%360;
   // printf("temp: %f -- Hour: %f\n",temp,angleHour);
    angleMin=temp;
    if((int)temp==0 && updatable){
        updatable=false;
        angleHour+=20;
        angleHour=(int)angleHour%360;
       // printf("temp: %f -- Hour: %f\n\n",temp,angleHour);
    }
    else if(temp>=1)
        updatable=true;
    glutPostRedisplay();
}




int main(int argc, char* argv[]){
    glutInit(&argc,argv); //INIT GLUT
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(383,154);
    glutInitWindowSize(width,heigth);
    glutCreateWindow("Esercizio 1"); //CREO UNA FINESTRA
    glutDisplayFunc(redraw); //PER RIDISEGNARE  QUANDO OPENGL CHIEDE USA REDRAW
    glutMotionFunc(mouseMotionListener);
    glutMainLoop();
    return 0;
}

