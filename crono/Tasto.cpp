#include "crono.h"

void Crono::Tasto::draw() const{
    //DRAW BUTTON
        glBegin(GL_QUADS);
            glColor3f(color[index][0],color[index][1],color[index][2]);
            glVertex3f(x, y, z1);
            glVertex3f( x+lato, y, z1);
            glVertex3f( x+lato, y+lato, z1);
            glVertex3f( x, y+lato, z1);
        glEnd();
    
    //DRAW TEXT BUTTON
        std::string temp=stringhe[index];
        float div=7.0;
        glColor3f(0, 0, 0);
        if (type==0 && index==1)
            div=5.0;
        glRasterPos2f(x+lato/div, y+0.085);
        for(int i = 0; i < temp.size(); i++)    
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, stringhe[index][i]);

}

void Crono::Tasto::checkClick(float nx, float ny){
    if(nx<x ||  nx>x+lato)
        return;
    if (ny<y|| ny>y+lato)
        return;
    index++;
    index=index%2;
    status=!status;
}
