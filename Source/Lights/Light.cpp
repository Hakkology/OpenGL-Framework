#include "../../Header/Lights/Light.h"

Light::Light(){

    // how much of a colour should be shown through ambient light:
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;
    diffuseIntensity = 0.0f;
    
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity, 
            GLuint shadowWidth, GLuint shadowHeight, GLfloat near, GLfloat far){

    shadowMap = new ShadowMap;
    shadowMap->init(shadowWidth, shadowHeight);
    // manual constructor defining values
    colour = glm::vec3(red, green, blue);
    ambientIntensity = _ambientIntensity;
    diffuseIntensity = _diffuseIntensity;

}

void Light::UseLight (GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation, 
                    GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint positionLocation, GLuint edgeLocation){

    // adding RGB and intensity values uniform locations for shaders
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);

    // adding diffuse light uniform locations for shaders
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);

}

Light::~Light(){



}
