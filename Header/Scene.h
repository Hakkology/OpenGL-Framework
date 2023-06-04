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

    void swapBuffers(){

        glfwSwapBuffers(mainWindow);
    }

    ~Scene();

private:
    
    GLFWwindow *mainWindow;

    GLint width, height; 
    GLint bufferWidth, bufferHeight; 

#endif

};