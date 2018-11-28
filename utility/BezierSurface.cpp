#include "mesh.h"

void Mesh::BezierSurface::addCheckpoint(Point x,float w){
    checkpoints.push_back(x.getCoords()[0]*w);
    checkpoints.push_back(x.getCoords()[1]*w);
    checkpoints.push_back(x.getCoords()[2]*w);
    checkpoints.push_back(w);
    center=NULL;
}

void Mesh::BezierSurface::addCheckpoint(float x, float y, float z,float w){
    checkpoints.push_back(x*w);
    checkpoints.push_back(y*w);
    checkpoints.push_back(z*w);
    checkpoints.push_back(w*w);
    center=NULL;
}

void Mesh::BezierSurface::drawCurve(){
    if(mode==GL_FILL){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    glMap2f(GL_MAP2_VERTEX_4, min[0], max[0], 4, order[0],
            min[1], max[1], 16, order[1], &checkpoints[0]);
    glEnable(GL_MAP2_VERTEX_4);

    glMapGrid2f(30.,0 ,1. ,30., 0, 1.);
    glEvalMesh2(mode,0, 30,0,30);
}

void Mesh::BezierSurface::testDrawCurve(){

    glMap2f(GL_MAP2_VERTEX_4, min[0], max[0], 4, order[0],
            min[1], max[1], 16, order[1], &checkpoints[0]);
    glEnable(GL_MAP2_VERTEX_4);

    glPushMatrix();

        for (int j = 0; j <= 8; j++) {
            glBegin(GL_LINE_STRIP);
                for (int i = 0; i <= 30; i++) 
                    glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
            glEnd();

            glBegin(GL_LINE_STRIP);
                for (int i = 0; i <= 30; i++) 
                    glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
            glEnd();
        }

    glPopMatrix();
}

void Mesh::BezierSurface::buildCenter(){
    float acc[3]={0,0,0};
    float tot=checkpoints.size()/4;
    
    for(int i = 0; i < checkpoints.size(); i+=4)
    {
        acc[0]+=checkpoints[i];
        acc[1]+=checkpoints[i+1];
        acc[2]+=checkpoints[i+2];
    }
    acc[0]/=tot;
    acc[1]/=tot;
    acc[2]/=tot;

    center=new Point(acc[0],acc[1],acc[2]);    
}

Mesh::BezierSurface::BezierSurface(GLenum mode,std::vector<float> order, std::vector<float> min, std::vector<float> max){
    this->mode=mode;
    this->order=order;
    this->min=min ;
    this->max=max;
}