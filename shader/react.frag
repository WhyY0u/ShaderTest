#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 color;
uniform vec2 size;
uniform vec2 location;

float calculator(vec2 p, vec2 b, float normalizedRadius) { 
    return length(max(abs(p) - b + normalizedRadius, 0.0)) - normalizedRadius;
}



void main() {
    float edgeSoftness = 2.0;
    vec2 center = size * 0.5;
    float relativeRadius = 0.1;  // 10% от размера фигуры
    float radius = relativeRadius * min(size.x, size.y);
    
    float distance = calculator(center - (TexCoord * size), center, radius);
    float smoothedAlpha = 1.0 - smoothstep(-edgeSoftness, edgeSoftness, distance);
    
    FragColor = vec4(color, smoothedAlpha);
}
