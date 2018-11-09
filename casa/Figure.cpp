#include "mesh.h"

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
        posteriore.vertex.push_back(points.at(4));
        posteriore.vertex.push_back(points.at(3));
        posteriore.vertex.push_back(points.at(2));
        posteriore.vertex.push_back(points.at(1));
        posteriore.vertex.push_back(points.at(0));

    //ISTANZIAZIONE FACCIA LATERALE DX
        laterale_dx.vertex.push_back(points.at(1));
        laterale_dx.vertex.push_back(points.at(2));
        laterale_dx.vertex.push_back(points.at(7));
        laterale_dx.vertex.push_back(points.at(6));

    //ISTANZIAZIONE FACCIA LATERALE SX
        laterale_sx.vertex.push_back(points.at(5));
        laterale_sx.vertex.push_back(points.at(9));
        laterale_sx.vertex.push_back(points.at(4));
        laterale_sx.vertex.push_back(points.at(0));

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
        pavimento.vertex.push_back(points.at(1));
        pavimento.vertex.push_back(points.at(6));
        pavimento.vertex.push_back(points.at(5));
        pavimento.vertex.push_back(points.at(0));


    faces.push_back(anteriore);
    faces.push_back(posteriore);
    faces.push_back(pavimento);
    faces.push_back(laterale_sx);
    faces.push_back(laterale_dx);
    faces.push_back(tetto_dx);
    faces.push_back(tetto_sx);
    
}

void Mesh::Figure::draw(){
            int coff_normal=3;
            for(short int i = 0; i < faces.size(); i++)
            {
                float median[3]={0,0,0};
                glEnable(GL_LIGHTING);
                    glBegin(GL_POLYGON);
                        Face temp= faces.at(i);
                        Point point=temp.getNormal();
                        float* normal=point.getCoords();
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
                        glVertex3fv(median);
                        glColor3f(0,0,1);
                        glVertex3f(median[0]+normal[0]*coff_normal,median[1]+normal[1]*coff_normal,median[2]+normal[2]*coff_normal);
                    glEnd(); 
                
            }
        
}


vector<Mesh::Point> Mesh::Figure::buildPoints(){
    vector<Point> points;
    points.push_back(*(new Point(5,5,5)));
    points.push_back(*(new Point(8,5,5)));
    points.push_back(*(new Point(8,8,5)));
    points.push_back(*(new Point(6.5,9.5,5)));
    points.push_back(*(new Point(5,8,5)));
    points.push_back(*(new Point(5,5,10)));
    points.push_back(*(new Point(8,5,10)));
    points.push_back(*(new Point(8,8,10)));
    points.push_back(*(new Point(6.5,9.5,10)));
    points.push_back(*(new Point(5,8,10)));
    float x=0,y=0,z=0;
    
    for(short int i = 0; i < points.size(); i++)
    {
        x+=points.at(i).getCoords()[0];
        y+=points.at(i).getCoords()[1];
        z+=points.at(i).getCoords()[2];
    }
    x/=points.size();
    y/=points.size();
    z/=points.size();
    cout<<"Media x|y|z:"<<x<<"|"<<y<<"|"<<z<<endl;
    
    return points;

}
