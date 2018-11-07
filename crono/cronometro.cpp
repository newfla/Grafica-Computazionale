#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include "crono.h"
using Crono::Quadrante;
using Crono::Tasto;

//WINDOW PARAM
float width=600, heigth=600;
float rotate[2]={0,0};
int windowPos[2]={383,154};

Quadrante quadrante;
Tasto start, reset;



void redraw(void){
    //CLEAR BUFFER
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
    //3D MODE
        glOrtho(-1,1,-1,1,-1,1);

    //CRONO ROTATION AND DRAWING
        quadrante.draw();

    //DRAW BUTTONS
        
        start.draw();
        reset.draw();

    glFlush();
}

void keyboardListener(unsigned char key, int x, int y){
    switch (key){
        case 'A':
        case 'a':
            quadrante.rotate[1]+=3;
            break;

        case 'S':
        case 's':
            quadrante.rotate[0]-=3;
            break;

        case 'D':
        case 'd':
            quadrante.rotate[1]-=3;
            break;

        case 'W':
        case 'w':
            quadrante.rotate[0]+=3;
            break;

    }
    glutPostRedisplay();
}

void mouseListener(int button, int state, int x, int y){
    float nx, ny;
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        
        nx=(2.0*(float)x)/width;
        nx-=1;
        ny=(2.0*(float)y)/heigth;
        ny-=1;
        ny*=-1;
        start.checkClick(nx,ny);
        reset.checkClick(nx,ny);
        if(reset.status){
            quadrante.minuti.rotate[0]=0;
            quadrante.secondi.rotate[0]=0;
            reset.status=false;
        }
        glutPostRedisplay();
    }
}

void timerListener(int value){
    if (start.status) {
        quadrante.secondi.rotate[0]+=6;
        if(quadrante.secondi.rotate[0]>=360)
            quadrante.secondi.rotate[0]-=360;
        if(quadrante.secondi.rotate[0]==0)
            quadrante.minuti.rotate[0]+=6;
        if(quadrante.minuti.rotate[0]>=360)
            quadrante.minuti.rotate[0]-=360;
    }
    glutTimerFunc(1000,timerListener,0);
    glutPostRedisplay();
    
}

int main(int argc, char* argv[]){
    //INIT GLUT
        glutInit(&argc,argv); 
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH);
        glutInitWindowPosition(windowPos[0],windowPos[1]);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Crono_Start_Stop_Reset");
        glutKeyboardFunc(keyboardListener);
        glutMouseFunc(mouseListener);
        glutTimerFunc(1000,timerListener,0);
        glutDisplayFunc(redraw);
        glEnable(GL_DEPTH_TEST);

    //INIT OBJ CLASS
        quadrante.raggio=0.45;
        quadrante.z1=-0.5;
        quadrante.z2=-0.6;
        quadrante.x=0;
        quadrante.y=0;

        quadrante.secondi.x=0;
        quadrante.secondi.y=0;
        quadrante.secondi.z1=-0.48;
        quadrante.secondi.raggio=0.4;
        quadrante.secondi.color[0]=0.87;
        quadrante.secondi.color[1]=0.17;
        quadrante.secondi.color[2]=0;

        quadrante.minuti.x=0;
        quadrante.minuti.y=0;
        quadrante.minuti.z1=-0.47;
        quadrante.minuti.raggio=0.3;
        quadrante.minuti.color[0]=0;
        quadrante.minuti.color[1]=0;
        quadrante.minuti.color[2]=0;
        

        start.lato=0.2;
        start.x=-0.8;
        start.y=-0.75;
        start.z1=-0.5;
        start.color[0][0]=0.26;
        start.color[0][1]=0.63;
        start.color[0][2]=0.28;
        start.color[1][0]=1;
        start.color[1][1]=0.92;
        start.color[1][2]=0.23;
        start.stringhe[0]="START";
        start.stringhe[1]="STOP ";

        reset.lato=0.2;
        reset.x=0.6;
        reset.y=-0.75;
        reset.z1=-0.6;
        reset.type=1;
        reset.color[0][0]=0.83;
        reset.color[0][1]=0.18;
        reset.color[0][2]=0.18;
        reset.color[1][0]=0.83;
        reset.color[1][1]=0.18;
        reset.color[1][2]=0.18;
        reset.stringhe[0]="RESET";
        reset.stringhe[1]=reset.stringhe[0];

    //DISPLAY    
        glutMainLoop();

    return 0;
}