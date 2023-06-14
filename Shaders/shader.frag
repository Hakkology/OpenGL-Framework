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
uniform Material material;

uniform vec3 eyePosition;

float CalculateDirectionalShadowFactor(DirectionalLight light){

    vec3 projCoords = directionalLightSpacePos.xyz / directionalLightSpacePos.w;
    projCoords = (projCoords * 0.5f) + 0.5f;

    float closest = texture(directionalShadowMap, projCoords.xy).r;
    float current = projCoords.z;

    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

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

vec4 CalculatePointLight(PointLight pointLight) {

    vec3 direction = FragPos - pointLight.position;
    float distance = length(direction);
    direction = normalize(direction);

    vec4 lightColour = CalculateLightByDirection(pointLight.base, direction, 0.0f);
    float attenuation = pointLight.exponent * distance * distance +
                        pointLight.linear * distance +
                        pointLight.constant;

    return (lightColour / attenuation);

}

vec4 CalculateSpotLight (SpotLight spotLight){

    vec3 rayDirection = normalize(FragPos - spotLight.base.position);
    float spotLightFactor = dot (rayDirection, spotLight.direction);

    if(spotLightFactor > spotLight.edge){

        vec4 lightColour = CalculatePointLight (spotLight.base);
        return lightColour * (1.0f - (1.0f - spotLightFactor) * (1.0f/(1.0f - spotLight.edge)));

    } else {
        return vec4 (0, 0, 0, 0);
    }
}

vec4 CalculatePointLights(){

    vec4 totalColour = vec4(0,0,0,0);
    for(int i =0; i < pointLightCount; i++){

        totalColour += CalculatePointLight(pointLights[i]);
    }

    return totalColour;
}

vec4 CalculateSpotLights(){

    vec4 totalColour = vec4(0,0,0,0);
    for(int i =0; i < spotLightCount; i++){

        totalColour += CalculateSpotLight(spotLights[i]);
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