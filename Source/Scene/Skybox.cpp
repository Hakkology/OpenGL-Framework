#include "../../Header/Scene/Skybox.h"

Skybox::Skybox(){


}

Skybox::Skybox(std::vector<std::string> faceLocations, const char* vSkyboxShader, const char* fSkyboxShader){

    // Shader setup
    skyShader = new Shader();

    skyShader->CreateFromFiles(vSkyboxShader, fSkyboxShader);

    uniformProjection = skyShader->GetProjectionLocation();
    uniformView = skyShader->GetViewLocation();

    // Texture setup
    glGenTextures (1, &textureID);
    glBindTexture (GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, bitDepth;

    for (size_t i = 0; i < 6; i++)
    {
        // Textures from files
        unsigned char* textureData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0);
        if (!textureData)
        {
            printf("Failed to find: %s\n", faceLocations[i].c_str());
            return;
        }

        glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        stbi_image_free(textureData);
    }

    // Wraps are for repeating of textures.
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Filters are linear or nearest, nearest gives a more pixelated look, linear gives a more blending look.
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Mesh Setup
    unsigned int skyboxIndices[] = {
        
        // front
        0, 1, 2,
        2, 1, 3,
        // right
        2, 3, 5,
        5, 3, 7,
        // back
        5, 7, 4,
        4, 7, 6,
        // left
        4, 6, 0,
        0, 6, 1,
        // top
        4, 0, 5,
        5, 0, 2,
        // bottom
        1, 6, 3,
        3, 6, 7
    };

    float skyboxVertices[] = {

        -1.0f,  1.0f, -1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,

        -1.0f,  1.0f,  1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f
    };

    skyMesh = new Mesh();
    skyMesh -> Create3DMesh (skyboxVertices, skyboxIndices, 64, 36);

}

void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix){

    viewMatrix = glm::mat4(glm::mat3(viewMatrix));

    glDepthMask (GL_FALSE);

    skyShader -> UseShader();

    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    skyShader -> Validate();
    skyMesh -> Render3DMesh();

    glDepthMask (GL_TRUE);
}

Skybox::~Skybox(){


}