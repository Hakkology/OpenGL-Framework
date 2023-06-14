#include "../../Header/Shader/ShaderProgram.h"

ShaderProgram::ShaderProgram(GLuint shaderID)
    : m_shaderID(shaderID)
{
    retrieveUniformLocations();
}

ShaderProgram::~ShaderProgram()
{
    // Destructor implementation
}

void ShaderProgram::retrieveUniformLocations()
{
    // Retrieve uniform locations using glGetUniformLocation function
    // Assign the values to the corresponding member variables

    // Example for retrieving directional light uniform locations
    retrieveDirectionalLightUniformLocations();

    // Example for retrieving point light uniform locations
    retrievePointLightUniformLocations();

    // Example for retrieving spot light uniform locations
    retrieveSpotLightUniformLocations();

    // Retrieve other uniform locations
}

void ShaderProgram::retrieveDirectionalLightUniformLocations()
{
    // Retrieve uniform locations for directional light and assign them to the member variables
}

void ShaderProgram::retrievePointLightUniformLocations()
{
    // Retrieve uniform locations for point lights and assign them to the member variables
}

void ShaderProgram::retrieveSpotLightUniformLocations()
{
    // Retrieve uniform locations for spot lights and assign them to the member variables
}
