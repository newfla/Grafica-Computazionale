#include "mesh.h"
#include "../dependencies/tinyxml2.h"
#include <map>
using namespace tinyxml2;

Mesh::Figure::Figure(){
}

void Mesh::Figure::draw(){
            glEnable(GL_LIGHTING);
            for(short int i = 0; i < faces.size(); i++)
            {
                    glBegin(GL_POLYGON);
                        Face temp= faces.at(i);
                        Point point=temp.getNormal();
                        float* normal=point.getCoords();
                      //  std::cout<<normal[0]<<": "<<normal[1]<<": "<<normal[2]<<std::endl;
                        glNormal3fv(normal);
                        for(short int j = 0; j < temp.vertex.size(); j++)
                            glVertex3fv(temp.vertex.at(j).getCoords());                    
                    glEnd();
            }
}

void Mesh::Figure::drawNormal(){
    int coff_normal=1;
    glDisable(GL_LIGHTING);
        for(short int i = 0; i < faces.size(); i++){
            Face temp= faces.at(i);
            Point point=temp.getNormal();
            float* normal=point.getCoords();
            float median[3]={0,0,0};
            for(short int j = 0; j < temp.vertex.size(); j++){
                glVertex3fv(temp.vertex.at(j).getCoords());
                median[0]+=temp.vertex.at(j).getCoords()[0];
                median[1]+=temp.vertex.at(j).getCoords()[1];
                median[2]+=temp.vertex.at(j).getCoords()[2];
                }
                median[0]/=(float)temp.vertex.size();
                median[1]/=(float)temp.vertex.size();
                median[2]/=(float)temp.vertex.size();
                glBegin(GL_LINES);
                    glColor3f(1,0,0);
                        glVertex3fv(median);
                    glColor3f(0,0,1);
                        glVertex3f(median[0]+normal[0]*coff_normal,median[1]+normal[1]*coff_normal,median[2]+normal[2]*coff_normal);
                glEnd();       
            }
}

void Mesh::Figure::addFaces(Mesh::Face face){
    faces.push_back(face);

}

void Mesh::Figure::buildPoints(const char* path){
    std::map<int, Point*> mappa;
    //Load XML description
        XMLDocument file;
        file.LoadFile(path);
        XMLNode* mesh=file.FirstChildElement("mesh");

        XMLElement* prova = mesh->FirstChildElement( "pointlist" );
    //Load Points description
        for(XMLElement* p = prova->FirstChildElement(); p; p=p->NextSiblingElement()){
            float x,y,z;
            int id;
            p->QueryIntAttribute("id",&id);
            p->QueryFloatAttribute("x",&x);
            p->QueryFloatAttribute("y",&y);
            p->QueryFloatAttribute("z",&z);
            mappa[id] = new Point(x,y,z);
        }
        
    //Build faces
        for(XMLElement* face=mesh->FirstChildElement("facelist")->FirstChildElement(); face; face=face->NextSiblingElement()){
            Face current;
            for(XMLElement* ref=face->FirstChildElement("ref"); ref; ref=ref->NextSiblingElement()){
                int node_id;
                ref->QueryIntText(&node_id);
                current.vertex.push_back(*(mappa.at(node_id)));
            }
            faces.push_back(current);
        }

}
