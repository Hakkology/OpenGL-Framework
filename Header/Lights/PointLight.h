#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

class PointLight: public Light{

public:
    PointLight();

    PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
                GLfloat xPos, GLfloat yPos, GLfloat zPos,
                GLfloat con, GLfloat lin, GLfloat exp);

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, 
                GLuint diffuseIntensityLocation, GLuint positionLocation,
                GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, 
                GLuint directionLocation=0, GLuint edgeLocation=0) override;

    ~PointLight();

protected:
    glm::vec3 position;

    // Attenuation of the light source
    GLfloat constant, linear, exponent;

};

#endif
