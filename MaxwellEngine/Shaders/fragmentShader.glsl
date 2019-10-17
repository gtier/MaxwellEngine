
#version 330 core
out vec4 FragColor;

in vec2 uv;

uniform sampler2D customTexture;

void main()
{
    FragColor = texture(customTexture, uv);
} 