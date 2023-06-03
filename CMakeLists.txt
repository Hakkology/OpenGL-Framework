cmake_minimum_required(VERSION 3.12)
# minimum required version of CMake
project(OpenGL_Study)
# project name
cmake_policy(SET CMP0072 NEW)
# Related to finding packages, forcing new behaviour applied after version 3.12, CMake specific

find_package(OpenGL REQUIRED)
# package must be found for this project to work

add_executable(OpenGL_Study Source/main.cpp)
# compile the source file, main

target_link_libraries(OpenGL_Study 
    GLEW
    glfw
    OpenGL::GL)
# Link glfw library and OpenGL::GL library. glfw is linked explicitly, while OpenGL::GL is using imported target provided by find_package(OpenGL)