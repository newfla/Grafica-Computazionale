#include"mesh.h"

Mesh::GluSolidFigure::GluSolidFigure(GLenum drawStyle, GLenum orientation, GLenum normals){
    this->drawStyle=drawStyle;
    this->orientation=orientation;
    this->normals=normals;
    quad=gluNewQuadric();
    gluQuadricDrawStyle(quad,drawStyle);
    gluQuadricOrientation(quad,orientation);
    gluQuadricNormals(quad,normals);
    if(drawStyle==GL_FILL){
      //  glEnable(GL_AUTO_NORMAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
}

void Mesh::GluSolidFigure::drawSphere(float radius, float slices, float stacks){
    gluSphere(quad,radius,slices,stacks);
}

void Mesh::GluSolidFigure::drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks){
    gluCylinder(quad, baseRadius, topRadius, height, slices, stacks);
}
void Mesh::GluSolidFigure::drawDisk (float innerRadius,float outerRadius, int slices, int rings){
    gluDisk(quad, innerRadius, outerRadius, slices, rings);
}

void Mesh::GluSolidFigure::drawPartialDisk (float innerRadius, float outerRadius, int slices, int rings, float startAngle, float sweepAngle){
    gluPartialDisk(quad, innerRadius, outerRadius, slices, rings, startAngle, sweepAngle);
}
