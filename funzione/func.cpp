#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include"../utility/mesh.h"
#include <math.h>
using namespace Mesh;

//WINDOW PARAM
    float width=700, heigth=700;
    float rotate[2]={0,0};
    int windowPos[2]={383,154};

//CAMERA PARAM
    double center[3]={0,0,0};
    double camera[3]={6.5,7.1,27};
    double up_vector[3]={0,1,0};
    double angle[2]={0,0};
    float plane[2]={1,100};
    double dist=center[2]-camera[2];

//ANIMATION
    Mesh::Figure funz;

//ACCURACY
    float step=0.3;

void redraw(void){
    //CLEAR
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60,width/heigth,plane[0], plane[1]);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    //REGOLAZIONE PUNTO DI VISTA
        glPushMatrix();
            gluLookAt(camera[0],camera[1],
            camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]);   
            funz.draw();
        glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void keyboardListener(unsigned char key, int x, int y){
    switch (key){
        case 'A':
        case 'a':
            angle[0]+=2;
            break;

        case 'S':
        case 's':
        angle[1]+=2;
            break;

        case 'D':
        case 'd':
            angle[0]-=2;
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

    glutPostRedisplay();
}

double func(double x, double z){
    double radice=sqrt(x*x+z*z);
    return (2*sin(radice))/radice;
}

double func2(double x, double z, double k){
    double radice=sqrt(x*x+z*z)-k*(M_PI/32);
    return (2*sin(radice))/radice;
}



void timerListener(int value){
    if(value==1){
        for(float x = -10; x <= 10; x+=step){
                for(float z = -10; z < 10; z+=step){
                    Face faccia;
                    faccia.vertex.push_back(Point(x,func2(x,z,value),-z));
                    faccia.vertex.push_back(Point(x+step,func2(x+step,z,value),-z));
                    faccia.vertex.push_back(Point(x+step,func2(x+step,z+step,value),-(z+step)));
                    faccia.vertex.push_back(Point(x,func2(x,z+step,value),-(z+step)));
                    funz.addFaces(faccia);
                }
            }
    }else{
        int count=0;
        if(value==300)
            value=1;
        vector<Face> faces=funz.faces;
        for(float x = -10; x <= 10; x+=step){
                for(float z = -10; z <= 10; z+=step){
                    funz.faces[count].vertex[0].getCoords()[1]=func2(x,z,value);

                   // funz.faces[count].vertex[1].getCoords()[0]=x+step;
                    funz.faces[count].vertex[1].getCoords()[1]=func2(x+step,z,value);

                   // funz.faces[count].vertex[2].getCoords()[0]=x+step;
                    funz.faces[count].vertex[2].getCoords()[1]=func2(x+step,z+step,value);
                   // funz.faces[count].vertex[2].getCoords()[2]=-(z+step);


                    funz.faces[count].vertex[3].getCoords()[1]=func2(x,z+step,value);
                    //funz.faces[count].vertex[3].getCoords()[2]=-(z+step);
                    funz.faces[count].forceNormal();
                    count++;
                }
                
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16,timerListener,value+1);
    
}


int main(int argc, char* argv[]){
    //INIT GLUT
        glutInit(&argc,argv); 
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowPosition(windowPos[0],windowPos[1]);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Animazione");
        glutKeyboardFunc(keyboardListener);
        glutDisplayFunc(redraw);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glShadeModel(GL_FLAT);
        timerListener(1);

    //DISPLAY    
        glutMainLoop();

    return 0;
}