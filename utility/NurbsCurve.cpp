#include "mesh.h"
#include "../dependencies/json.hpp"
#include<fstream>
using namespace std;
using json = nlohmann::json;

void Mesh::NurbsCurve::addCheckpoint(Point x, float w){
    checkpoints.push_back(x.getCoords()[0]*w);
    checkpoints.push_back(x.getCoords()[1]*w);
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
               // cout<< checkpoints.at(i+3)<<endl<<"-----"<<endl;
            }
        }
    }
}

void Mesh::NurbsCurve::modUniform(Point who,float angleMod){
    int i=whoModUniform(who,angleMod);
    if(i!=-1){
        if(modUniformGraphic(i,angleMod))
            modUniformKnots(i/4,angleMod);
    }
}

bool Mesh::NurbsCurve::modUniformGraphic(int i,float angleMod){
        float angle=0, back=0;
        if(angleMap.find(i)!=angleMap.end())
            angle=angleMap[i];
        back=angle;
        angle+=angleMod;
        angle=(int)angle%360;
        if(angle>=90 && angle<=270){
            angleMap[i]=back;
            return false;
        }
        angleMap[i]=angle;
        return true;
}

void Mesh::NurbsCurve::modUniformKnots(int i,float angleMod){
    if(angleMod<=90)
        for(short j =i+degree-1; j>=i+degree/2; j--)
    {
        cout<<"Old: "<<knots[j]<<endl;
        knots[j]+= (knots[j+1]-knots[j])*(angleMod/90.);
        cout<<"New: "<<knots[j]<<endl<<"-----\n";
    }
    else{
        for(short j=i+degree/2; j>=i; j--)
        {
            cout<<"Old: "<<knots[j]<<endl;
            knots[j]-= (knots[j]-knots[j-1])*(angleMod/360.);
            cout<<"New: "<<knots[j]<<endl<<"-----\n";
        }
    }
}

int Mesh::NurbsCurve::whoModUniform(Point who,float angleMod){
    bool founded=false;
    int i=0;
    for(i = 0; i < checkpoints.size(); i+=4)
    {
        for(short j = 0; j < 4; j++)
        {
            if(!checkInRange(who.getCoords()[j],checkpoints.at(i+j),j))
                break;
            else if(j==2){
                founded=true;
                break;
            }
        }
        if(founded)
           return i;
    }
    return -1;
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
    for(int i = 0; i < checkpoints.size(); i+=4){
        //COLOR SETTING
            if(checkpoints.at(i+3)<0)
                glColor3f(1,0,0);
            else
                glColor3f(0,1,0);
                
        //CHECK HANDLE ROTATION 1        
            if(angleMap.find(i)!=angleMap.end()){
                cout<<"angolo: "<<angleMap[i]<<endl;
                glPushMatrix();
                    glTranslatef(checkpoints.at(i),checkpoints.at(i+1),0);
                    glRotatef(angleMap[i],0,0,1);
                    glTranslatef(-checkpoints.at(i),-checkpoints.at(i+1),0);
            }

        //HANDLE DRAW
            glBegin(GL_LINES);
                glVertex3f(checkpoints.at(i)-(3*cube*checkpoints.at(i+3)), checkpoints.at(i+1), checkpoints.at(i+2));
                glVertex3f(checkpoints.at(i)+(3*cube*checkpoints.at(i+3)), checkpoints.at(i+1), checkpoints.at(i+2));
            glEnd();

        //CHECK HANDLE ROTATION 2   
            if(angleMap.find(i)!=angleMap.end())
                glPopMatrix();
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
   // cerr<<estring<<endl;
}

Mesh::NurbsCurve::NurbsCurve(int step, int degree){
        nurbs=gluNewNurbsRenderer();
        setDegree(degree);
        gluNurbsProperty(nurbs,GLU_U_STEP,step);
        gluNurbsProperty(nurbs, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
        gluNurbsCallback(nurbs,GLU_ERROR, (_GLUfuncptr)Mesh::NurbsCurve::printError);
}

Mesh::NurbsCurve::NurbsCurve(const char* jsonPath){
    //LOAD FILE
        std::ifstream i(jsonPath);
        json j;
        i >> j;

    //STANDARD INIT NURBS
        nurbs=gluNewNurbsRenderer();
        setDegree(j["degree"]);
        gluNurbsProperty(nurbs,GLU_U_STEP,j["discretization"]);
        gluNurbsProperty(nurbs, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);

    //ADD CHECKPOINT
        vector<float> checks=j["controlPoints"];
        for(int i = 0; i < checks.size(); i+=4)
            addCheckpoint(checks.at(i),checks.at(i+1),checks.at(i+2),checks.at(i+3));
        

    //ADD KNOTS
        vector<float> knots=j["knots"];
        for(int i = 0; i < knots.size(); i++)
           addKnot(knots.at(i));
        
}

