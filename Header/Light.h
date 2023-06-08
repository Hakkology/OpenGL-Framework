#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>

#include <glm/glm.hpp>

class Light{

public:

    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity, 
        GLfloat xDir, GLfloat yDir, GLfloat zdir, GLfloat _diffuseIntensity);

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
        GLuint diffuseIntensityLocation, GLuint directionLocation);

    ~Light();

private:

    glm::vec3 colour;
    GLfloat ambientIntensity;

    glm::vec3 direction;
    GLfloat diffuseIntensity;

#endif

};