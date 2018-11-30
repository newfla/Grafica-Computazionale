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

//CAMERA PARAM
    double center[3]={0,0,0};
    double camera[3]={-0.348782,1.31176,-4.98782};
    double up_vector[3]={0,1,0};
    double angle[2]={-94,1.31176};
    float plane[2]={1,20};
    double dist=camera[2]-center[2];

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
    glutPostRedisplay();
}

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(120,width/heigth,plane[0], plane[1]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera[0],camera[1],
           camera[2],center[0],center[1],center[2],up_vector[0],up_vector[1],up_vector[2]);

    glScalef(1.2,1.2,1.2);
    //ALBERO + STELLA + PALLINE
        albero.draw();

    //DONI
    for(int i = 0; i < gifts.size(); i++)
    {
        glPushMatrix();
            glRotatef(i*360/gifts.size(),0,1,0);
                gifts[i].draw(-1,albero.getTroncoHeight());
        glPopMatrix();
    }

    //PAVIMENTO
    glPushMatrix();
        glColor3f(0,0.19,0.05);
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

    //GL INIT
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);

    //INIT CHRISTMAS STAR
        pavimento=new GluSolidFigure(GLU_FILL,GLU_OUTSIDE,GLU_FLAT);
        stella.buildFromFile("chr_tree/json/star.json");
        decors=Decor::buildDecorsFromFile("chr_tree/json/decor.json");
        gifts=Gift::buildGiftsFromFile("chr_tree/json/gift.json");
        albero.buildTreeFromFile("chr_tree/json/albero.json");
        albero.addStar(stella);
        albero.addDecor(decors);

    glutMainLoop();
    return 0;
}
