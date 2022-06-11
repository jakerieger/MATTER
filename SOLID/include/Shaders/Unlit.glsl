R""(
@VERTEX
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP;

out vec2 TexCoords;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
}
@ENDVERTEX

@FRAGMENT
out vec4 FragColor;
in vec2 TexCoords;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
@ENDFRAGMENT
)"";