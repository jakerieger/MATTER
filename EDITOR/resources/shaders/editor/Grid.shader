@VERTEX
layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;

out vec3 nearPoint;
out vec3 farPoint;
out mat4 fragView;
out mat4 fragProj;

vec3 gridPlane[6] = vec3[](
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

vec3 UnprojectPoint(vec3 point, mat4 _view, mat4 _proj) {
    mat4 vInv = inverse(_view);
    mat4 pInv = inverse(_proj);
    vec4 uP = vInv * pInv * vec4(point, 1.0);
    return uP.xyz / uP.w;
}

void main() {
    vec3 p = gridPlane[gl_VertexID].xyz;

    nearPoint = UnprojectPoint(vec3(p.xy, 0.0), view, projection).xyz;
    farPoint = UnprojectPoint(vec3(p.xy, 1.0), view, projection).xyz;

    fragView = view;
    fragProj = projection;

    gl_Position = vec4(p, 1.0);
}
@ENDVERTEX

@FRAGMENT
precision highp float;
out vec4 FragColor;

in vec3 nearPoint;
in vec3 farPoint;
in mat4 fragView;
in mat4 fragProj;

uniform vec3 gridLineColor;
uniform vec3 xAxisColor;
uniform vec3 zAxisColor;

uniform float near;
uniform float far;

// float near = 0.01;
// float far = 100.0;

vec4 grid(vec3 fragPos3D, float scale, bool drawAxis) {
    vec2 coord = fragPos3D.xz * scale; // use the scale variable to set the distance between the lines
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(gridLineColor, 1.0 - min(line, 1.0));

    // z axis
    if(fragPos3D.x > -0.1 * minimumx && fragPos3D.x < 0.1 * minimumx)
        color.xyz = zAxisColor;

    // x axis
    if(fragPos3D.z > -0.1 * minimumz && fragPos3D.z < 0.1 * minimumz)
        color.xyz = xAxisColor;

    return color;
}

float computeDepth(vec3 pos) {
    vec4 clip_space_pos = fragProj * fragView * vec4(pos.xyz, 1.0);
    return (clip_space_pos.z / clip_space_pos.w);
}

float computeLinearDepth(vec3 pos) {
    vec4 clip_space_pos = fragProj * fragView * vec4(pos.xyz, 1.0);
    float clip_space_depth = (clip_space_pos.z / clip_space_pos.w) * 2.0 - 1.0; // put back between -1 and 1
    float linearDepth = (2.0 * near * far) / (far + near - clip_space_depth * (far - near)); // get linear value between 0.01 and 100
    return linearDepth / far; // normalize
}

void main() {
    float t = -nearPoint.y / (farPoint.y - nearPoint.y);
    vec3 fragPos3D = nearPoint + t * (farPoint - nearPoint);

    gl_FragDepth = computeDepth(fragPos3D);

    float linearDepth = computeLinearDepth(fragPos3D);
    float fading = max(0, (0.5 - linearDepth));

    vec4 outColor = grid(fragPos3D, 10, true) * float(t > 0);
	// outColor.w *= fading;
    FragColor = outColor;
}
@ENDFRAGMENT