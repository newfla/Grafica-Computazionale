#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../utility/mesh.h"
using namespace Mesh;

//WINDOW PARAM
    float width=700, heigth=700;

//Point vector
vector<Point> points;

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
        glColor3f(1,0,0);
        for(int i=0; i<points.size(); i++){
            glVertex2fv(points.at(i).getCoords());
        }
    glEnd();
    glFlush();
}

Mesh::Point casteljau(vector<Mesh::Point> checkpoints, float t){
    vector<Mesh::Point> result;
    int n=checkpoints.size();
    
    for(int i = 0; i < n; i++)
        result.push_back(checkpoints.at(i));
    
    for(int  r = 1; r < n; r++)
    {
        for(int i = 0; i < n-r; i++)
        {
            for(int dim = 0; dim < 3; dim++)
                result[i].getCoords()[dim]=(1.0-t)*result[i].getCoords()[dim] + t*result[i+1].getCoords()[dim];
        }
    }
    return result.at(0);
}

int main(int argc, char** argv) {
    //GLUT INIT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowPosition(300,100);
        glutInitWindowSize(width,heigth);
        glutCreateWindow("Bezier_1");
        glutDisplayFunc(redraw);

    //CREATE VECTOR
        float step=0.01;
        vector<Point> checkpoints;
        checkpoints.push_back(Point(-4.0, -4.0, 0.0));
        checkpoints.push_back(Point(-2.0, 4.0, 0.0));
        checkpoints.push_back(Point(2.0, -4.0, 0.0));
        checkpoints.push_back(Point( 4.0, 4.0, 0.0));
        
        for(float i = 0; i < 1; i+=step)
            points.push_back(casteljau(checkpoints,i));
        

    glutMainLoop();
    return 0;
}
