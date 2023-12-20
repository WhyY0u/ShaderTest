#version 330 core
in vec3 VertexCoord;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 color;
uniform vec2 size;

float roundedBoxSDF(vec2 CenterPosition, vec2 Size, float Radius) {
    return length(max(abs(CenterPosition) - Size + Radius, 0.0)) - Radius;
}

void main() {
    float radius         = 30.0;
    float edgeSoftness   = 1.0;
    vec2 center          = size / 2.0;
    float distance       = roundedBoxSDF(center - gl_FragCoord.xy, center, radius);
    float smoothedAlpha  = 1.0 - smoothstep(-edgeSoftness, edgeSoftness, distance);
    FragColor = vec4(color, smoothedAlpha);
}