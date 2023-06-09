#include <iostream>
#include <string.h>

#include "../Header/Shader.h"

Shader::Shader(){

    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;

    pointLightCount = 0;
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
    uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
    uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
    uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
    uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

    uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

    // understand this code snippet
    for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        char locBuff[100] = { '\0'};

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", i);
        uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
        uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
        uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
        uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
        uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
        uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
        uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);
    }
    

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

    return uniformDirectionalLight.uniformColour;
}

GLuint Shader::GetAmbientIntensityLocation(){

    return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetDirectionLocation(){

    return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetDiffuseIntensityLocation(){

    return uniformDirectionalLight.uniformDiffuseIntensity;
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

void Shader::SetDirectionalLight(DirectionalLight *directionalLight){

    directionalLight ->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour,
                                uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLight(PointLight *pointLight, unsigned int lightCount){

    if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

    glUniform1i(uniformPointLightCount, lightCount);

    for (size_t i = 0; i < lightCount; i++)
    {
        pointLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColour, uniformPointLight[i].uniformDiffuseIntensity,
                               uniformPointLight[i].uniformPosition, 
                               uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
    }
    
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