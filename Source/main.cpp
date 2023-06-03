#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

// Vertex Array Object and Vertex Buffer Objects
GLuint VAO, VBO, shader;

// Uniform variables
GLuint uniformModel;

// Triangle location change variables
bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.6f;
float triIncrement = 0.005f;

// Rotation tools
const float toRadians = 3.14159265f / 180.0f;
float currentAngle = 0.0f;

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
    CompileShaders(shader, uniformModel);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Make window orange - RBG values, 255 means 1.
        glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

        // Beginning of Program for Shader application
        glUseProgram(shader);

        // Math for creating movement model
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(triOffset, triOffset/2, 0.0f));
        model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

        // shader transform (later with a model matrix instead of a single variable equation)
        // glUniform1f(uniformModel, triOffset);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);
        // End of Program for Shader Application

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events such as keyboard input or mouse movements */
        glfwPollEvents();

        if(direction){

            triOffset += triIncrement;
        }
        else{

            triOffset -= triIncrement;
        }

        if(triOffset >= triMaxoffset || triOffset <= -triMaxoffset){
            direction = !direction;
        }

        currentAngle += 0.5f;
        if(currentAngle >=360){

            currentAngle -=360;
        }
        if(currentAngle <0){

            currentAngle +=360;
        }
    }

    glfwTerminate();
    return 0;
}

