#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "PointLight.h"

class SpotLight: public PointLight{

public:
    SpotLight();

    SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat _ambientIntensity, GLfloat _diffuseIntensity,
                GLfloat shadowWidth, GLfloat shadowHeight,
                GLfloat xPos, GLfloat yPos, GLfloat zPos,
                GLfloat con, GLfloat lin, GLfloat exp,
                GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat _edge);

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, 
                    GLuint diffuseIntenQsityLocation, GLuint positionLocation,
                    GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, 
                    GLuint directionLocation, GLuint edgeLocation) override;

    void SetFlash(glm::vec3 pos, glm::vec3 dir);

    ~SpotLight();

private:
    // direction for point light
    glm::vec3 direction;

    // how much is not going to be shown on
    GLfloat edge, processedEdge;

};

#endif
