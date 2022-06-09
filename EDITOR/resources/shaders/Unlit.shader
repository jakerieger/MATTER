@VERTEX
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP;

out vec2 TexCoord;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
@ENDVERTEX

@FRAGMENT
out vec4 FragColor;

in vec2 TexCoord;

struct Material {
    vec4 diffuse;
    sampler2D texture;
    int hasTexture;
};

uniform Material material;

void main() {
    vec4 outColor = material.diffuse;

    if (material.hasTexture == 1) {
        outColor *= texture(material.texture, TexCoord);
    }

    FragColor = outColor;
}
@ENDFRAGMENT
