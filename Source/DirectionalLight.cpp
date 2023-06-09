#include "../Header/DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light(){

    // diffused light that comes from a direction, zero for default constructor
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
                                    GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, _ambientIntensity, _diffuseIntensity){

    // defining values for diffused light
    direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation){

    // adding RGB and intensity values uniform locations for shaders
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    
    // adding diffuse light uniform locations for shaders
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);

}

DirectionalLight::~DirectionalLight(){

}