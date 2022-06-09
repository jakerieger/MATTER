@VERTEX
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
@ENDVERTEX

@FRAGMENT
#define MAX_NUM_TOTAL_LIGHTS 100

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform int numPointLights;

uniform vec3 viewPosition;

uniform Material uMaterial;
uniform DirectionalLight uDirectionalLight;
uniform PointLight uPointLights[MAX_NUM_TOTAL_LIGHTS];

// Function prototypes
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);

/**
    There are lot of duplicated calculations in this approach spread out over the light type functions 
    (e.g. calculating the reflect vector, diffuse and specular terms, and sampling the material textures) 
    so there's room for optimization here.
**/

void main() {
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDirection = normalize(viewPosition - FragPos);

    // Phase 1: Directional lighting
    vec3 result = CalcDirectionalLight(uDirectionalLight, norm, viewDirection);

    // Phase 2: Point lighting
    for (int i = 0; i < numPointLights; i++) {
        result += CalcPointLight(uPointLights[i], norm, FragPos, viewDirection);
    }

    // Phase 3: Spot lighting

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
    vec3 lightDirection = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0);

    // specular shading
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), uMaterial.shininess);

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    if (uMaterial.diffuse != 0) {
        ambient  = light.ambient  *        texture(uMaterial.diffuse,  TexCoords).rgb;
        diffuse  = light.diffuse  * diff * texture(uMaterial.diffuse,  TexCoords).rgb;
    } else {
        ambient  = light.ambient;
        diffuse  = light.diffuse * diff;
    }

    if (uMaterial.specular != 0) {
        specular = light.specular * spec * texture(uMaterial.specular, TexCoords).rgb;
    } else {
        specular = light.specular * spec;
    }

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0);
    // specular shading
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), uMaterial.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    if (uMaterial.diffuse != 0) {
        ambient  = light.ambient  *        texture(uMaterial.diffuse,  TexCoords).rgb;
        diffuse  = light.diffuse  * diff * texture(uMaterial.diffuse,  TexCoords).rgb;
    } else {
        ambient  = light.ambient;
        diffuse  = light.diffuse * diff;
    }

    if (uMaterial.specular != 0) {
        specular = light.specular * spec * texture(uMaterial.specular, TexCoords).rgb;
    } else {
        specular = light.specular * spec;
    }

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
@ENDFRAGMENT