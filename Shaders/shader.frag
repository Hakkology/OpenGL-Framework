#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 directionalLightSpacePos;

out vec4 colour;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light{
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight{
    Light base;
    vec3 direction;
};

struct OmniShadowMap{
    samplerCube shadowMap;
    float farPlane;
};

struct PointLight{
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};

struct SpotLight{
    PointLight base;
    vec3 direction;
    float edge;
};

struct Material{
    float specularIntensity;
    float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights [MAX_POINT_LIGHTS];
uniform SpotLight spotLights [MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;
uniform OmniShadowMap omniShadowMaps[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];
uniform Material material;

uniform vec3 eyePosition;

vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float CalculateDirectionalShadowFactor(DirectionalLight light){

    vec3 projCoords = directionalLightSpacePos.xyz / directionalLightSpacePos.w;
    projCoords = (projCoords * 0.5f) + 0.5f;

    float closestDepth = texture(directionalShadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.direction);

    float bias = max(0.05 *(1- dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 /textureSize(directionalShadowMap, 0);

    for(int x =-1; x <= 1; ++x){
        for(int y =-1; y <= 1; ++y){

            float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x,y) * texelSize).r;
            shadow += (currentDepth - bias) > pcfDepth ? 1.0 : 0.0;
        }
    }

    shadow /= 9.0;

    if(projCoords.z > 1.0){

        shadow = 0;
    }

    return shadow;
}

float CalculateOmniShadowFactor(PointLight light, int shadowIndex){

	vec3 fragToLight = FragPos - light.position;
	float currentDepth = length(fragToLight);
	
	float shadow = 0.0;
	float bias   = 0.15;
	int samples  = 20;
	float viewDistance = length(eyePosition - FragPos);
	float diskRadius = (1.0 + (viewDistance / omniShadowMaps[shadowIndex].farPlane)) / 25.0;

	for(int i = 0; i < samples; ++i)
	{
		float closestDepth = texture(omniShadowMaps[shadowIndex].shadowMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
		closestDepth *= omniShadowMaps[shadowIndex].farPlane;   // Undo mapping [0;1]
		if(currentDepth - bias > closestDepth) shadow += 1.0;
	}

	shadow /= float(samples);  
	return shadow;
}

vec4 CalculateLightByDirection(Light light, vec3 direction, float shadowFactor){

    vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;

    float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
    vec4 diffuseColour = vec4(light.colour, 1.0f) * light.diffuseIntensity * diffuseFactor;

    vec4 specularColour = vec4(0, 0, 0, 0);

    if(diffuseFactor > 0.0f){
        vec3 fragToEye = normalize(eyePosition - FragPos);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));

        float specularFactor = dot (fragToEye, reflectedVertex);
        if(specularFactor > 0.0f){
            specularFactor = pow(specularFactor, material.shininess);
            specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
        }
    }

    return (ambientColour + (1 - shadowFactor) * (diffuseColour + specularColour));
}

vec4 CalculateDirectionalLight(){

    float shadowFactor = CalculateDirectionalShadowFactor(directionalLight);
    return CalculateLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 CalculatePointLight(PointLight pointLight, int shadowIndex) {

    vec3 direction = FragPos - pointLight.position;
    float distance = length(direction);
    direction = normalize(direction);

    float shadowFactor = CalculateOmniShadowFactor(pointLight, shadowIndex);

    vec4 lightColour = CalculateLightByDirection(pointLight.base, direction, shadowFactor);
    float attenuation = pointLight.exponent * distance * distance +
                        pointLight.linear * distance +
                        pointLight.constant;

    return (lightColour / attenuation);

}

vec4 CalculateSpotLight (SpotLight spotLight, int shadowIndex){

    vec3 rayDirection = normalize(FragPos - spotLight.base.position);
    float spotLightFactor = dot (rayDirection, spotLight.direction);

    if(spotLightFactor > spotLight.edge){

        vec4 lightColour = CalculatePointLight (spotLight.base, shadowIndex);
        return lightColour * (1.0f - (1.0f - spotLightFactor) * (1.0f/(1.0f - spotLight.edge)));

    } else {
        return vec4 (0, 0, 0, 0);
    }
}

vec4 CalculatePointLights(){

    vec4 totalColour = vec4(0,0,0,0);
    for(int i =0; i < pointLightCount; i++){

        totalColour += CalculatePointLight(pointLights[i], i);
    }

    return totalColour;
}

vec4 CalculateSpotLights(){

    vec4 totalColour = vec4(0,0,0,0);
    for(int i =0; i < spotLightCount; i++){

        totalColour += CalculateSpotLight(spotLights[i], i + pointLightCount);
    }

    return totalColour;

}

void main()
{
    vec4 finalColour = CalculateDirectionalLight();
    finalColour += CalculatePointLights();
    finalColour += CalculateSpotLights();

    colour= texture(theTexture, TexCoord) * finalColour;


    
}