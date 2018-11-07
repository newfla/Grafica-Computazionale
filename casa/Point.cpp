#include "mesh.h"

Mesh::Point::Point(float x, float y, float z){
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
}

float* Mesh::Point::getCoords(){
    return &coords[0];
}