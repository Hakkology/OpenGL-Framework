#include "../../Header/Lights/PointLight.h"

PointLight::PointLight() : Light(){

    // diffused light that comes from a direction, zero for default constructor
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f;
    linear = 0.0f;
    exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
                                    GLfloat shadowWidth, GLfloat shadowHeight,
                                    GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat con, GLfloat lin, GLfloat exp) : 
                                    Light(red, green, blue, _ambientIntensity, _diffuseIntensity, shadowWidth, shadowHeight){

    // defining values for diffused light
    position = glm::vec3(xPos, yPos, zPos);
    constant = con;
    linear = lin;
    exponent = exp;
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint positionLocation,
                            GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint directionLocation, GLuint edgeLocation){

    Light::UseLight (ambientIntensityLocation, ambientColourLocation, diffuseIntensityLocation);

    // adding position constants
    glUniform3f(positionLocation, position.x, position.y, position.z);

    // adding attenuation constants
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);

}

PointLight::~PointLight(){

}