#include "../Header/Camera.h"

Camera::Camera(){


}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed){

    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;

    front = glm::vec3(0.0f, 0.0f, -1.0f);

    movementSpeed = startMoveSpeed;
    turnSpeed = startTurnSpeed;

    update();
}

void Camera::keyControl(GLFWwindow* window, GLfloat deltaTime){

    GLfloat velocity = movementSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += front * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position -= front * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += right * velocity;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= right * velocity;
    }
    
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange){

    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange; 

    if (pitch > 89.0f){pitch = 89.0f;}
    if (pitch < -89.0f){pitch = -89.0f;}

    update();
}

glm::mat4 Camera::calculateViewMatrix(){

    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition(){
    return position;
}

void Camera::update(){

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera(){


}