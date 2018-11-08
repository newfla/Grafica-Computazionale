#include "mesh.h"
using namespace std;
Mesh::Figure::Figure(){
    vector<Point> points=buildPoints();
    Face anteriore,posteriore, pavimento, laterale_dx,
        laterale_sx, tetto_sx, tetto_dx;
        
    //ISTANZIAZIONE FACCIA FRONTALE
        anteriore.vertex.push_back(points.at(5));
        anteriore.vertex.push_back(points.at(6));
        anteriore.vertex.push_back(points.at(7));
        anteriore.vertex.push_back(points.at(8));
        anteriore.vertex.push_back(points.at(9));


    //ISTANZIAZIONE FACCIA POSTERIORE
        posteriore.vertex.push_back(points.at(0));
        posteriore.vertex.push_back(points.at(1));
        posteriore.vertex.push_back(points.at(2));
        posteriore.vertex.push_back(points.at(3));
        posteriore.vertex.push_back(points.at(4));

    //ISTANZIAZIONE FACCIA LATERALE DX
        laterale_dx.vertex.push_back(points.at(1));
        laterale_dx.vertex.push_back(points.at(2));
        laterale_dx.vertex.push_back(points.at(7));
        laterale_dx.vertex.push_back(points.at(6));

    //ISTANZIAZIONE FACCIA LATERALE SX
        laterale_sx.vertex.push_back(points.at(0));
        laterale_sx.vertex.push_back(points.at(4));
        laterale_sx.vertex.push_back(points.at(9));
        laterale_sx.vertex.push_back(points.at(5));

    //ISTANZIAZIONE TETTO DX
        tetto_dx.vertex.push_back(points.at(2));
        tetto_dx.vertex.push_back(points.at(3));
        tetto_dx.vertex.push_back(points.at(8));
        tetto_dx.vertex.push_back(points.at(7));

    //ISTANZIAZIONE TETTO SX
        tetto_sx.vertex.push_back(points.at(3));
        tetto_sx.vertex.push_back(points.at(4));
        tetto_sx.vertex.push_back(points.at(9));
        tetto_sx.vertex.push_back(points.at(8));

    //ISTANZIAZIONE PAVIMENTO
        pavimento.vertex.push_back(points.at(0));
        pavimento.vertex.push_back(points.at(5));
        pavimento.vertex.push_back(points.at(6));
        pavimento.vertex.push_back(points.at(1));


    faces.push_back(anteriore);
    faces.push_back(posteriore);
    faces.push_back(pavimento);
    faces.push_back(laterale_sx);
    faces.push_back(laterale_dx);
    faces.push_back(tetto_dx);
    faces.push_back(tetto_sx);
    
}

void Mesh::Figure::draw(){

            for(short int i = 0; i < faces.size(); i++)
            {
                glColor3f(1,1,1);
                glBegin(GL_POLYGON);
                    Face temp= faces.at(i);
                    float* normal= temp.getNormal().getCoords();
                 //   cout<<"Normale della faccia anteriore\n"<<normal[0]<<" __ "<<normal[1]<<" __ "<<normal[2]<<endl;
                    glNormal3fv(normal);
                   // cout<<"Vertici faccia anteriore: "<<endl;
                    for(short int j = 0; j < temp.vertex.size(); j++){
                        glVertex3fv(temp.vertex.at(j).getCoords()); 
                       /* cout<<temp.vertex.at(j).getCoords()[0]<<" _ ";
                        cout<<temp.vertex.at(j).getCoords()[1]<<" _ ";
                        cout<<temp.vertex.at(j).getCoords()[2]<<endl;*/
                    }  
                glEnd();     
            }
        
}


vector<Mesh::Point> Mesh::Figure::buildPoints(){
    vector<Point> points;
    points.push_back(*(new Point(0,0,1)));
    points.push_back(*(new Point(0.5,0,1)));
    points.push_back(*(new Point(0.5,0.5,1)));
    points.push_back(*(new Point(0.25,0.7,1)));
    points.push_back(*(new Point(0,0.5,1)));
    points.push_back(*(new Point(0,0,0)));
    points.push_back(*(new Point(0.5,0,0)));
    points.push_back(*(new Point(0.5,0.5,0)));
    points.push_back(*(new Point(0.25,0.7,0)));
    points.push_back(*(new Point(0,0.5,0)));
    return points;

}
