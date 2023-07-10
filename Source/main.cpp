#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>

#include "../Header/CommonValues.h"

#include "../Header/Mesh.h"
#include "../Header/Texture.h"
#include "../Header/Material.h"
#include "../Header/Model.h"

#include "../Header/Shader.h"
#include "../Header/Scene.h"
#include "../Header/Camera.h"
#include "../Header/Scene/Skybox.h"

#include "../Header/Lights/DirectionalLight.h"
#include "../Header/Lights/PointLight.h"
#include "../Header/Lights/SpotLight.h"

#include "../Header/Utility.h"

// Window Creation
Scene mainWindow;

// Mesh list
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Shader directionalShadowShader, omniShadowShader;

// Uniform Variables
GLuint uniformProjection =0, uniformModel=0, uniformView =0, uniformEyePosition =0,
        uniformSpecularIntensity =0, uniformShininess =0,
        uniformOmniLightPos =0, uniformFarPlane =0;

// Camera creation
Camera camera; 

// Texture creation
Texture brickTexture, dirtTexture, plainTexture;

// Material instance creation
Material shinyMaterial, dullMaterial;

// Model objs
Model trees, trees2, lampPost, statue;

// Light instance creation
unsigned int pointLightCount =0; 
unsigned int spotLightCount =0;      
DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
Skybox skybox;

// Utility instance creation
Utility utility;

// Constants for deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Triangle location change variables
bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.8f;
float triIncrement = 0.005f;

// Rotation tools
float currentAngle = 0.0f;

// Size tools
bool sizeDirection = true;
float currentSize = 0.7f;
float maxSize = 0.8f;
float minSize = 0.1f;

// to create an objects and shaders
void CreateGameObject();
void CreateShaders();

// Render functions
void RenderScene();
void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
void DirectionalShadowMapPass(DirectionalLight *mainLight);
void OmniShadowMapPass(PointLight* light);

// to define boundary conditions
void TransformControls();

int main(void)
{
    mainWindow = Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    mainWindow.Initialize();

    /*Creating Shapes Code Block*/
    //CreateTriangle(VAO, VBO);
    CreateGameObject();
    CreateShaders();

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

    // Loading textures
    brickTexture = Texture(brickTexturePath);
    brickTexture.LoadTextureA();
    dirtTexture = Texture(dirtTexturePath);
    dirtTexture.LoadTextureA();
    plainTexture = Texture(plainTexturePath);
    plainTexture.LoadTextureA();

    shinyMaterial = Material(1.0f, 32);
    dullMaterial = Material (0.3f, 4);

    trees = Model();
    trees.LoadModel(treeModelPath);
    lampPost = Model();
    lampPost.LoadModel(lampModelPath);
    statue = Model();
    statue.LoadModel(statueModelPath);
    trees2 = Model();
    trees2.LoadModel(treeModelPath);

    mainLight = DirectionalLight(1.0f, 0.53f, 0.3f, 
                                0.0f, 0.4f,
                                2048, 2048, 0.0, 0.0,
                                -10.0f, -12.0f, 18.5f);

    pointLights[0] = PointLight( 0.0f, 1.5f, 1.0f,
                                 0.0f, 1.0f,
                                 1024, 1024, 0.01f, 100.0f,
                                -4.0f, 0.0f, 10.0f,
                                 0.3f, 0.05f, 0.05f);

    pointLightCount++;
    pointLights[1] = PointLight( 2.0f, 1.0f, 0.0f,
                                 0.0f, 1.0f,
                                 1024, 1024, 0.01f, 100.0f,
                                 0.0f, 0.0f, -1.0f,
                                 0.3f, 0.05f, 0.05f);

    pointLightCount++;
    spotLights[0] = SpotLight( 1.0f, 0.0f, 0.0f,
                               0.0f, 0.4f,
                               1024, 1024, 0.01f, 100.0f,
                               5.0f, 2.0f, 5.0f,
                               0.3f, 0.05f, 0.05f,
                               0.0f,-1.0f, 0.0f, 30.0f);

    spotLightCount++;

    std::vector<std::string> skyboxFaces;
    skyboxFaces.push_back(skyboxRtPath);
    skyboxFaces.push_back(skyboxLfPath);
    skyboxFaces.push_back(skyboxUpPath);
    skyboxFaces.push_back(skyboxDnPath);
    skyboxFaces.push_back(skyboxBkPath);
    skyboxFaces.push_back(skyboxFtPath);

    skybox = Skybox (skyboxFaces, vSkyboxShader, fSkyboxShader);

    // Math for creating projection model
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.f);

    /* Loop until the user closes the window */
    while (!mainWindow.getShouldClose())
    {

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

        DirectionalShadowMapPass(&mainLight);
        for (size_t i = 0; i < pointLightCount; i++)
        {
            OmniShadowMapPass(&pointLights[i]);
        }

        for (size_t i = 0; i < spotLightCount; i++)
        {
            OmniShadowMapPass(&spotLights[i]);
        }
        
        RenderPass(projection, camera.calculateViewMatrix());

        glUseProgram(0);
        // End of Program for Shader Application
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

    unsigned int floorIndices[] = {

        0, 2, 1,
        1, 2, 3
    };

    GLfloat floorVertices[]{

        -10.0f, 0.0f, -10.0f,   0.0f,  0.0f,    0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, -10.0f,    10.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        -10.0f, 0.0f, 10.0f,    0.0f,  10.0f,   0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, 10.0f,     10.0f, 10.0f,   0.0f, -1.0f, 0.0f
    };

    utility.CalculateAverageNormals(indices, 12, vertices, 32, 8, 5);

    Mesh *obj1 = new Mesh();
    obj1 ->Create3DMesh(vertices, indices, 32, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2 -> Create3DMesh(vertices, indices, 32, 12);
    meshList.push_back(obj2);

    Mesh *obj3 = new Mesh();
    obj3 -> Create3DMesh(floorVertices, floorIndices, 32, 6);
    meshList.push_back(obj3);
}

void CreateShaders(){

    Shader *shader1 = new Shader();
    shader1 ->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    directionalShadowShader = Shader();
    directionalShadowShader.CreateFromFiles(vShadowShader, fShadowShader);

    omniShadowShader = Shader();
    omniShadowShader.CreateFromFiles(vOmniShadowShader, gOmniShadowShader, fOmniShadowShader);
}

void RenderScene(){

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

    model = glm::translate(model, glm::vec3(triOffset, -1.0f, -3.0f));
    model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 1.0f, 3.0f));
    model = glm::scale(model, glm::vec3(currentSize, currentSize, 1.0f));
    //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    // shader transform
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    brickTexture.UseTexture();
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    meshList[1] -> Render3DMesh();

    // Creation of GameObject-3
    // Math for creating movement model
    model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));

    // shader transform
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dirtTexture.UseTexture();
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    meshList[2] -> Render3DMesh();

    // Tree model
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.0f, -2.0f, -3.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    trees.Render3DModel();

    // Tree2 model
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(3.0f, -2.0f, -3.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    trees2.Render3DModel();

    // Lamppost model
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.5f, -2.0f, -1.5f));
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, -90.0f));
    model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    lampPost.Render3DModel();    

    // statue model
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
    model = glm::rotate(model, 90.0f * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 0.0f, 2.0f));
    model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    statue.Render3DModel();   
}

void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix){

    glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
    // Make window orange - RBG values, 255 means 1.
    glClearColor(0.2f, 0.5f, 0.2f, 1.0f);
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox.DrawSkybox(viewMatrix, projectionMatrix);

    shaderList[0].UseShader();

    uniformModel = shaderList[0].GetModelLocation();
    uniformProjection = shaderList[0].GetProjectionLocation();
    uniformView = shaderList[0].GetViewLocation();
    uniformEyePosition = shaderList[0].GetEyePositionLocation();
    uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
    uniformShininess = shaderList[0].GetShininessLocation();

    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

    shaderList[0].SetDirectionalLight(&mainLight);
    shaderList[0].SetPointLight(pointLights, pointLightCount, 3, 0);
    shaderList[0].SetSpotLight(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
    glm::mat4 lightTransform = mainLight.CalculateLightTransform();
    shaderList[0].SetDirectionalLightTransform(&lightTransform);

    mainLight.GetShadowMap() -> Read(GL_TEXTURE2);
    shaderList[0].SetTexture(1);
    shaderList[0].SetDirectionalShadowMap(2);

    // for Camera Lights
    spotLights[0].SetFlash(camera.getCameraPosition(), camera.getCameraDirection());

    shaderList[0].Validate();
    RenderScene();
}

void DirectionalShadowMapPass(DirectionalLight *light){

    directionalShadowShader.UseShader();
    
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    light->GetShadowMap()->Write();
    glClear(GL_DEPTH_BUFFER_BIT);

    uniformModel = directionalShadowShader.GetModelLocation();
    glm::mat4 lightTransform = light->CalculateLightTransform();
    directionalShadowShader.SetDirectionalLightTransform (&lightTransform);

    directionalShadowShader.Validate();
    RenderScene();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OmniShadowMapPass(PointLight* light){

    omniShadowShader.UseShader();
    
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    light->GetShadowMap()->Write();
    glClear(GL_DEPTH_BUFFER_BIT);

    uniformModel = omniShadowShader.GetModelLocation();
    uniformOmniLightPos = omniShadowShader.GetOmniLightPosLocation();
    uniformFarPlane = omniShadowShader.GetFarPlaneLocation();

    glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
    glUniform1f(uniformFarPlane, light->GetFarPlane());
    omniShadowShader.SetLightMatrices(light->CalculateLightTransform());

    omniShadowShader.Validate();
    RenderScene();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

