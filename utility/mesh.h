#if !defined(MESH_H)
#define MESH_H
#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include <string>
#include<vector>
#include<math.h>
#include <iostream>
#include <map>
using namespace std;

namespace Mesh{
    class Point;
    class Face;
    class Figure;
    class BezierCurve;
    class NurbsCurve;
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

class Mesh::BezierCurve{
    public:
        void addCheckpoint(Point x);
        void addCheckpoint(float x, float y, float z);
        void drawCurve();
        void drawCheckpoints();
        void modCheckpoint(Point who, Point newer);

    private:
        float cube=0.02;
        std::vector<float> checkpoints;
        bool checkInRange(float val, float cord, short invert);
        int max=0;
};

class Mesh::NurbsCurve{
    public:
        void addCheckpoint(Point x,float w);
        void addCheckpoint(float x, float y, float z,float w);
        void modCheckpoint(Point who, Point newer);
        void modUniform(Point who,float angleMod);
        void modWeight(Point who, float weight);
        void addKnot(float k);
        void drawCurve();
        void drawCheckpoints();
        void drawHandles();
        GLUnurbsObj* getNurb();
        NurbsCurve(int step,int degree);
        NurbsCurve(const char* jsonPath);

    private:
        float cube=0.02;
        std::map<int,float> angleMap;
        std::vector<float> checkpoints;
        std::vector<float> knots;
        GLUnurbsObj* nurbs;
        int degree=0;
        static GLvoid printError(GLenum errorCode);
        void setDegree(int deg);
        bool checkInRange(float val, float cord, short invert);
        int whoModUniform(Point who,float angleMod);
        bool modUniformGraphic(int i,float angleMod);
        void modUniformKnots(int i,float angleMod);

};

#endif