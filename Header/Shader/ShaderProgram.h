#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>

struct UniformDirectionalLight {
    GLint uniformColour;
    GLint uniformAmbientIntensity;
    GLint uniformDirection;
    GLint uniformDiffuseIntensity;
};

struct UniformPointLight {
    GLint uniformColour;
    GLint uniformAmbientIntensity;
    GLint uniformDiffuseIntensity;
    GLint uniformPosition;
    GLint uniformConstant;
    GLint uniformLinear;
    GLint uniformExponent;
};

struct UniformSpotLight {
    GLint uniformColour;
    GLint uniformAmbientIntensity;
    GLint uniformDiffuseIntensity;
    GLint uniformPosition;
    GLint uniformConstant;
    GLint uniformLinear;
    GLint uniformExponent;
    GLint uniformDirection;
    GLint uniformEdge;
};

class ShaderProgram {
public:
    ShaderProgram(GLuint shaderID);

    ~ShaderProgram();

    void retrieveUniformLocations();

    // Declare getter functions for the uniform locations

private:

    GLuint m_shaderID;

    // Define uniform locations as private member variables

    void retrieveDirectionalLightUniformLocations();
    void retrievePointLightUniformLocations();
    void retrieveSpotLightUniformLocations();
};

#endif
