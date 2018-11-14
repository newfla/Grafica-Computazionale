#include "mesh.h"
#include "../dependencies/tinyxml2.h"
#include <map>
using namespace tinyxml2;

Mesh::Figure::Figure(){
    buildPoints();
}

void Mesh::Figure::draw(){
            int coff_normal=1;
            for(short int i = 0; i < faces.size(); i++)
            {
                float median[3]={0,0,0};
                glEnable(GL_LIGHTING);
                    glBegin(GL_POLYGON);
                        Face temp= faces.at(i);
                        Point point=temp.getNormal();
                        float* normal=point.getCoords();
                       // std::cout<<normal[0]<<": "<<normal[1]<<": "<<normal[2]<<std::endl;
                        glNormal3fv(normal);
                        
                        for(short int j = 0; j < temp.vertex.size(); j++){
                            glVertex3fv(temp.vertex.at(j).getCoords());
                            median[0]+=temp.vertex.at(j).getCoords()[0];
                            median[1]+=temp.vertex.at(j).getCoords()[1];
                            median[2]+=temp.vertex.at(j).getCoords()[2];
                        }
                    glEnd();

                median[0]/=(float)temp.vertex.size();
                median[1]/=(float)temp.vertex.size();
                median[2]/=(float)temp.vertex.size();

                glDisable(GL_LIGHTING);
                    glBegin(GL_LINES);
                        glColor3f(1,0,0);
                        glVertex3fv(median);
                        glColor3f(0,0,1);
                        glVertex3f(median[0]+normal[0]*coff_normal,median[1]+normal[1]*coff_normal,median[2]+normal[2]*coff_normal);
                    glEnd(); 
                
            }
        
}


void Mesh::Figure::buildPoints(){
    std::map<int, Point*> mappa;
    //Load XML description
        XMLDocument file;
        file.LoadFile("casa/descr.xml");
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
            cout<<x<<" "<<y<<" "<<z<<endl;
            mappa[id] = new Point(x,y,z);
        }
        
    //Build faces
        for(XMLElement* face=mesh->FirstChildElement("facelist")->FirstChildElement(); face; face=face->NextSiblingElement()){
            Face current;
            cout<<"Faccia x\n";
            for(XMLElement* ref=face->FirstChildElement("ref"); ref; ref=ref->NextSiblingElement()){
                cout<<"fff\n";
                int node_id;
                ref->QueryIntText(&node_id);
                cout<<node_id<<endl;
                current.vertex.push_back(*(mappa.at(node_id)));
            }
            faces.push_back(current);
        }

}
