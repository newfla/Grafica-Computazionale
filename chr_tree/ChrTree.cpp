#include "tree.h"
#include "../dependencies/json.hpp"
#include<fstream>
#include  <random>
#include  <iterator>
using json = nlohmann::json;
using namespace Mesh;

void Tree::ChrTree::buildTreeFromFile(const char* path){
    char a[2];

    //LOAD FILE
        std::ifstream i(path);
        json j;
        i >> j;

    //PARAM TRONCO
        tronco= new GluSolidFigure(GLU_FILL,GLU_OUTSIDE,GLU_FLAT);
        baseTronco= new GluSolidFigure(GLU_FILL,GLU_OUTSIDE,GLU_FLAT);
        paramTronco.push_back(j["tronco"]["radius"]);
        paramTronco.push_back(j["tronco"]["height"]);
        paramTronco.push_back(j["tronco"]["slices"]);
        paramTronco.push_back(j["tronco"]["stacks"]);
        paramTronco.push_back(j["tronco"]["color"][0]);
        paramTronco.push_back(j["tronco"]["color"][1]);
        paramTronco.push_back(j["tronco"]["color"][2]);

    //OTHER PARAM CONI
        paramCono.push_back(j["cono"]["tot"]);
        paramCono.push_back(j["cono"]["radius"]);
        paramCono.push_back(j["cono"]["height"]);
        paramCono.push_back(j["cono"]["slices"]);
        paramCono.push_back(j["cono"]["stacks"]);
    //COLOR CONI
        vector<float> primary, dark, light;

        dark.push_back(j["cono"]["colorDark"][0]);
        dark.push_back(j["cono"]["colorDark"][1]);
        dark.push_back(j["cono"]["colorDark"][2]);

        light.push_back(j["cono"]["colorLight"][0]);
        light.push_back(j["cono"]["colorLight"][1]);
        light.push_back(j["cono"]["colorLight"][2]);

        primary.push_back(j["cono"]["colorPrimary"][0]);
        primary.push_back(j["cono"]["colorPrimary"][1]);      
        primary.push_back(j["cono"]["colorPrimary"][2]);

        color.push_back(dark);
        color.push_back(primary);
        color.push_back(light);
}

void Tree::ChrTree::draw() const{
    
    //DRAW TRONCO
        glColor3fv(&paramTronco[4]);
        glPushMatrix();
            glRotatef(90,1,0,0);
            tronco->drawCylinder(paramTronco[0],paramTronco[0],paramTronco[1],(int)paramTronco[2],(int)paramTronco[3]);
        glPopMatrix();

    //DRAW BASE TRONCO
        glColor3fv(&paramTronco[4]);
        glPushMatrix();
            glTranslatef(0,-paramTronco[1],0);
            glRotatef(90,1,0,0);
            baseTronco->drawDisk(0,paramTronco[0],(int)paramTronco[2],(int)paramTronco[3]);
        glPopMatrix();

    //DRAW CONI
    float height=paramCono[2]/paramCono[0];
    float spostamento=0;
        for(int i = 0; i < (int)paramCono[0]; i++)
        {
                glColor3fv(&(color[2])[0]);
                glPushMatrix();
                    glTranslatef(0,spostamento,0);
                    glRotatef(270,1,0,0);
                        glutSolidCone(paramCono[1]-spostamento/2.,height,(int)paramCono[3],(int)paramCono[4]);                       
                glPopMatrix();
                //ADD PALLINE
                    /*vector<Decor>::const_iterator randIt = palline.begin();
                    std::advance(randIt, std::rand() % palline.size());*/
                for(int j = 30; j <= 360; j+=30)
                {
                    glPushMatrix();
                        glRotatef(j-30,0,1,0);
                        palline[i%palline.size()==0].draw(paramCono[1]-spostamento/2,spostamento);
                    glPopMatrix();

                    glPushMatrix();
                        glRotatef(j-15.,0,1,0);
                            palline[i+1%palline.size()==0].draw(paramCono[1]-spostamento/2,spostamento);
                    glPopMatrix();  
                }
                spostamento+=0.4;
            }
        
    //DRAW STELLA
        glPushMatrix();
            glTranslatef(0,spostamento,0);
            stella.draw();
        glPopMatrix();        

}

void Tree::ChrTree::addStar(Tree::Star star){
    stella=star;
}

void Tree::ChrTree::addDecor(vector<Tree::Decor> decor){
   
   for(int i = 0; i < decor.size(); i++)
      palline.push_back(decor[i]);
}

float Tree::ChrTree::getTroncoHeight(){
    return paramTronco[1];
}