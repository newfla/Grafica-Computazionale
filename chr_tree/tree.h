#if !defined(TREE_H)

#include "../utility/mesh.h"
#include<string>

namespace Tree{
    class TreeTextureContainer;
    class Star;
    class Decor;
    class Gift;
    class ChrTree;
    
};

class Tree::TreeTextureContainer{
    public:
        GLvoid initTexture(const char* path, int pos,bool mipMap);
        GLuint getPos(int pos);
        TreeTextureContainer();

    private:
        static const int n=6;
        GLuint textures[n];
};

class Tree::Star{
    public:
        void buildFromFile(const char* path);
        void draw() const;

    private:
        float tot, radius, height;
        int slices,stacks;
        vector<float> color,scale;
};

class Tree::Decor{
    public:
        void draw(float x, float y, Tree::TreeTextureContainer* container) const;
        static vector<Decor> buildDecorsFromFile(const char* path,Tree::TreeTextureContainer* container);

    private:
        float radius,slices,stacks;
        int pos=0;
        vector<float> color,scale;
        Decor(float radius, int slices, int stacks, vector<float>color, vector<float>scale, int pos);
};

class Tree::Gift{
    public:
        void draw(float x,float y, Tree::TreeTextureContainer* container) const;
        static vector<Gift> buildGiftsFromFile(const char* path,Tree::TreeTextureContainer* container);
    private:
        float side;
        bool texture=false;
        vector<float> colorBox,colorRibbon,scale;
        Mesh::NurbsCurve* ribbon;
        Gift(vector<float>colorRibbon,vector<float>colorBox,vector<float>scale,float cube,Mesh::NurbsCurve* ribbon);
};

class Tree::ChrTree{
    public:
        void buildTreeFromFile(const char* path, Tree::TreeTextureContainer* container);
        void draw(Tree::TreeTextureContainer* container) const;
        void addStar(Tree::Star stella);
        void addDecor(vector<Tree::Decor> decor);
        float getTroncoHeight();
        static void resetMaterial();
        

    private:
        Tree::Star stella;
        vector<Tree::Decor> palline;
        vector<float>paramTronco, paramCono;
        vector<vector<float>>color;
        Mesh::GluSolidFigure *tronco, *baseTronco;
        bool texture[2]={false,false};
        
};

#endif