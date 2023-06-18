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
    void CreateFromFiles(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
    void Validate();

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
    GLuint GetOmniLightPosLocation();
    GLuint GetFarPlaneLocation();
    

    void SetDirectionalLight(DirectionalLight *directionalLight);
    void SetPointLight(PointLight *pointLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
    void SetSpotLight(SpotLight *SpotLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
    void SetTexture(GLuint textureUnit);
    void SetDirectionalShadowMap(GLuint textureUnit);
    void SetDirectionalLightTransform(glm::mat4 *transform);
    void SetLightMatrices(std::vector<glm::mat4> lightMatrices);

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
                    uniformTexture, uniformDirectionalLightTransform, uniformDirectionalShadowMap,
                    uniformOmniLightPos, uniformFarPlane;

    GLuint uniformlightMatrices[6];

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

    struct{

        GLuint shadowMap;
        GLuint farPlane;
    } uniformOmniShadowMap[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];
        
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
    void CompileProgram();

    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    

};

#endif