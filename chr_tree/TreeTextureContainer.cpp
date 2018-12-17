#include"tree.h"
#include"SOIL/SOIL.h"

GLvoid Tree::TreeTextureContainer::initTexture(const char* path,int pos,bool mipMap){
    int imageWidth, imageHeight, components;
    unsigned char *image;
    glBindTexture(GL_TEXTURE_2D,textures[pos]);
    image=SOIL_load_image(path,&imageWidth,&imageHeight,&components,SOIL_LOAD_RGBA);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if(mipMap){
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, imageWidth,imageHeight,GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);
    glEnable( GL_TEXTURE_2D );
    if( 0 == image ){
	cout<<"SOIL loading error: "<<endl<<SOIL_last_result();
    cout<<endl<<"--------"<<endl;
    }
}

GLuint Tree::TreeTextureContainer::getPos(int pos){
    return textures[pos];
}

Tree::TreeTextureContainer::TreeTextureContainer(){
    glGenTextures(n, textures);
}