#include "tree.h"
#include "../dependencies/json.hpp"
#include<fstream>
using json = nlohmann::json;

void Tree::Star::buildFromFile(const char* path){

    //LOAD FILE
        std::ifstream i(path);
        json j;
        i >> j;

    //FIND COLOR
        color.push_back(j["color"][0]);
        color.push_back(j["color"][1]);
        color.push_back(j["color"][2]);

    //SCALE FACTOR
        scale.push_back(j["scale"][0]);
        scale.push_back(j["scale"][1]);
        scale.push_back(j["scale"][2]);
    
    //OTHER PARAMS
        tot=j["tot"];
        radius=j["radius"];
        height=j["height"];
        slices=j["slices"];
        stacks=j["stacks"];
}

void Tree::Star::draw() const{
    //SET COLOR FOR ALL SPIKES
       // glColor3fv(&color[0]);
       ChrTree::resetMaterial();
       glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,&color[0]);

    //DRAW ALL SPIKES
            float degree=360./(float)tot;
        glPushMatrix();
            glTranslatef(0,3.*height/7. ,-0.2);
            glPushMatrix();
                glRotatef(180,1,0,0);
                    glLightfv(GL_LIGHT2,GL_POSITION, new float[4]{0,height,-radius,0});
                    glLightfv(GL_LIGHT3,GL_POSITION, new float[4]{0,height/2,-radius,0});
                    glLightfv(GL_LIGHT4,GL_POSITION, new float[4]{0,height,-radius,0});
                    glLightfv(GL_LIGHT5,GL_POSITION, new float[4]{0,height/2,-radius,0});
                    glLightfv(GL_LIGHT6,GL_POSITION, new float[4]{0,height,-radius,0});
                    glLightfv(GL_LIGHT7,GL_POSITION, new float[4]{0,height/2,-radius,0});
            glPopMatrix();
            
            glRotatef(90,1,0,0);
            glScalef(scale[0],scale[1],scale[2]);    
                for(int i = 0; i <tot; i++)
                {
                    glPushMatrix();
                        glRotatef(degree*(float)i,0,1,0);
                            glutSolidCone(radius,height,slices,stacks);
                    glPopMatrix();
                }
        glPopMatrix();

}

