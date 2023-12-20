#version 330 core
in vec2 TexCoords;
out vec4 FragColor;
uniform float alpha;
uniform vec3 color;
uniform sampler2D textur;


void main() {
    FragColor = vec4(color, texture(textur, vec2(TexCoords.x, 1.0 - TexCoords.y)).r * alpha);
}
