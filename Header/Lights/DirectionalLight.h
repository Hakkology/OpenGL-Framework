#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight: public Light{

public:
    DirectionalLight();

    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
                    GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
                    GLfloat xDir, GLfloat yDir, GLfloat zdir);

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation);


    ~DirectionalLight();

private:
    glm::vec3 direction;


};

#endif