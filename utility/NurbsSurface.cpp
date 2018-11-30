#include"mesh.h"
#include "../dependencies/json.hpp"
#include<fstream>
using json = nlohmann::json;

Mesh::NurbsSurface::NurbsSurface(GLenum displayMode, int uStep, int vStep, GLfloat samplingMethod,int uOrder, int vOrder){
    nurbs=gluNewNurbsRenderer();
    gluNurbsProperty(nurbs,GLU_U_STEP,uStep);
    gluNurbsProperty(nurbs,GLU_V_STEP,vStep);
    gluNurbsProperty(nurbs,GLU_DISPLAY_MODE,displayMode);
    if(displayMode==GL_FILL){
        glEnable(GL_AUTO_NORMAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    order[0]=uOrder;
    order[1]=vOrder;
    gluNurbsCallback(nurbs,GLU_ERROR, (_GLUfuncptr)Mesh::NurbsCurve::printError);
}

Mesh::NurbsSurface::NurbsSurface(){
    nurbs=gluNewNurbsRenderer();
    gluNurbsCallback(nurbs,GLU_ERROR, (_GLUfuncptr)Mesh::NurbsCurve::printError);
    glEnable(GL_AUTO_NORMAL);
    order[0]=1;
    order[1]=1;
}

void Mesh::NurbsSurface::buildFromFile(const char* path){
    //LOAD FILE
        std::ifstream i(path);
        json j;
        i >> j;

    //OTHER PARAMS    
    gluNurbsProperty(nurbs,GLU_U_STEP,j["uStep"]);
    gluNurbsProperty(nurbs,GLU_V_STEP,j["vStep"]);
    gluNurbsProperty(nurbs,GLU_DISPLAY_MODE,GL_FILL);
    order[0]+=(int)j["degree"];
    order[1]+=(int)j["degree"];

    //CONTROL POINTS
    vector<float> checks=j["controlPoints"];
        for(int i = 0; i < checks.size(); i+=4)
            addCheckpoint(checks.at(i),checks.at(i+1),checks.at(i+2),checks.at(i+3));

    //ADD KNOTS
        vector<float> knots=j["knots"];
        for(int i = 0; i < knots.size(); i++)
           addKnot(knots.at(i));
}

void Mesh::NurbsSurface::addCheckpoint(Point x, float w){
    checkpoints.push_back(x.getCoords()[0]*w);
    checkpoints.push_back(x.getCoords()[1]*w);
    checkpoints.push_back(x.getCoords()[2]*w);
    checkpoints.push_back(w);

}

void Mesh::NurbsSurface::addCheckpoint(float x, float y, float z, float w){
    checkpoints.push_back(x*w);
    checkpoints.push_back(y*w);
    checkpoints.push_back(z*w);
    checkpoints.push_back(w);
}

void Mesh::NurbsSurface::addUKnot(float k){
    uKnots.push_back(k);
}

void Mesh::NurbsSurface::addVKnot(float k){
    vKnots.push_back(k);
}

void Mesh::NurbsSurface::addKnot(float k){
    addUKnot(k);
    addVKnot(k);
}

void Mesh::NurbsSurface::addTrimPwl2f(vector<float>trim){
    trimsPwl.push_back(trim);
}

void Mesh::NurbsSurface::addTrimCurve2f(vector<float> trim){
    trimsCurve.push_back(trim);
}

void Mesh::NurbsSurface::drawCurve(){
    gluBeginSurface(nurbs);
        gluNurbsSurface(nurbs,uKnots.size(),&uKnots[0],vKnots.size(),&vKnots[0],16,4,&checkpoints[0],order[0],order[1],GL_MAP2_VERTEX_4);
        
        for(int i = 0; i < trimsPwl.size(); i++)
        {
            vector<float> vec=trimsPwl[i];
            gluBeginTrim(nurbs);
                gluPwlCurve(nurbs,vec.size()/2,&vec[0] ,2,GLU_MAP1_TRIM_2);
            gluEndTrim(nurbs);
        }

        for(int i = 0; i < trimsCurve.size(); i++)
        {
            vector<float> vec=trimsCurve[i];
            vector<float>knot;
            float step=0.8/(((float)vec.size()/2.)+2.);
            for(int i = 0; i < (vec.size()/2)+3; i++){
                knot.push_back((float)i*step);
                cout<<knot[i]<<endl;
            }
                
            gluBeginTrim(nurbs);
                gluNurbsCurve(nurbs,knot.size(),&knot[0],2,&vec[0] ,3,GLU_MAP1_TRIM_2);
            gluEndTrim(nurbs);
        }
    gluEndSurface(nurbs);
}
