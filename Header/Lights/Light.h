#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shadows/ShadowMap.h"

class Light{

public:

    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity, 
            GLfloat shadowWidth, GLfloat shadowHeight, GLfloat near, GLfloat far);

    virtual void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, 
                GLuint diffuseIntensityLocation, GLuint directionLocation=0,
                GLuint constantLocation=0, GLuint linearLocation=0, GLuint exponentLocation=0, 
                GLuint positionLocation=0, GLuint edgeLocation=0);

    ShadowMap* GetShadowMap(){
        
        return shadowMap;
    }

    ~Light();

protected:

    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;

    glm::mat4 lightProj;

    ShadowMap *shadowMap;
    
};

#endif


