@VERTEX
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP;

void main() {
    // we read the multiplication from right to left
    gl_Position = MVP * vec4(aPos, 1.0);
}
@ENDVERTEX

@FRAGMENT
out vec4 FragColor;

struct Material {
    vec4 diffuse;
    sampler2D diffuseTexture;
};

uniform Material material;

void main() {
    FragColor = material.color;
}
@ENDFRAGMENT