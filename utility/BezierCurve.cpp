#include "mesh.h"
using namespace std;

void Mesh::BezierCurve::addCheckpoint(Point x){
    checkpoints.push_back(x.getCoords()[0]);
    checkpoints.push_back(-x.getCoords()[1]);
    checkpoints.push_back(x.getCoords()[2]);  
}

void Mesh::BezierCurve::addCheckpoint(float x, float y, float z){
    checkpoints.push_back(x);
    checkpoints.push_back(-y);
    checkpoints.push_back(z);
}

void Mesh::BezierCurve::modCheckpoint(Point who, Point newer){
    for(int i = 0; i < checkpoints.size(); i+=3)
    {
        for(short j = 0; j < 3; j++)
        {
            if(!checkInRange(who.getCoords()[j],checkpoints.at(i+j),j))
                break;
            else if(j==2){
                checkpoints.at(i)=newer.getCoords()[0];
                checkpoints.at(i+1)=-newer.getCoords()[1];
                checkpoints.at(i+2)=newer.getCoords()[2];
            }
        }
    }
}

bool Mesh::BezierCurve::checkInRange(float val, float cord,short invert){
    float a=cord-cube*2;
    float b=cord+cube*2;
    if (invert==1)
        val*=-1.0;
    if(val>=a && val<=b)
        return true;
    return false;
}

void Mesh::BezierCurve::drawCurve(){
    if(checkpoints.size()>0){
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, checkpoints.size()/3, &checkpoints[0]);
        glEnable(GL_MAP1_VERTEX_3);
        glMapGrid1f(30, 0, 1);
        glEvalMesh1(GL_LINE, 0, 30);
    }
}

void Mesh::BezierCurve::drawCheckpoints(){
    for(int i = 0; i < checkpoints.size()/3; i++)
    {
        int j=3*i;
        glPushMatrix();
            glTranslatef(checkpoints.at(j)+cube,checkpoints.at(j+1)+cube,checkpoints.at(j+2)+cube);
            glutSolidCube(cube);
        glPopMatrix();
    }
}


