#version 330 core
in vec2 TexCoord, VertexCord;
out vec4 FragColor;
uniform sampler2D textur;

void main() {
    FragColor = texture(textur, TexCoord);
}
