#include "../Header/Scene.h"

Scene::Scene(){

    width = 800;
    height = 600;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }

    xChange = 0.0f;
    yChange = 0.0f;
    
}

Scene::Scene(GLint windowWidth, GLint windowHeight){

    width = windowWidth;
    height = windowHeight;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }

    xChange = 0.0f;
    yChange = 0.0f;
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

    // Handle key + Mouse Input
    createCallbacks();
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glfwSetWindowUserPointer(mainWindow, this);
}

void Scene::handleKeys(GLFWwindow* window, int key, int code, int action, int mode){

    Scene* theWindow = static_cast<Scene*>(glfwGetWindowUserPointer(window)); 

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action = GLFW_PRESS)
        {
            theWindow ->keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow ->keys[key] = false;
        }
    }  
}

void Scene::handleMouse(GLFWwindow* window, double xPos, double yPos){

    Scene* theWindow = static_cast<Scene*>(glfwGetWindowUserPointer(window)); 

    if (theWindow -> mouseFirstMoved)
    {
        theWindow -> lastX = xPos;
        theWindow -> lastY = yPos;
        theWindow -> mouseFirstMoved = false;
    }

    theWindow -> xChange = xPos - theWindow -> lastX;
    theWindow -> yChange = theWindow -> lastY - yPos;

    theWindow -> lastX = xPos;
    theWindow -> lastY = yPos;

    //printf("x:%.6f, y:%.6f\n", theWindow->xChange, theWindow->yChange);
}

void Scene::createCallbacks(){

    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Scene::getXChange(){
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}

GLfloat Scene::getYChange(){
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}


Scene::~Scene(){

    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

