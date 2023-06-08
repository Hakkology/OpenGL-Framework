#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

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

    void UseShader();
    void ClearShader();

    ~Shader();

private:
    
    // Vertex shaders and Uniform variables
    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
    uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection, uniformSpecularIntensity, uniformShininess;
        
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

#endif

};