#include "../Header/Light.h"

Light::Light(){

    // how much of a colour should be shown:
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;

}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity){

    // manual constructor defining values
    colour = glm::vec3(red, green, blue);
    ambientIntensity = _ambientIntensity;

}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation){

    // adding RGB and intensity values to shader
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
}

Light::~Light(){



}
