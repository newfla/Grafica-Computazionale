#if !defined(CRONO_H)
#define CRONO_H
#define _USE_MATH_DEFINES
#include<GL/gl.h>
#include<GL/glut.h>
#include <string>
#include<math.h>

namespace Crono{
    class Shape;
    class Lancetta;
    class Quadrante;
    class Tasto;
}

class Crono::Shape{
    public:
        float radians=M_PI/180;
        float raggio;
        float z1;
        float z2;
        float x;
        float y;
        float rotate[2]={0,0};
        virtual void draw() const{};
};

class Crono::Lancetta: public Shape{
    public:
        float color[3];
        void draw() const;
};

class Crono::Quadrante: public Shape{
    public:
        Crono::Lancetta minuti, secondi;
        void draw() const;
        void moveToCenter() const;
        void moveBack() const;
};

class Crono::Tasto: public Shape{
    public:
        float color[2][3];
        float lato;
        short int type=0;
        std::string stringhe[2];
        void draw() const;
        void checkClick(float nx, float ny);
        bool status=false;

    private:
        short int index;
        
};


#endif // CRONO_H
