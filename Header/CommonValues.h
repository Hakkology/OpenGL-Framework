#ifndef COMMON_VALUES_H
#define COMMON_VALUES_H

#include "stb_image.h"

// Shader assignments

// Vertex Shader
static const char* vShader = "../Shaders/shader.vert";
static const char* vShadowShader = "../Shaders/directional_shadow_map.vert";
static const char* vOmniShadowShader = "../Shaders/omni_shadow_map.vert";
static const char* vSkyboxShader = "../Shaders/Skybox.vert";

// Geometry Shader
static const char* gOmniShadowShader = "../Shaders/omni_shadow_map.geom";

// Fragment Shader
static const char* fShader = "../Shaders/shader.frag";
static const char* fShadowShader = "../Shaders/directional_shadow_map.frag";
static const char* fOmniShadowShader = "../Shaders/omni_shadow_map.frag";
static const char* fSkyboxShader = "../Shaders/Skybox.frag";

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

#endif 