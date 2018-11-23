#include "mesh.h"
using namespace std;

void Mesh::NurbsCurve::addCheckpoint(Point x, float w){
    checkpoints.push_back(x.getCoords()[0]*w);
    checkpoints.push_back(-x.getCoords()[1]*w);
    checkpoints.push_back(x.getCoords()[2]*w);
    checkpoints.push_back(w);

    float step=1./(checkpoints.size()/4)+degree-1;
    knots.clear();
    
    for(int i = 0; i < (checkpoints.size()/4)+degree; i++)
        this->addKnot((float)i*step);
}

void Mesh::NurbsCurve::addCheckpoint(float x, float y, float z, float w){
    checkpoints.push_back(x*w);
    checkpoints.push_back(y*w);
    checkpoints.push_back(z*w);
    checkpoints.push_back(w);
}

void Mesh::NurbsCurve::modCheckpoint(Point who, Point newer){
    for(int i = 0; i < checkpoints.size(); i+=4)
    {
        for(short j = 0; j < 4; j++)
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

void Mesh::NurbsCurve::modWeight(Point who, float weight){
    for(int i = 0; i < checkpoints.size(); i+=4)
    {
        for(short j = 0; j < 4; j++)
        {
            if(!checkInRange(who.getCoords()[j],checkpoints.at(i+j),j))
                break;
            else if(j==2){
                checkpoints.at(i+3)+=weight;
            }
        }
    }
}

bool Mesh::NurbsCurve::checkInRange(float val, float cord,short invert){
    float a=cord-cube*2;
    float b=cord+cube*2;
    if (invert==1)
        val*=-1.0;
    if(val>=a && val<=b)
        return true;
    return false;
}

void Mesh::NurbsCurve::addKnot(float k){
    knots.push_back(k);
}


void Mesh::NurbsCurve::drawCurve(){
    gluBeginCurve(nurbs);
        glColor3f(0,0,1);
        gluNurbsCurve(nurbs,knots.size(),&knots[0],4,&checkpoints[0],degree,GL_MAP1_VERTEX_4);
    gluEndCurve(nurbs);

}

void Mesh::NurbsCurve::drawCheckpoints(){
    for(int i = 0; i < checkpoints.size()/4; i++)
    {
        int j=4*i;
        glPushMatrix();
            glTranslatef(checkpoints.at(j),checkpoints.at(j+1),checkpoints.at(j+2)+cube);
            glutSolidCube(cube);
        glPopMatrix();
    }
}

void Mesh::NurbsCurve::drawHandles(){
    for(int i = 0; i < checkpoints.size()/4; i++){
        int j=4*i;
        glBegin(GL_LINES);
            glVertex3f(checkpoints.at(j)-(3*cube*checkpoints.at(j+3)), checkpoints.at(j+1), checkpoints.at(j+2));
            glVertex3f(checkpoints.at(j)+(3*cube*checkpoints.at(j+3)), checkpoints.at(j+1), checkpoints.at(j+2));
        glEnd();
    }

}



GLUnurbsObj* Mesh::NurbsCurve::getNurb(){
    return nurbs;
}

void Mesh::NurbsCurve::setDegree(int deg){
    if(degree==0)
        degree=deg+1;
}

GLvoid Mesh::NurbsCurve::printError(GLenum errorCode){
    const GLubyte* estring;
    estring=gluErrorString(errorCode);
    cerr<<estring<<endl;
}

Mesh::NurbsCurve::NurbsCurve(int step, int degree){
        nurbs=gluNewNurbsRenderer();
        setDegree(degree);
        gluNurbsProperty(nurbs,GLU_U_STEP,step);
        gluNurbsProperty(nurbs, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
        gluNurbsCallback(nurbs,GLU_ERROR, (_GLUfuncptr)Mesh::NurbsCurve::printError);
}

