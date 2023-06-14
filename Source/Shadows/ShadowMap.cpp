#include "../../Header/Shadows/ShadowMap.h"

class ShadowMap{

public:

    ShadowMap(){
        FBO = 0;
        shadowMap = 0;
    }

    bool ShadowMap::init (GLuint width, GLuint height){

        shadowWidth = width;
        shadowHeight = height;

        glGenFramebuffers(1, &FBO);

        // Depth component will store depth data for shadow map.
        glGenTextures(1, &shadowMap);
        glBindTextures(GL_TEXTURE_2D, shadowMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

        // Wraps are for repeating of textures.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Filters are linear or nearest, nearest gives a more pixelated look, linear gives a more blending look.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // depth values passed down to framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, &FBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

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

    void ShadowMap::Write(){

        glBindFramebuffer(GL_FRAMEBUFFER, &FBO);
    }

    void ShadowMap::Read(GLenum textureUnit){

        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, shadowMap);
    }

    ~ShadowMap(){

        if (FBO)
        {
            glDeleteFramebuffers(1, &FBO);
        }

        if (shadowMap)
        {
            glDeleteTextures(1, &shadowMap);
        }
    }

private:

    GLuint FBO, shadowMap;
    GLuint shadowWidth, shadowHeight;

#endif

};