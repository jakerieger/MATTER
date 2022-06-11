@VERTEX
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
    TexCoord = aTexCoord;
    gl_Position = vec4(aPos, 1.0);
}
@ENDVERTEX

@FRAGMENT
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D splashTexture;

void main() {
    FragColor = texture(splashTexture, TexCoord);
}
@ENDFRAGMENT