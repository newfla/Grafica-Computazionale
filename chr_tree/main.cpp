#define _USE_MATH_DEFINES

#include "tree.h"
using namespace Mesh;
using namespace std;
using namespace Tree;

//WINDOW PARAM
    float width=700, heigth=700;

//CHRISTMAS ITEMS
    Star stella;
    ChrTree albero;
    GluSolidFigure* pavimento;
    vector<Decor>decors;
    vector<Gift> gifts;

//CHRISTMAS TEXTURE
    TreeTextureContainer* container;

//CAMERA PARAM
    double center[3]={0,0,0};
    double camera[3]={-0.348782,1.31176,-4.98782};
    double up_vector[3]={0,1,0};
    double angle[2]={-94,1.31176};
    float plane[2]={1,20};
    double dist=camera[2]-center[2];
    bool light=true;

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

        case 27:
            exit(0);

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

void lightSwitch(int value){
    if(value==0){
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);

        glDisable(GL_LIGHT6);
        glDisable(GL_LIGHT7);
    }
    else if(value==1){
        glEnable(GL_LIGHT4);
        glEnable(GL_LIGHT5);

        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
    }
    else{
        glEnable(GL_LIGHT6);
        glEnable(GL_LIGHT7);

        glDisable(GL_LIGHT4);
        glDisable(GL_LIGHT5);
    }
    glutPostRedisplay();
    glutTimerFunc(1000,lightSwitch,(value+1)%3);
}

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90,width/heigth,plane[0], plane[1]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera[0],camera[1],
           camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]);

    glScalef(1.2,1.2,1.2);
    
    //ALBERO + STELLA + PALLINE
        albero.draw(container);

    //DONI
        for(int i = 0; i < gifts.size(); i++){
            glPushMatrix();
                glRotatef(i*360/gifts.size(),0,1,0);
                    gifts[i].draw(-1,albero.getTroncoHeight(),container);
            glPopMatrix();
        }

    //PAVIMENTO
    glPushMatrix();
        ChrTree::resetMaterial();
       // glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,new float[3]{0,0.19,0.05});
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,new float[3]{1,1,1});
        glBindTexture(GL_TEXTURE_2D,container->getPos(2));
        glTranslatef(0,-(albero.getTroncoHeight()+0.007),0);
        glRotatef(270,1,0,0);
            pavimento->drawDisk(0,3,50,50);
    glPopMatrix();
    glFlush();
}


int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Christmas_Tree");
        glutKeyboardFunc(keyboardListener);
        glutDisplayFunc(redraw);
        glutTimerFunc(2000,lightSwitch,0);

    //GL INIT
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

    //LIGHT INIT
        glLightfv(GL_LIGHT1,GL_DIFFUSE,new float[3]{1,1,1});
        glLightfv(GL_LIGHT1,GL_SPECULAR,new float[3]{1,1,1});
        glLightfv(GL_LIGHT1,GL_POSITION, new float[4]{5,30,0,1});

        glLightfv(GL_LIGHT2,GL_DIFFUSE,new float[3]{1,1,1});
        glLightfv(GL_LIGHT2,GL_SPECULAR,new float[3]{1,1,1});
        glLightfv(GL_LIGHT3,GL_SPECULAR,new float[3]{1,1,1});
        glLightfv(GL_LIGHT3,GL_DIFFUSE,new float[3]{1,1,1});

        glLightfv(GL_LIGHT4,GL_DIFFUSE,new float[3]{.5,0,0});
        glLightfv(GL_LIGHT4,GL_SPECULAR,new float[3]{.5,0,0});
        glLightfv(GL_LIGHT5,GL_SPECULAR,new float[3]{.5,0,0});
        glLightfv(GL_LIGHT5,GL_DIFFUSE,new float[3]{.5,0,0});

        glLightfv(GL_LIGHT6,GL_DIFFUSE,new float[3]{147./255.,112./255.,219/255.});
        glLightfv(GL_LIGHT6,GL_SPECULAR,new float[3]{147./255.,112./255.,219/255.});
        glLightfv(GL_LIGHT7,GL_SPECULAR,new float[3]{147./255.,112./255.,219/255.});
        glLightfv(GL_LIGHT7,GL_DIFFUSE,new float[3]{147./255.,112./255.,219/255.});
        
    //INIT CHRISTMAS
        container=new TreeTextureContainer();
        pavimento=new GluSolidFigure(GLU_FILL,GLU_OUTSIDE,GLU_FLAT);
        stella.buildFromFile("chr_tree/json/star.json");
        decors=Decor::buildDecorsFromFile("chr_tree/json/decor.json",container);
        gifts=Gift::buildGiftsFromFile("chr_tree/json/gift.json",container);
        albero.buildTreeFromFile("chr_tree/json/albero.json",container);
        albero.addStar(stella);
        albero.addDecor(decors);

    //INIT PAVIMENTO TEXTURE
        container->initTexture("chr_tree/texture/floor.jpg",2,true);
    

    glutMainLoop();
    return 0;
}
