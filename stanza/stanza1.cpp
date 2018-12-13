#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include "../utility/mesh.h"
#include <math.h>
using namespace std;
using namespace Mesh;

//WINDOW PARAM
    float width=700, height=700;
    float rotate[2]={0,0};
    int windowPos[2]={383,154};

//CAMERA PARAM
    double center[3]={17.1809,0.1825,7.94288};
    double camera[3]={12.185,0.25,8.14681};
    double up_vector[3]={0,1,0};
    double angle[2]={0,0};
    float plane[2]={1,200};
    float cameraFOV=45.;
    double dist=center[2]-camera[2];
    float cameraSpeed=0.3;

BezierSurface* surface;

//COLORS
    float colorParete1[3]={245./255.,245./255.,220/255.},
            colorParete2[3]={245./(2.*255.),245./(2.*255.),220/(2.*255.)},
            colorPavimento[3]={41./255.,86./255.,143./255.},
            colorApplique1[3]={255./255.,197/255.,143/255.},
            colorApplique2[3]={241./255.,141./255.,0./255.};

void resetMaterial(){
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,new float[4]{0.8,0.8,0.8,1});
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,new float[4]{0,0,0,1});
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,new float[4]{0,0,0,1});
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);      
}

void lightOn(){
    //LIGTH INIT
        
        glLightfv(GL_LIGHT1,GL_DIFFUSE,new float[4]{0.33,80./255.,74./255.,0});
        glLightfv(GL_LIGHT1,GL_SPECULAR,new float[4]{0.7,0.7,0.7,0});

        glLightfv(GL_LIGHT2,GL_DIFFUSE,new float[4]{0.33,80./255.,74./255.,0});
        glLightfv(GL_LIGHT2,GL_SPECULAR,new float[4]{0.7,0.7,0.7,0});

        glLightfv(GL_LIGHT3,GL_DIFFUSE,new float[4]{0.33,80./255.,74./255.,0});
        glLightfv(GL_LIGHT3,GL_SPECULAR,new float[4]{0.7,0.7,0.7,0});

        glLightfv(GL_LIGHT4,GL_DIFFUSE,new float[4]{0.33,80./255.,74./255.,0});
        glLightfv(GL_LIGHT4,GL_SPECULAR,new float[4]{0.7,0.7,0.7,0});
}


void redraw(void){
    //CLEAR
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

    //LIGTH
        lightOn();
        

    //UPDATE WIDTH HEIGHT WINDOW
        width=glutGet(GLUT_WINDOW_WIDTH);
        height=glutGet(GLUT_WINDOW_HEIGHT);

        gluPerspective(cameraFOV,width/height,plane[0], plane[1]);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(camera[0],camera[1],
            camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]);    

    //INGRANDIAMO UN PO' TUTTO
        glScalef(50,35,15);

    //COLORE PER LE PARETI LATERALI
        resetMaterial();
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,colorParete1);

    //PARETE SX    
        glPushMatrix();
            glScalef(1,0.2,1);
                surface->drawCurve();
        glPopMatrix();

    //PARETE DX
        glPushMatrix();
            glScalef(1,0.2,1);
            glTranslatef(0,0,2);
            glRotatef(180,1,0,0);
                surface->drawCurve();
        glPopMatrix();

        resetMaterial();
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,colorParete2);

    //PARETE INFONDO    
        glPushMatrix();
            glTranslatef(2,0,1);
            glScalef(1,0.2,0.5);
            glRotatef(270,0,1,0);
                surface->drawCurve();
        glPopMatrix();


    //PARETE DAVANTI  
        glPushMatrix();
            glTranslatef(-2,0,1);
            glScalef(1,0.2,0.5);
            glRotatef(90,0,1,0);
                surface->drawCurve();
        glPopMatrix();

    //COLORE PER IL PAVIMENTO
        resetMaterial();
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,128);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,colorPavimento);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,new float[4]{1,1,1,1});

    //PAVIMENTO
        glPushMatrix();
            glScalef(1,0.5,0.5);
            glTranslatef(0,-.8,2);
            glRotatef(270,1,0,0);
                surface->drawCurve();
        glPopMatrix();

    //COLORE PER IL SOFFITTO
        resetMaterial();
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,new float[3]{1,1,1});

    //SOFFITTO
        glPushMatrix();
            glScalef(1,0.5,0.5);
            glTranslatef(0,.8,2);
            glRotatef(90,1,0,0);
                surface->drawCurve();
        glPopMatrix();


    //COLOR APPLIQUE SX
        resetMaterial();
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,colorApplique1);

    //APPLIQUE PARETE SX
        glPushMatrix();
            glScalef(1,1,0.3);
            glTranslatef(.7,.1,.051);
                glutSolidCube(0.1);
                glLightfv(GL_LIGHT1,GL_POSITION, new float[4]{0,0,.51,1});
        glPopMatrix();
        glPushMatrix();
            glScalef(1,1,0.3);
            glTranslatef(-.7,.1,.051);
                glutSolidCube(0.1);
                glLightfv(GL_LIGHT2,GL_POSITION, new float[4]{0,0,0.51,1});
        glPopMatrix();

    //COLOR APPLIQUE DX
        resetMaterial();
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,colorApplique2);

    //APPLIQUE PARETE DX
        glPushMatrix();
            glTranslatef(0,0,2);
            glScalef(1,1,0.3);
            glTranslatef(1.1,.1,-.051);
                glutSolidCube(0.1);
                glLightfv(GL_LIGHT3,GL_POSITION, new float[4]{0,0,-0.51,1});
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0,2);
            glScalef(1,1,0.3);
            glTranslatef(-1.1,.1,-.051);
                glutSolidCube(0.1);
                glLightfv(GL_LIGHT4,GL_POSITION, new float[4]{0,0,-0.51,1});
        glPopMatrix();

    glFlush();
}

void moveCamera(float speed){
    float vVector[3];
    vVector[0]=center[0]-camera[0];
    vVector[1]=center[1]-camera[1];
    vVector[2]=center[2]-camera[2];

    camera[0]+=vVector[0]*speed;
    camera[2]+=vVector[2]*speed;

    center[0]+=vVector[0]*speed;
    center[2]+=vVector[2]*speed;

}

void rotateView(float speed){
    float vVector[3];
    vVector[0]=center[0]-camera[0];
    vVector[1]=center[1]-camera[1];
    vVector[2]=center[2]-camera[2];

    center[2] = (float)(camera[2] + sin(speed)*vVector[0] + cos(speed)*vVector[2]);
	center[0] = (float)(camera[0] + cos(speed)*vVector[0] - sin(speed)*vVector[2]);

}

void mouseListener(int x, int y){
    int midX=width/2, midY=height/2;
    if(x==midX && y==midY) return;
    glutWarpPointer(midX,midY);
    float angleY = (float)( (midX - x) ) / 1000.;		
	float angleZ = (float)( (midY - y) ) / 1000.;
    center[1]+=angleZ*2;

    if((center[1] - camera[1]) > 8)  center[1]= camera[1] + 8.;
	if((center[1] - camera[1]) <-8)  center[1]= camera[1] - 8.;
	
	rotateView(-angleY);
/*
    cout<<"--------------------\n";

    cout<<"Camera[0]: "<<camera[0]<<endl;
    cout<<"Camera[1]: "<<camera[1]<<endl;
    cout<<"Camera[2]: "<<camera[2]<<endl;

    cout<<"Center[0]: "<<center[0]<<endl;
    cout<<"Center[1]: "<<center[1]<<endl;
    cout<<"Center[2]: "<<center[2]<<endl;

    cout<<"--------------------\n";
*/

    glutPostRedisplay();
}

void keyboardListener(unsigned char key, int x, int y){
    switch (key){
        case 'A':
        case 'a':
            rotateView(-cameraSpeed);
            break;

        case 'S':
        case 's':
            moveCamera(-cameraSpeed);
            break;

        case 'D':
        case 'd':
            rotateView(cameraSpeed);
            break;

        case 'W':
        case 'w':
            moveCamera(cameraSpeed);
            break;

        default:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    //INIT GLUT
        glutInit(&argc,argv); 
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH);
        glutInitWindowPosition(windowPos[0],windowPos[1]);
        glutInitWindowSize(width,height);
        glutCreateWindow("Stanza");
        glutKeyboardFunc(keyboardListener);
        glutPassiveMotionFunc(mouseListener);
        glutDisplayFunc(redraw);

    //INIT GL
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);
        glEnable(GL_LIGHT4);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


    //BUILD GRID
        surface = new BezierSurface(GL_FILL,{4,4},{0,0},{1,1});
        surface->addCheckpoint(-2,-2,0,1);
        surface->addCheckpoint(-0.5,-2,0,1);
        surface->addCheckpoint(0.5,-2,0,1);
        surface->addCheckpoint(2,-2,0,1);

        surface->addCheckpoint(-2, -0.5,0,1);
        surface->addCheckpoint(-0.5, -0.5,0,1);
        surface->addCheckpoint(0.5, -0.5,0,1);
        surface->addCheckpoint(2, -0.5,0,1);

        surface->addCheckpoint(-2, 0.5,0,1);
        surface->addCheckpoint(-0.5, 0.5,0,1);
        surface->addCheckpoint(0.5, 0.5,0,1);
        surface->addCheckpoint(2, 0.5,0,1);
       
        surface->addCheckpoint(-2, 2,0,1);
        surface->addCheckpoint(-0.5, 2,0,1);
        surface->addCheckpoint(0.5, 2,0,1);
        surface->addCheckpoint(2, 2,0,1);

    //DISPLAY    
        glutMainLoop();

    return 0;
}