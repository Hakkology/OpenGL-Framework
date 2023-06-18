#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>

#include <glm/glm.hpp>

class Material{

public:

    Material();
    Material(GLfloat specularIntensity, GLfloat shine);

    void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

    ~Material();

private:

    GLfloat specularIntensity;
    GLfloat shininess;

};

#endif