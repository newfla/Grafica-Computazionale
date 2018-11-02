#include "crono.h"
#include <cstdlib>
#include <iostream>
void Crono::Quadrante::draw() const{

    glPushMatrix();
            moveToCenter();
            glRotatef(-rotate[0],1.0,0.0,0.0);
            glRotatef(-rotate[1],0.0,1.0,0.0);
            moveBack(); 

            //FACCIA FRONTALE
                glBegin(GL_TRIANGLE_FAN);
                    glColor3f(0.9, 0.9, 0.9);
                    glVertex3f(0.0,0.0,z1);
                    for(float i=0; i<=400; i++)
                        glVertex3f(cos(i*radians)*raggio,sin(i*radians)*raggio,z1); 
                    glEnd();

            //FACCIA NASCOSTA
                glBegin(GL_TRIANGLE_FAN);
                    glColor3f(0.5, 0.5, 0.5);
                    glVertex3f(0.0,0.0,z2);
                    for(float i=0; i<=400; i++)
                        glVertex3f(cos(i*radians)*raggio,sin(i*radians)*raggio,z2);   
                glEnd();

            //BORDO CILINDRO
                glBegin(GL_QUAD_STRIP);
                    glColor3f(0.85, 0.85, 0.85);
                    for(float i=0; i<=400; i++)
                    {
                        glVertex3f(cos(i*radians)*raggio,sin(i*radians)*raggio,z2);
                        glVertex3f(cos(i*radians)*raggio,sin(i*radians)*raggio,z1);
                    }
                glEnd();
            
            //LANCETTA SECONDI
                secondi.draw();

            //LANCETTA MINUTI
                minuti.draw();
            
            //NUMERI QUADRANTE
                glColor3f(0, 0, 0);
                float temp=270;
                for(short int i = 1; i <13; i++)
                {
                    glPushMatrix();
                        temp+=30;
                        float y1=y, x1=x;
                        glRotatef(-temp,0,0,1);
                        glTranslatef(raggio-0.1,0,0);
                        std::string s = std::to_string(i); 
                        if(i==12)
                           y1+=0.025;
                        else if(i==6)
                            y1-=0.012;
                        glRasterPos3f(x1,y1,z1+0.01);
                        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[0]);
                        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[1]);
                    glPopMatrix();
                }
    glPopMatrix();

}

void Crono::Quadrante::moveToCenter() const{
    glTranslatef(x,y,(z1+z2)/2.0);
}

void Crono::Quadrante::moveBack() const{
    glTranslatef(-x,-y,-(z1+z2)/2.0);
}