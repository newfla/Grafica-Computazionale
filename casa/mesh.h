#if !defined(MESH_H)
#define MESH_H
#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include <string>
#include<vector>
#include<math.h>
#include <iostream>

namespace Mesh{
    class Point;
    class Face;
    class Figure;
};

class Mesh::Point{
    public:
        Point (float x, float y, float z);
        float* getCoords();
    private:
        std::vector<float> coords;
};

class Mesh::Face{
    public:
        std::vector<Point> vertex;
        Point getNormal();
    private:
        Point* normal=NULL;
};

class Mesh::Figure{
    private:
        std::vector<Face> faces;
        std::vector<Point> buildPoints();
    
    public:
        void draw();
        Figure();
};

#endif