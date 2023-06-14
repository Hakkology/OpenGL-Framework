#ifndef SHADOW_MAP_H
#define SHADOW_MAP_H

#include <stdio.h>

#include <GL/glew.h>

class ShadowMap{

public:

    ShadowMap();

    virtual bool init (GLuint width, GLuint height);

    virtual void Write();

    virtual void Read(GLenum textureUnit);

    GLuint GetShadowWidth() {return shadowWidth;}
    GLuint GetShadowHeight() {return shadowHeight;}

    ~ShadowMap();

private:

    GLuint FBO, shadowMap;
    GLuint shadowWidth, shadowHeight;

#endif

};