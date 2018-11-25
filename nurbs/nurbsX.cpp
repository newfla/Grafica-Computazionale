#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../utility/mesh.h"
using namespace Mesh;

//WINDOW PARAM
    float width=700, heigth=700;

//BEZIER CURVE
    vector<NurbsCurve> curve;

//LAST CONTROL POINT INSERTED
    Point* last;

//LEFT CLICK POSITION
    float* click;

//RADIANS CONVERSION
   float degrees=180/(3.14*3);


float angleMovement(Point old, Point newer){
    float x=newer.getCoords()[0]-old.getCoords()[0],
        y=-(newer.getCoords()[1]-old.getCoords()[1]);
    float temp=atan2f(y,x);
    temp*=degrees;
    if(temp<0)
        temp+=360;
    return temp;
}

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    for(int i = 0; i < curve.size(); i++)
    {
        glColor3f(1,0,0);
            curve.at(i).drawCheckpoints();
            curve.at(i).drawHandles();
        glColor3f(0,0,1);
            curve.at(i).drawCurve();
    }
    glFlush();    
}

float* scaleToScreen(int x, int y){
    float * value= (float*)calloc(2, sizeof(float));
    value[0]=((2.0*(float)x)/glutGet(GLUT_WINDOW_WIDTH))-1;
    value[1]=((2.0*(float)y)/glutGet(GLUT_WINDOW_HEIGHT))-1;
    return value;
}

void mouseListener(int button, int state, int x, int y){
    if(button==GLUT_RIGHT_BUTTON && state==0){
        float* pos=scaleToScreen(x,y);
        delete last;
        last=new Point(pos[0],pos[1],0);
        curve.back().addCheckpoint(*last,1);
    }
    else if (button==GLUT_LEFT_BUTTON && state==0){
        click=scaleToScreen(x,y);
    }
    else if (button==GLUT_LEFT_BUTTON && state==1){
        float* pos=scaleToScreen(x,y);
        Point who=Point(click[0],click[1],0);
        Point newer=Point(pos[0],pos[1],0);
        float weight=1;
        
        for(int i = 0; i < curve.size(); i++){
            switch(glutGetModifiers()){
                case GLUT_ACTIVE_SHIFT:
                    weight=8*(newer.getCoords()[0]-who.getCoords()[0]);
                    //cout<<weight<<endl;
                    curve.at(i).modWeight(who,weight);
                    break;
                
                case GLUT_ACTIVE_CTRL:
                    curve.at(i).modUniform(who,angleMovement(who,newer));
                    break;

                default:
                    curve.at(i).modCheckpoint(who,newer);
                    break;
                
            } 
        }
    }
    glutPostRedisplay();
}

void keyboardListner(unsigned char key, int x, int y){
    NurbsCurve curva(50,2);
    switch(key){
        case ' ':
            curva.addCheckpoint(*last,1);
            curve.push_back(curva);
            break;
        
        case 'N':
        case 'n':
            curve.push_back(curva);
            break;
        default:
            delete &curva;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Bezier_X");
        glutMouseFunc(mouseListener);
        glutKeyboardFunc(keyboardListner);
        glutDisplayFunc(redraw);
    
    //ADD FIRST NURBS CURVE
        curve.push_back(NurbsCurve(50,2));
    glutMainLoop();
    return 0;
}
