#include "crono.h"

void Crono::Lancetta::draw() const{
    //DRAW lLANCETTA
        glPushMatrix();
            glRotatef(-rotate[0],0.0,0.0,1.0);
            glBegin(GL_LINES);
                glColor3f(color[0],color[1],color[2]);
                glVertex3f(0,0,z1);
                glVertex3f(0,0+raggio,z1);
            glEnd();
    glPopMatrix();

}