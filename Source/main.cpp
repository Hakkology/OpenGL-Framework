#include <iostream>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Vertex Array Object and Vertex Buffer Objects
GLuint VAO, VBO, shader;
// Create Triangle Function
void CreateTriangle();
void AddShader(GLuint, const char*, GLenum);
void CompileShaders();


// Vertex Shader
static const char* vShader = "                                  \n\
#version 330                                                    \n\
                                                                \n\
layout (location =0) in vec3 pos;                               \n\
                                                                \n\
void main()                                                     \n\
{                                                               \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);   \n\
}";

// Fragment Shader
static const char* fShader = "                                  \n\
#version 330                                                    \n\
                                                                \n\
out vec4 colour;                                                \n\
                                                                \n\
void main()                                                     \n\
{                                                               \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                          \n\
}";

int main(void)
{
    GLFWwindow* window;

    /* Initialize the GL Framework library */
    if (!glfwInit()) {
        printf("GLFW Init failed.\n");
        return -1;
    }
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "My_Project", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize (window, &bufferWidth, &bufferHeight);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Initialize the GL Extension Wrangler library
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK){

        printf("GLEW Init failed.\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // If we want to use GLAD
    /*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout <<"Could not load OpenGL" << std::endl;
        glfwTerminate();
        return -1;
    }
    */

    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    /*Creating Triangle Code Block*/
    CreateTriangle();
    CompileShaders();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Make window blue - RBG values, 255 means 1.
        glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

        // Program for Shader application
        glUseProgram(shader);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events such as keyboard input or mouse movements */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void CreateTriangle(){

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

void CompileShaders(){

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
}