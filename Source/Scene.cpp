#include "../Header/Scene.h"

Scene::Scene(){

    width = 800;
    height = 600;
}

Scene::Scene(GLint windowWidth, GLint windowHeight){

    width = windowWidth;
    height = windowHeight;
}

int Scene::Initialize(){

    /* Initialize the GL Framework library */
    if (!glfwInit()) {
        printf("GLFW Init failed.\n");
        return -1;
    }

    // Setup GLFW Windows Properties
    // OpenGL Version 3.3

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Core Profile
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    mainWindow = glfwCreateWindow(width, height, "Scene Window", NULL, NULL);

    if (!mainWindow)
    {
        printf("Failed to create window with GLFW!");
        glfwTerminate();
        return -1;
    }

    glfwGetFramebufferSize (mainWindow, &bufferWidth, &bufferHeight);

    /* Make the window's context current */
    glfwMakeContextCurrent(mainWindow);

    // Initialize the GL Extension Wrangler library
    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if(error != GLEW_OK){

        printf("Error: %s", glewGetErrorString(error));
        glfwDestroyWindow(mainWindow);
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

    glEnable(GL_DEPTH_TEST);

    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
}

Scene::~Scene(){

    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

