#include <iostream>
#include "shader.h"
#include <string.h>

// Vertex Shader
static const char* vShader = "                                          \n\
#version 330                                                            \n\
                                                                        \n\
layout (location =0) in vec3 pos;                                       \n\
                                                                        \n\
out vec4 vCol;                                                          \n\
                                                                        \n\
uniform mat4 model;                                                     \n\
                                                                        \n\
void main()                                                             \n\
{                                                                       \n\
    gl_Position = model * vec4(pos, 1.0);                               \n\
    vCol = vec4 ( clamp ( pos, 0.0f, 1.0f ), 1.0f );                    \n\
}";

// Fragment Shader
static const char* fShader = "                                          \n\
#version 330                                                            \n\
                                                                        \n\
in vec4 vCol;                                                           \n\
                                                                        \n\
out vec4 colour;                                                        \n\
                                                                        \n\
void main()                                                             \n\
{                                                                       \n\
    colour = vCol;                                                      \n\
}";

void CreateTriangle(GLuint& VAO, GLuint& VBO) {

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    // Generate vertex Arrays
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate vertex Buffers
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //static draw means points do not change, dynamic draw is also available.

    // Enable vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Release Vertex Buffer Binds
    glBindBuffer(GL_ARRAY_BUFFER,0);

    // Release Vertex Array Binds
    glBindVertexArray(0);
}

void CreatePyramid(GLuint& VAO, GLuint& VBO, GLuint& IBO) {

    unsigned int indices[]={
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    // Generate vertex Arrays
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate vertex Buffers And indices
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //static draw means points do not change, dynamic draw is also available.

    // Enable vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Release Vertex Array Binds
    glBindVertexArray(0);
    
    // Release Vertex Buffer Binds
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType){
    
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

void CompileShaders(GLuint& shader, GLuint& uniformModel){

    shader = glCreateProgram();
    if (!shader)
    {
        printf("Shader program could not be created.");
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    // Link error catching
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    // Validation error catching
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }

    uniformModel = glGetUniformLocation(shader, "model");
}
