#ifndef COMMON_VALUES_H
#define COMMON_VALUES_H

#include "stb_image.h"

// Window values
const int WINDOW_WIDTH = 1366;
const int WINDOW_HEIGHT = 788;

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

const float toRadians = 3.14159265f / 180.0f;

// Texture paths
static const char* brickTexturePath = "../Resources/Textures/Ground/brick.png";
static const char* dirtTexturePath = "../Resources/Textures/Ground/dirt.png";
static const char* plainTexturePath = "../Resources/Textures/Ground/plain.png";

// Model paths
static const char* treeModelPath = "../Resources/Models/Model/Tree.obj";
static const char* lampModelPath = "../Resources/Models/Model/uploads_files_2809625_Light.obj";
static const char* statueModelPath = "../Resources/Models/Model/12334_statue_v1_l3.obj";

// Skybox paths
static const char* skyboxRtPath = "../Resources/Models/Texture/Skybox/cupertin-lake_rt.tga";
static const char* skyboxLfPath = "../Resources/Models/Texture/Skybox/cupertin-lake_lf.tga";
static const char* skyboxUpPath = "../Resources/Models/Texture/Skybox/cupertin-lake_up.tga";
static const char* skyboxDnPath = "../Resources/Models/Texture/Skybox/cupertin-lake_dn.tga";
static const char* skyboxBkPath = "../Resources/Models/Texture/Skybox/cupertin-lake_bk.tga";
static const char* skyboxFtPath = "../Resources/Models/Texture/Skybox/cupertin-lake_ft.tga";

#endif 