
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inUv;

out vec4 outColor;
out vec2 uv;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = inUv;
}