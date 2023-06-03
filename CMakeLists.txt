cmake_minimum_required(VERSION 3.12)
project(OpenGL_Study)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(OpenGL_Study Source/main.cpp)

# Link GLEW library
target_link_libraries(OpenGL_Study 
    glfw
    OpenGL::GL)
