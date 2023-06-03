#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the GL Framework library */
    if (!glfwInit()) {
        printf("GLFW Init failed.");
        return -1;
    }
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "My_Project", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Initialize the GL Extension Wrangler library
    glewExperimental = GL_TRUE;

    if(!glewInit()){

        printf("GLEW Init failed.");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize (window, &bufferWidth, &bufferHeight);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        // Make window blue - RBG values, 255 means 1.
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Poll for and process events such as keyboard input or mouse movements */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}