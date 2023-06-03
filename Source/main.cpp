#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"

// Vertex Array Object and Vertex Buffer Objects
GLuint VAO, VBO, shader;

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
    CreateTriangle(VAO, VBO);
    CompileShaders(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Make window blue - RBG values, 255 means 1.
        glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

        // PBeginning of Program for Shader application
        glUseProgram(shader);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);
        // End of Program for Shader Application

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events such as keyboard input or mouse movements */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

