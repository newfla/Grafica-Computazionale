#include "mesh.h"
using namespace std;
Mesh::Point Mesh::Face::getNormal(){
    float x=0, y=0,z=0;
    if(normal==NULL){
        for(short int i=0; i<vertex.size(); i++){
            Point first=vertex.at(i),
                    second=vertex.at((i+1)%vertex.size());
            x+=(first.getCoords()[1]-second.getCoords()[1])*(first.getCoords()[2]+second.getCoords()[2]);
            y+=(first.getCoords()[2]-second.getCoords()[2])*(first.getCoords()[0]+second.getCoords()[0]);
            z+=(first.getCoords()[0]-second.getCoords()[0])*(first.getCoords()[1]+second.getCoords()[1]);
        }
        normal= new Point (x,y,z);
    }
    return *normal;
}