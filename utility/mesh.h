#if !defined(MESH_H)
#define MESH_H
#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include <string>
#include<vector>
#include<math.h>
#include <iostream>
using namespace std;

namespace Mesh{
    class Point;
    class Face;
    class Figure;
};

class Mesh::Point{
    private:
        std::vector<float> coords;
    public:
        Point (float x, float y, float z);
        float* getCoords();
        ~Point();
        
};

class Mesh::Face{
    public:
        std::vector<Point> vertex;
        Point getNormal();
        void forceNormal();
        ~Face();
    private:
        Point* normal=NULL;
};

class Mesh::Figure{
    public:
        std::vector<Face> faces;
        Figure();
        void draw();
        void drawNormal();
        void addFaces(Mesh::Face face);
        void buildPoints(const char* path);
};

#endif