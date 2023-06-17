#include "../../Header/Lights/DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light(){

    // diffused light that comes from a direction, zero for default constructor
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
                                    GLuint shadowWidth, GLuint shadowHeight, GLfloat near, GLfloat far,
                                    GLfloat xDir, GLfloat yDir, GLfloat zDir) 
                                    : Light(red, green, blue, _ambientIntensity, _diffuseIntensity, shadowWidth, shadowHeight, near, far){

    // defining values for diffused light
    direction = glm::vec3(xDir, yDir, zDir);
    lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation, 
                                GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint positionLocation, GLuint edgeLocation){

    Light::UseLight (ambientIntensityLocation, ambientColourLocation, diffuseIntensityLocation);
    
    // adding direction constants
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

glm::mat4 DirectionalLight::CalculateLightTransform()
{
    return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

DirectionalLight::~DirectionalLight()
{

}