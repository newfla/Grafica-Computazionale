#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include "../utility/mesh.h"
#include "SOIL/SOIL.h"
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
            colorApplique1[3]={1,1,1},
            colorApplique2[3]={1,1,1};

//TEXTURE 
    GLuint textures[3];

void resetMaterial(){
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,new float[4]{0.8,0.8,0.8,1});
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,new float[4]{0,0,0,1});
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,new float[4]{0,0,0,1});
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,0);
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

void drawLongSide(){
    glPushMatrix();
        glTranslatef(-1.6,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.4,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.2,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.8,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.6,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.4,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-.2,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();
        
        glPushMatrix();
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(.2,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(.4,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(.6,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(.8,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.2,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.4,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.6,0,0);
            glScalef(.2,0.2,1);
                surface->drawCurve();
        glPopMatrix();
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
    
     //TEXTURE MATTONE PER LE PARETI
        glBindTexture(GL_TEXTURE_2D,textures[0]);

    //PARETE SX

        drawLongSide();

    //PARETE DX
        glPushMatrix();
            glTranslatef(0,0,2);
            glRotatef(180,1,0,0);
                drawLongSide();
        glPopMatrix();

        resetMaterial();
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,colorParete2);

    //TEXTURE MATTONE PER LE PARETI
        glBindTexture(GL_TEXTURE_2D,textures[0]);

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

    //TEXTURE PAVIMENTO
        glBindTexture(GL_TEXTURE_2D,textures[1]);

    //PAVIMENTO
        glPushMatrix();
            glScalef(1,1,2.5);
            glTranslatef(0,-.4,.4);
            glRotatef(270,1,0,0);
               drawLongSide();
        glPopMatrix();


    //COLORE PER IL SOFFITTO
        resetMaterial();
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,new float[3]{1,1,1});

    //SOFFITTO
        glPushMatrix();
            glScalef(1,1,2.5);
            glTranslatef(0,.4,.4);
            glRotatef(90,1,0,0);
                drawLongSide();
        glPopMatrix();
    
    //COLOR APPLIQUE SX
        resetMaterial();
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,colorApplique1);

    //TEXTURE TESSUTO
        glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
        glBindTexture(GL_TEXTURE_2D,textures[2]);

    //APPLIQUE PARETE SX
        glPushMatrix();
            glScalef(1,1,0.3);
            glTranslatef(.7,.1,.051);
                glutSolidCube(0.1);
                glLightfv(GL_LIGHT1,GL_POSITION, new float[4]{0,0,0.51,1});
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

    //TEXTURE TESSUTO
        glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
        glBindTexture(GL_TEXTURE_2D,textures[2]);

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

    glutSwapBuffers();
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

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

GLvoid initTexture(const char* path, int pos,bool mipMap){
    int imageWidth, imageHeight, components;
    unsigned char *image;
    glBindTexture(GL_TEXTURE_2D,textures[pos]);
    image=SOIL_load_image(path,&imageWidth,&imageHeight,&components,SOIL_LOAD_RGBA);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if(mipMap){
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, imageWidth,imageHeight,GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    SOIL_free_image_data(image);
    glEnable( GL_TEXTURE_2D );
    if( 0 == image )
{
	cout<<"SOIL loading error: "<<endl<<SOIL_last_result();
    cout<<endl<<"--------"<<endl;
}

}


int main(int argc, char* argv[]){
    //INIT GLUT
        glutInit(&argc,argv); 
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowPosition(windowPos[0],windowPos[1]);
        glutInitWindowSize(width,height);
        glutCreateWindow("Stanza_Texture");
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
        glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);


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


    //LOAD TEXTURE
       glGenTextures(3,textures);
       initTexture("stanza/brick.jpg",0,true);
       initTexture("stanza/floor.jpg",1,true);
       initTexture("stanza/violet2.jpg",2,true);


    //DISPLAY    
        glutMainLoop();

    return 0;
}