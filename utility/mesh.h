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
    class BezierSurface;
    class NurbsSurface;
    class GluSolidFigure;
};

class Mesh::Point{
    private:
        std::vector<float> coords;
    public:
        Point (float x, float y, float z);
        Point (float x, float y, float z, float w);
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

class Mesh::BezierSurface{
    public:
        void addCheckpoint(Point x,float w);
        void addCheckpoint(float x, float y, float z, float w);
        void drawCurve();
        void testDrawCurve();
        BezierSurface(GLenum mode,std::vector<float> order, std::vector<float> min, std::vector<float> max);
    
    private:
        GLenum mode;
        std::vector<float> checkpoints;
        std::vector<float> order, min,max;
        Point* center;
        void buildCenter();
};

class Mesh::NurbsCurve{
    public:
        std::vector<float> checkpoints;
        std::vector<float> knots;
        int degree=0;
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
        static GLvoid printError(GLenum errorCode);

    private:
        float cube=0.02;
        std::map<int,float> angleMap;
        GLUnurbsObj* nurbs;
        void setDegree(int deg);
        bool checkInRange(float val, float cord, short invert);
        int whoModUniform(Point who,float angleMod);
        bool modUniformGraphic(int i,float angleMod);
        void modUniformKnots(int i,float angleMod);
};

class Mesh::NurbsSurface{
     public:
        void addCheckpoint(Point x,float w);
        void addCheckpoint(float x, float y, float z, float w);
        void addKnot(float k);
        void addUKnot(float k);
        void addVKnot(float k);
        void addTrimPwl2f(vector<float> trim);
        void addTrimCurve2f(vector<float> trim);
        void drawCurve();
        NurbsSurface(GLenum displayMode, int uStep, int vStep, GLfloat samplingMethod, int uOrder, int vOrder);
    
    private:
        GLUnurbsObj* nurbs;
        int order[2]={0,0};
        std::vector<float> checkpoints;
        std::vector<float> uKnots;
        std::vector<float> vKnots;
        std::vector<std::vector<float>> trimsPwl;
        std::vector<std::vector<float>> trimsCurve;
};

class Mesh::GluSolidFigure{
    private:
        GLenum drawStyle;
        GLenum orientation;
        GLenum normals;
        GLUquadric* quad;
        vector<float> translate;

    public:
        GluSolidFigure(GLenum drawStyle, GLenum orientation, GLenum normals);
        void drawSphere(float radius, float slices, float stacks);
        void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks);
        void drawDisk (float innerRadius,float outerRadius, int slices, int rings);
        void drawPartialDisk (float innerRadius, float outerRadius, int slices, int rings, float startAngle, float sweepAngle);

};


#endif