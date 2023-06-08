#include <iostream>
#include <string.h>

#include "../Header/Shader.h"

Shader::Shader(){

    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode){

    CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexShaderPath, const char* fragmentShaderPath){

    std::string vertexString = ReadFile (vertexShaderPath);
    std::string fragmentString = ReadFile (fragmentShaderPath);

    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    CompileShader (vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* filePath){

    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open())
    {
        printf("Failed to read %s! File does not exist.", filePath);
        return "";
    }
    
    std::string line = "";
    while(!fileStream.eof()){

        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode){

    shaderID = glCreateProgram();
    if (!shaderID)
    {
        printf("Shader program could not be created.");
        return;
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    // Link error catching
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    // Validation error catching
    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformAmbientColour = glGetUniformLocation(shaderID, "directionalLight.colour");
    uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
    uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
    uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType){
    
    GLuint theShader = glCreateShader (shaderType);

    const GLchar* theCode[1];
    theCode [0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    // Error Catching for Added Shaders
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);

    return;
}

// This section is to access private values by the shader program.
GLuint Shader::GetProjectionLocation(){

    return uniformProjection;
}

GLuint Shader::GetModelLocation(){

    return uniformModel;
}

GLuint Shader::GetViewLocation(){

    return uniformView;
}

GLuint Shader::GetAmbientColourLocation(){

    return uniformAmbientColour;
}

GLuint Shader::GetAmbientIntensityLocation(){

    return uniformAmbientIntensity;
}

GLuint Shader::GetDirectionLocation(){

    return uniformDirection;
}

GLuint Shader::GetDiffuseIntensityLocation(){

    return uniformDiffuseIntensity;
}

GLuint Shader::GetEyePositionLocation(){

    return uniformEyePosition;
}

GLuint Shader::GetShininessLocation(){

    return uniformShininess;
}

GLuint Shader::GetSpecularIntensityLocation(){

    return uniformSpecularIntensity;
}

void Shader::UseShader(){

    glUseProgram(shaderID);
}

void Shader::ClearShader(){

    if (shaderID != 0)
    {
        glDeleteProgram(shaderID);
        shaderID =0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}

Shader::~Shader(){

    ClearShader();
}