#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<cstdlib>
#include<time.h>


bool prof=false, larg=false, alt=false, rotate=false, first=true;
double left=-1, right=1, bottom=-1, top=1, nearVal=1, farVal=5;
float width=600, heigth=600, angleX=0, angleY=0;
int xOld=0, yOld=0;

void redraw( void){
    float max=360;
    float lati=8;
    float raggio=0.5;
    float step=360/lati;
    float radians=3.14/180;
    float z1=-0.5,z2=-1.0;
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(left,right,bottom,top,nearVal,farVal);
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
            alt=!alt;
            prof=false;
            rotate=false;
            larg=false;
            break;

        case 'L':
        case 'l':
            larg=!larg;
            prof=false;
            rotate=false;
            alt=false;
            break;

        case 'P':
        case 'p':
            prof=!prof;   
            rotate=false;
            larg=false;
            alt=false;   
            break;

        case 'R':
        case 'r':
            rotate=!rotate;
            larg=false;
            alt=false;  
            prof=false;
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
        angleX+=2*(x-xOld);
        angleY+=2*(y-yOld);
    }
    else{
        bool ok=false;
        if (prof){
            farVal-=0.05*(y-yOld)/5.0;
            nearVal+=0.05*(y-yOld)/5.0;
            printf("Near: %f ______ Far: %f\n\n",nearVal,farVal);
            ok=true;
        }
        else if(larg){
            left-=0.002*(x-xOld)/5.0;
            right+=0.002*(x-xOld)/5.0;
            printf("L: %f ______ R: %f\n\n",left,right);
            ok=true;
        }
        else if (alt){
            bottom+=0.002*((y-yOld)/5.0);
            top-=0.002*((y-yOld)/5.0);
            printf("Bot: %f ______ Top: %f\n\n",bottom,top);
            ok=true;
        }
        if(ok){
           // glLoadIdentity();
         //   glOrtho(left,right,bottom,top,nearVal,farVal);
        }
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

