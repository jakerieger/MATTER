# Shaders

Shaders are written in a slightly modified version of GLSL (OpenGL Shading Language) where the vertex and fragment components are combined in to one `.shader` file.
Vertex and Fragment shaders are defined by an opening and closing tag like so:

```c
@VERTEX
void main() {

}
@ENDVERTEX

@FRAGMENT
void main() {

}
@ENDFRAGMENT
```

The `#version XXX` header can be omitted as the OpenGL version the engine is configured with will be used.