#include "tree.h"
#include "../dependencies/json.hpp"
#include<fstream>
using json = nlohmann::json;

Tree::Gift::Gift(vector<float>colorRibbon,vector<float>colorBox,vector<float>scale,float cube,Mesh::NurbsCurve* ribbon){
    this->colorRibbon=colorRibbon;
    this->colorBox=colorBox;
    this->side=cube;
    this->ribbon=ribbon;
    this->scale=scale;
}

vector<Tree::Gift> Tree::Gift::buildGiftsFromFile(const char* path, Tree::TreeTextureContainer* container){
    //VAR DECLARATION
        vector<Tree::Gift> gifts;
        bool texture=false;

    //LOAD FILE
        std::ifstream i(path);
        json j;
        i >> j;

    for(int i = 0; i < j["gift"].size(); i++){
         vector<float> color,scale,colorRibbon;

        //FIND COLOR BOX
            color.push_back(j["gift"][i]["colorBox"][0]);
            color.push_back(j["gift"][i]["colorBox"][1]);
            color.push_back(j["gift"][i]["colorBox"][2]);
        //SCALE FACTOR
            scale.push_back(j["gift"][i]["scale"][0]);
            scale.push_back(j["gift"][i]["scale"][1]);
            scale.push_back(j["gift"][i]["scale"][2]);

        //FIND COLOR RIBBON
            colorRibbon.push_back(j["gift"][i]["colorRibbon"][0]);
            colorRibbon.push_back(j["gift"][i]["colorRibbon"][1]);
            colorRibbon.push_back(j["gift"][i]["colorRibbon"][2]);
        //FIND TEXTURE
            if(j["texture"]){
            texture=true;
            string temp=j["path"];
            container->initTexture(temp.c_str(),3,true);
        }
            
        Tree::Gift gif=Gift(colorRibbon,color,scale,j["gift"][i]["side"],new Mesh::NurbsCurve("chr_tree/json/ribbon.json"));

        if(texture)
            gif.texture=true;
        gifts.push_back(gif);
    }
    return gifts;
}

void Tree::Gift::draw(float x, float y, Tree::TreeTextureContainer* container) const{

    //SET COLOR RIBBON
        glPushMatrix();
        //glRotatef(270,1,2/3,0);
            glTranslatef(x,-y+(side/2.),0);
            glRotatef(270,0,1,0);
            glScalef(scale[0],scale[1],scale[2]);    
            
                //DRAW RIBBON
                ChrTree::resetMaterial();
                if(!texture){
                    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,&colorRibbon[0]);
                    glPushMatrix();
                        glTranslatef(0,0,(double)side/2+0.00000000000000002);
                        glScalef(0.05,0.05,0.05);
                        ribbon->drawCurve();
                    glPopMatrix();
                }
                //DRAW BOX
                ChrTree::resetMaterial();
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,&colorBox[0]);

               if(texture){
                    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,new float[3]{1,1,1});
                    glBindTexture(GL_TEXTURE_2D,container->getPos(3));
               }
                glutSolidCube(side);
        glPopMatrix();
}