#if !defined(TREE_H)

#include "../utility/mesh.h"

namespace Tree{
    class Star;
    class Decor;
    class Gift;
    class ChrTree;
}

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
        void draw(float x, float y) const;
        static vector<Decor> buildDecorsFromFile(const char* path);

    private:
        float radius,slices,stacks;
        vector<float> color,scale;
        Decor(float radius, int slices, int stacks, vector<float>color, vector<float>scale);
};

class Tree::Gift{
    public:
        void draw(float x,float y) const;
        static vector<Gift> buildGiftsFromFile(const char* path);
    private:
        float side;
        vector<float> colorBox,colorRibbon,scale;
        Mesh::NurbsCurve* ribbon;
        Gift(vector<float>colorRibbon,vector<float>colorBox,vector<float>scale,float cube,Mesh::NurbsCurve* ribbon);
};

class Tree::ChrTree{
    public:
        void buildTreeFromFile(const char* path);
        void draw() const;
        void addStar(Tree::Star stella);
        void addDecor(vector<Tree::Decor> decor);
        float getTroncoHeight();

    private:
        Tree::Star stella;
        vector<Tree::Decor> palline;
        vector<float>paramTronco, paramCono;
        vector<vector<float>>color;
        Mesh::GluSolidFigure *tronco, *baseTronco;
};

#endif