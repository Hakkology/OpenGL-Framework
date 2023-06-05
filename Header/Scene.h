#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Scene{

public:

    Scene();

    Scene(GLint windowWidth, GLint windowHeight);

    int Initialize();

    GLfloat getBufferWidth(){
        
        return bufferWidth;
    }

    GLfloat getBufferHeight(){
        
        return bufferHeight;
    }

    bool getShouldClose(){

        return glfwWindowShouldClose(mainWindow);
    }

    bool* getKeys(){

        return keys;
    }

    // Simplified solution
    GLfloat getXChange();
    GLfloat getYChange();
    GLFWwindow* getWindow();

    void swapBuffers(){

        glfwSwapBuffers(mainWindow);
    }

    ~Scene();

private:
    
    GLFWwindow *mainWindow;

    GLint width, height; 
    GLint bufferWidth, bufferHeight; 

    bool keys [1024];

    GLfloat lastX, lastY, xChange, yChange;
    bool mouseFirstMoved;

    void createCallbacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);

#endif

};