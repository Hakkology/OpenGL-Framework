#include "../../Header/Shadows/OmniShadowMap.h"
   
OmniShadowMap::OmniShadowMap() : ShadowMap(){

    
}

bool OmniShadowMap::init(GLuint width, GLuint height){

    shadowWidth = width;
    shadowHeight = height;

    glGenFramebuffers(1, &FBO);

    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);

    for (size_t i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }

    // Filters are linear or nearest, nearest gives a more pixelated look, linear gives a more blending look.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wraps are for repeating of textures. R value is added here for 3D purposes to smoothen the edges.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);

    // no need to change colours
    glDrawBuffer (GL_NONE);
    glReadBuffer (GL_NONE);

    // just for error checking
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Framebuffer Error: %i\n", status);
        return false;
    }
        
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

void OmniShadowMap::Write(){

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void OmniShadowMap::Read(GLenum textureUnit){

    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);
}

OmniShadowMap::~OmniShadowMap(){


}