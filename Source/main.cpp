#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Header/Mesh.h"
#include "../Header/Shader.h"
#include "../Header/Scene.h"
#include "../Header/Camera.h"
#include "../Header/Texture.h"
#include "../Header/Light.h"
#include "../Header/Utility.h"
#include "../Header/Material.h"

// Vertex Shader
static const char* vShader = "../Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "../Shaders/shader.frag";

// Window Creation
Scene mainWindow;

// Mesh list
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

// Camera creation
Camera camera; 

// Texture creation
Texture brickTexture;
Texture dirtTexture;

// Material instance creation
Material shinyMaterial;
Material dullMaterial;

// Light instance creation
Light mainLight;

// Utility instance creation
Utility utility;

// Constants for deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Triangle location change variables
bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.6f;
float triIncrement = 0.005f;

// Rotation tools
const float toRadians = 3.14159265f / 180.0f;
float currentAngle = 0.0f;

// Size tools
bool sizeDirection = true;
float currentSize = 0.7f;
float maxSize = 0.8f;
float minSize = 0.1f;

// to create an object
void CreateGameObject();

// shader functions
void CreateShaders();

// to define boundary conditions
void TransformControls();

int main(void)
{

    mainWindow = Scene(1366,768);
    mainWindow.Initialize();

    /*Creating Shapes Code Block*/
    //CreateTriangle(VAO, VBO);
    CreateGameObject();
    CreateShaders();

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

    // Loading textures
    brickTexture = Texture("../Textures/brick.png");
    brickTexture.LoadTexture();
    dirtTexture = Texture("../Textures/dirt.png");
    dirtTexture.LoadTexture();

    shinyMaterial = Material(1.0f, 32);
    dullMaterial = Material (0.3f, 4);

    mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f, 2.0f, -1.0f, -2.0f, 0.7f);

    GLuint uniformProjection =0, uniformModel=0, uniformView =0, uniformEyePosition =0,
            uniformAmbientIntensity =0, uniformAmbientColour =0, uniformDirection =0, uniformDiffuseIntensity =0,
            uniformSpecularIntensity =0, uniformShininess =0;

    // Math for creating projection model
    glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.f);

    /* Loop until the user closes the window */
    while (!mainWindow.getShouldClose())
    {
        // Make window orange - RBG values, 255 means 1.
        glClearColor(0.2f, 0.1f, 0.2f, 1.0f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Beginning of Program for Shader application
        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
        uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
        uniformDirection = shaderList[0].GetDirectionLocation();
        uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();
        uniformEyePosition = shaderList[0].GetEyePositionLocation();
        uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
        uniformShininess = shaderList[0].GetShininessLocation();

        mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour, 
                            uniformDiffuseIntensity, uniformDirection);

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

        // Creation of GameObject-1
        // Math for creating movement model
        glm::mat4 model(1.0f);

        model = glm::translate(model, glm::vec3(triOffset, 0.75f, -4.0f));
        model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 3.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(currentSize, currentSize, 1.0f));

        // shader transform
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        brickTexture.UseTexture();
        shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        meshList[0] -> Render3DMesh();

        // Creation of GameObject-2
        // Math for creating movement model
        model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(triOffset, -2.0f, -3.0f));
        model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        // shader transform
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        dirtTexture.UseTexture();
        dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        meshList[1] -> Render3DMesh();

        glUseProgram(0);
        // End of Program for Shader Application

        /* Swap front and back buffers */
        mainWindow.swapBuffers();

        // Delta time on code
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        /* Poll for and process events such as keyboard input or mouse movements */
        glfwPollEvents();
        // Camera key controls
        camera.keyControl(mainWindow.getWindow(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
        // Function for transform controls
        TransformControls();

    }

    glfwTerminate();
    return 0;
}

void CreateGameObject() {

    unsigned int indices[]={
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
      // x      y       z    u      v       nx    ny    nz
        -1.0f, -1.0f,-0.6f, 0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f,  0.5f, 0.0f,     0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -0.6f, 1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,   0.5f, 1.0f,     0.0f, 0.0f, 0.0f
    };

    utility.CalculateAverageNormals(indices, 12, vertices, 32, 8, 5);

    Mesh *obj1 = new Mesh();
    obj1 ->Create3DMesh(vertices, indices, 32, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2 -> Create3DMesh(vertices, indices, 32, 12);
    meshList.push_back(obj2);
}

void CreateShaders(){

    Shader *shader1 = new Shader();
    shader1 ->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

void TransformControls(){

        if(direction){

            triOffset += triIncrement;
        }
        else{

            triOffset -= triIncrement;
        }

        if(triOffset >= triMaxoffset || triOffset <= -triMaxoffset){
            direction = !direction;
        }

        currentAngle += 0.5f;
        if(currentAngle >=360){

            currentAngle -=360;
        }
        if(currentAngle <0){

            currentAngle +=360;
        }

        if(sizeDirection){

            currentSize += 0.001f;
        }
        else{
            
            currentSize -= 0.001f;
        }

        if(currentSize >= maxSize || currentSize <= minSize){

            sizeDirection = !sizeDirection;
        }
}

