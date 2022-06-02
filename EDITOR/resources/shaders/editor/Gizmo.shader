@VERTEX
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
    FragPos = aPos;
    Normal = aNormal;
    TexCoord = aTexCoord;
}
@ENDVERTEX

@FRAGMENT
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D gizmoTexture;

void main() {
    FragColor = texture(gizmoTexture, TexCoord);
}
@ENDFRAGMENT