#include "tree.h"
#include "../dependencies/json.hpp"
#include<fstream>
using json = nlohmann::json;

Tree::Decor::Decor(float radius, int slices, int stacks, vector<float>color, vector<float>scale,int pos){
    this->radius=radius;
    this->slices=slices;
    this->stacks=stacks;
    this->color=color;
    this->scale=scale;
    this->pos=pos;
}

void Tree::Decor::draw(float x, float y,Tree::TreeTextureContainer* container) const{
    //SET COLOR
        ChrTree::resetMaterial();
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,128);    
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,&color[0]);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,new float[4]{1,1,1,1});

    //CHECK TEXTURE
        if(pos!=0){
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,new float[3]{1,1,1});
                    glBindTexture(GL_TEXTURE_2D,container->getPos(pos));
        }
        
    //DRAW DECOR
        glPushMatrix();
            glTranslatef(x,y,0);
            glScalef(scale[0],scale[1],scale[2]);
                glutSolidSphere(radius,slices,stacks);
        glPopMatrix();
}

vector<Tree::Decor> Tree::Decor::buildDecorsFromFile(const char* path,Tree::TreeTextureContainer* container){
    
    //VAR DECLARATION
        int slices,stacks;
        vector<Decor> decors;

    //LOAD FILE
        std::ifstream i(path);
        json j;
        i >> j;

    //OTHER PARAMS
        slices=j["slices"];
        stacks=j["stacks"];

    
    for(int i = 0; i < j["decor"].size(); i++){
        vector<float> color,scale;
        int pos=0;
        //FIND COLOR
            color.push_back(j["decor"][i]["color"][0]);
            color.push_back(j["decor"][i]["color"][1]);
            color.push_back(j["decor"][i]["color"][2]);
        //SCALE FACTOR
            scale.push_back(j["decor"][i]["scale"][0]);
            scale.push_back(j["decor"][i]["scale"][1]);
            scale.push_back(j["decor"][i]["scale"][2]);

        //CHECK TEXTURE PARAM
        if(j["decor"][i]["texture"]){

            pos=j["decor"][i]["pos"];
            string temp=j["decor"][i]["path"];
            container->initTexture(temp.c_str(),pos,true);
        }
        decors.push_back(Decor(j["decor"][i]["rays"],slices,stacks,color,scale,pos));
    }
    

    return decors;
    
}