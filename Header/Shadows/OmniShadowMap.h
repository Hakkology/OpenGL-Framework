#ifndef OMNISHADOW_MAP_H
#define OMNISHADOW_MAP_H

#include <stdio.h>

#include <GL/glew.h>

#include "ShadowMap.h"

class OmniShadowMap: public ShadowMap{

public:

    OmniShadowMap();

    bool init (GLuint width, GLuint height);

    void Write();

    void Read(GLenum textureUnit);

    GLuint GetShadowWidth() {return shadowWidth;}
    GLuint GetShadowHeight() {return shadowHeight;}

    ~OmniShadowMap();

private:

};

#endif