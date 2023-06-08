#include "../Header/Light.h"

Light::Light(){

    // how much of a colour should be shown through ambient light:
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;

    // diffused light that comes from a direction, zero for default constructor
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity,
        GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat _diffuseIntensity){

    // manual constructor defining values
    colour = glm::vec3(red, green, blue);
    ambientIntensity = _ambientIntensity;

    // defining values for diffused light
    direction = glm::vec3(xDir, yDir, zDir);
    diffuseIntensity = _diffuseIntensity;

}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
                    GLfloat diffuseIntensityLocation, GLfloat directionLocation){

    // adding RGB and intensity values uniform locations for shaders
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    
    // adding diffuse light uniform locations for shaders
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);

}

Light::~Light(){



}
