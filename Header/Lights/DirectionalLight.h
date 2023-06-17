#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight: public Light{

public:
    DirectionalLight();

    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
                    GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
                    GLuint shadowWidth, GLuint shadowHeight, GLfloat near, GLfloat far,
                    GLfloat xDir, GLfloat yDir, GLfloat zdir);

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, 
                GLuint diffuseIntensityLocation, GLuint directionLocation,
                GLuint constantLocation=0, GLuint linearLocation=0, GLuint exponentLocation=0, 
                GLuint positionLocation=0, GLuint edgeLocation=0) override;

    glm::mat4 CalculateLightTransform();

    ~DirectionalLight();

private:
    glm::vec3 direction;


};

#endif