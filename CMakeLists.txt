cmake_minimum_required(VERSION 3.12)
# minimum required version of CMake
project(OpenGL_Framework)
# project name
cmake_policy(SET CMP0072 NEW)
# Related to finding packages, forcing new behaviour applied after version 3.12, CMake specific

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
# package must be found for this project to work

add_executable(OpenGL-Framework Source/main.cpp 
                            Source/Mesh.cpp Header/Mesh.h 
                            Source/Shader.cpp Header/Shader.h 
                            Source/Scene.cpp Header/Scene.h 
                            Source/Camera.cpp Header/Camera.h
                            Source/Texture.cpp Header/Texture.h
                            Source/Utility.cpp Header/Utility.h
                            Source/Material.cpp Header/Material.h
                            Source/Lights/Light.cpp Header/Lights/Light.h
                            Source/Lights/DirectionalLight.cpp Header/Lights/DirectionalLight.h
                            Source/Lights/PointLight.cpp Header/Lights/PointLight.h
                            Source/Lights/SpotLight.cpp Header/Lights/SpotLight.h)
# compile the source file, main

include_directories(
    $(PROJECT_SOURCE_DIR)/Header
    $(PROJECT_SOURCE_DIR)/Header/Lights
    $(PROJECT_SOURCE_DIR)/Resources
)

target_link_libraries(OpenGL-Framework 
    GLEW
    glfw
    OpenGL::GL
    )
# Link glfw library and OpenGL::GL library. glfw is linked explicitly, while OpenGL::GL is using imported target provided by find_package(OpenGL)