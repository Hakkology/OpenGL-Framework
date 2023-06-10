#include "../Header/Texture.h"

Texture::Texture(){

    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = "";
}

Texture::Texture(const char* fileLoc){

    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = fileLoc;

}

bool Texture::LoadTexture(){

    // Textures from files
    unsigned char* textureData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    if (!textureData)
    {
        printf("Failed to find: %s\n", fileLocation);
        return false;
    }
    
    // Similar to VAO's, first generate, then bind to ID.
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Wraps are for repeating of textures.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filters are linear or nearest, nearest gives a more pixelated look, linear gives a more blending look.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Texture itself, mipmaps, data type, width, height, always 0, load type, char is byte so Unsigned byte, texdata.
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Release the Bind.
    glBindTexture(GL_TEXTURE_2D, 0);
    // Release stbi.
    stbi_image_free(textureData);

    return true;
}

bool Texture::LoadTextureA(){

    // Textures from files
    unsigned char* textureData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    if (!textureData)
    {
        printf("Failed to find: %s\n", fileLocation);
        return false;
    }
    
    // Similar to VAO's, first generate, then bind to ID.
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Wraps are for repeating of textures.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filters are linear or nearest, nearest gives a more pixelated look, linear gives a more blending look.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Texture itself, mipmaps, data type, width, height, always 0, load type, char is byte so Unsigned byte, texdata.
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Release the Bind.
    glBindTexture(GL_TEXTURE_2D, 0);
    // Release stbi.
    stbi_image_free(textureData);

    return true;
}

void Texture::UseTexture(){

    // GL_TEXTURE0 is unit texture.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture(){

    glDeleteTextures(1, &textureID);
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = "";
}

Texture::~Texture(){

    ClearTexture();
}