#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture{

public:
    Texture();
    Texture(const char* fileLoc);

    bool LoadTexture();
    bool LoadTextureA();

    void UseTexture();
    void ClearTexture();

    ~Texture();

private:
    GLuint textureID;
    int width, height, bitDepth;

    const char* fileLocation;

};

#endif