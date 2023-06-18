#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{

public:

    Camera();
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

    void keyControl(GLFWwindow* window, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);

    glm::vec3 getCameraPosition();
    glm::vec3 getCameraDirection();

    glm::mat4 calculateViewMatrix();

    ~Camera();

private:

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw; // looking left and right
    GLfloat pitch; // looking up and down

    GLfloat movementSpeed;
    GLfloat turnSpeed;

    void update();

};

#endif