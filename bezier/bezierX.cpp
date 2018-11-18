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
    vector<BezierCurve> curve;

//LAST CONTROL POINT INSERTED
    Point* last;

//LEFT CLICK POSITION
    float* click;

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    for(int i = 0; i < curve.size(); i++)
    {
        glColor3f(1,0,0);
            curve.at(i).drawCheckpoints();
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
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
        float* pos=scaleToScreen(x,y);
        delete last;
        last=new Point(pos[0],pos[1],0);
        curve.back().addCheckpoint(*last);
    }
    else if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        click=scaleToScreen(x,y);
    }
    else if (button==GLUT_LEFT_BUTTON && state==GLUT_UP){
        float* pos=scaleToScreen(x,y);
        Point who=Point(click[0],click[1],0);
        Point newer=Point(pos[0],pos[1],0);
        click=NULL;
        
        for(int i = 0; i < curve.size(); i++)
            curve.at(i).modCheckpoint(who,newer);        
    }
    glutPostRedisplay();
}

void keyboardListner(unsigned char key, int x, int y){
    BezierCurve curva;
    switch(key){
        case ' ':
            curva.addCheckpoint(*last);
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
    
    //ADD FIRST BEZIER CURVE
        curve.push_back(BezierCurve());
    glutMainLoop();
    return 0;
}
