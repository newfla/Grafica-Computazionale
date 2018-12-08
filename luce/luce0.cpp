#define _USE_MATH_DEFINES
#include<math.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include <string>
#include<vector>
#include<math.h>
#include <iostream>
#include <map>
using namespace std;

//WINDOW PARAM
    float width=700, heigth=700;

//CAMERA PARAM
    double center[3]={0,0,0};
    float camera[3]={0.348782,1.31176,4.98782};
    double up_vector[3]={0,1,0};
    double angle[4]={-94,1.31176,0,0};
    float plane[2]={1,20};
    double dist=camera[2]-center[2];

void directionalListener(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            angle[3]-=2;
            break;

        case GLUT_KEY_DOWN:
        angle[3]+=2;
            break;

        case GLUT_KEY_LEFT:
            angle[2]-=2;
            break;

        case GLUT_KEY_RIGHT:
            angle[2]+=2;
            break;
    }
    glutPostRedisplay();
}

void keyboardListener(unsigned char key, int x, int y){
    switch (key){
        case 'A':
        case 'a':
            angle[0]-=2;
            break;

        case 'S':
        case 's':
        angle[1]+=2;
            break;

        case 'D':
        case 'd':
            angle[0]+=2;
            break;

        case 'W':
        case 'w':
            angle[1]-=2;
            break;
    }
    //Rotazione intorno all'oggetto;
    camera[0]=center[0]+(dist*cos(angle[0]*((double)M_PI/180.0)));
    camera[2]=center[2]+(dist*sin(angle[0]*((double)M_PI/180.0)));

    //Guardare dall'alto e dal basso l'oggetto entro i 60gradi
    if(angle[1]<-60.0)
        angle[1]=-60.0;
    else if(angle[1]>60.0)
        angle[1]=60;
    if(angle[1]!=0)
        camera[1]=center[1]+(dist*sin(angle[1]*((double)M_PI/180.0)));

    /*cout<<"camera2: "<<camera[2]<<endl;
    cout<<"camera1 :"<<camera[1]<<endl;
    cout<<"angl1: "<<angle[1]<<endl;
    cout<<"camera0 :"<<camera[0]<<endl;
    cout<<"angl0: "<<angle[0]<<endl<<"-------------"<<endl;*/

    float light2dir[4]={camera[0],camera[1],camera[2],0};
    glLightfv(GL_LIGHT2,GL_POSITION,light2dir);

    glutPostRedisplay();
}

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90,width/heigth,plane[0], plane[1]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightfv(GL_LIGHT1,GL_POSITION,new float[4]{1,1,1,1});

    gluLookAt(camera[0],camera[1],
           camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]);

        float light2dir[4]={camera[0],camera[1],camera[2],0};
        glLightfv(GL_LIGHT2,GL_POSITION,light2dir);

        glRotatef(angle[2],0,1,0);
        glRotatef(angle[3],1,0,0);

        //Aggiungiamo le due sfere intersecate
            glutSolidSphere(0.5,50,50);
        
        glPushMatrix();
            glTranslatef(0.35,0.35,0.25);
                glutSolidSphere(0.5,50,50);
        glPopMatrix();

    glFlush();
}


int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Prova_Luce");
        glutKeyboardFunc(keyboardListener);
        glutSpecialFunc(directionalListener);
        glutDisplayFunc(redraw);

    //GL INIT
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);

    //GL LIGHT COLOR INIT
        glLightfv(GL_LIGHT1,GL_DIFFUSE,new float[3]{1,1,1});
        glLightfv(GL_LIGHT2,GL_DIFFUSE,new float[3]{1,0,0});

    glutMainLoop();
    return 0;
}
