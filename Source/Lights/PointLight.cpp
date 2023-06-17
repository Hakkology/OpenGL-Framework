#include "../../Header/Lights/PointLight.h"
#include "../../Header/Shadows/OmniShadowMap.h"
#include "PointLight.h"

PointLight::PointLight() : Light(){

    // diffused light that comes from a direction, zero for default constructor
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f;
    linear = 0.0f;
    exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
                                    GLuint shadowWidth, GLuint shadowHeight, GLfloat near, GLfloat far,
                                    GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat con, GLfloat lin, GLfloat exp) : 
                                    Light(red, green, blue, _ambientIntensity, _diffuseIntensity, shadowWidth, shadowHeight, near, far){

    // defining values for diffused light
    position = glm::vec3(xPos, yPos, zPos);
    constant = con;
    linear = lin;
    exponent = exp;

    farPlane = far;

    float aspect = (float)shadowWidth/(float)shadowHeight;
    lightProj = glm::perspective (glm::radians(90.0f), aspect, near, far);

    shadowMap = new OmniShadowMap();
    shadowMap -> init(shadowWidth, shadowHeight);
}

std::vector<glm::mat4> PointLight::CalculateLightTransform(){

    std::vector<glm::mat4> lightMatrices;

    // x positive and negative
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));

    // y positive and negative
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));

    // z positive and negative
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

    return lightMatrices;
}

GLfloat PointLight::GetFarPlane(){

    return farPlane;
}

glm::vec3 PointLight::GetPosition()
{
    return position;
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint positionLocation,
                          GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint directionLocation, GLuint edgeLocation)
{

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