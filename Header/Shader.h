#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CommonValues.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"


class Shader{

public:
    Shader();

    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFiles(const char* vertexPath, const char* fragmentPath);

    std::string ReadFile(const char* filePath);

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    GLuint GetAmbientIntensityLocation();
    GLuint GetAmbientColourLocation();
    GLuint GetDiffuseIntensityLocation();
    GLuint GetDirectionLocation();
    GLuint GetSpecularIntensityLocation();
    GLuint GetShininessLocation();
    GLuint GetEyePositionLocation();

    void SetDirectionalLight(DirectionalLight *directionalLight);
    void SetPointLight(PointLight *pointLight, unsigned int lightCount);
    void SetSpotLight(SpotLight *SpotLight, unsigned int lightCount);
    void SetTexture(GLuint textureUnit);
    void SetDirectionalShadowMap(GLuint textureUnit);
    void SetDirectionalLightTransform(glm::mat4 *transform);

    void UseShader();
    void ClearShader();

    ~Shader();

private:
    
    // Amount of lights we have
    int pointLightCount;
    int spotLightCount;

    // Vertex shaders and Uniform variables
    GLuint shaderID, uniformProjection, uniformModel, uniformView, 
                    uniformEyePosition, uniformSpecularIntensity, uniformShininess,
                    uniformTexture, uniformDirectionalLightTransform, uniformDirectionalShadowMap;

    struct{

        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        
        GLuint uniformDirection;

    } uniformDirectionalLight;

    GLuint uniformPointLightCount;

    struct{

        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        
        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;

    } uniformPointLight[MAX_POINT_LIGHTS];

    GLuint uniformSpotLightCount;

    struct{

        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        
        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;

        GLuint uniformDirection;
        GLuint uniformEdge;

    } uniformSpotLight[MAX_SPOT_LIGHTS];
        
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

};

#endif