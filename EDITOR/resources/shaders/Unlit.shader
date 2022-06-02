@VERTEX
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main() {
    // we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoords = aTexCoord;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
}
@ENDVERTEX

@FRAGMENT
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewPos = vec3(0.0, 0.0, 4.0);
    vec3 viewDirection = normalize(viewPos - FragPos);

    DirectionalLight light = DirectionalLight(
        vec3(-0.2, 0.0, -0.3),
        vec3(0.2, 0.2, 0.2),
        vec3(0.8, 0.8, 0.8),
        vec3(1.0, 1.0, 1.0)
    );

    vec3 result = CalcDirectionalLight(light, norm, viewDirection);

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
    vec3 lightDirection = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0);

    // specular shading
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32.0);

    // combine results
    vec3 ambient  = light.ambient  *        texture(texture_diffuse1,  TexCoords).rgb;
    vec3 diffuse  = light.diffuse  * diff * texture(texture_diffuse1,  TexCoords).rgb;
    // vec3 specular = light.specular * spec * texture(texture_specular1, TexCoords).rgb;

    return (ambient + diffuse);
}
@ENDFRAGMENT