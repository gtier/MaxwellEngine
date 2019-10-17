
#version 330 core
out vec4 FragColor;

in vec2 uv;

//ENGINE NEEDS THESE UNIFORMS. DO NOT DELETE OR AUGMENT.
uniform sampler2D user_texture_0;
uniform sampler2D user_texture_1;
uniform sampler2D user_texture_2;
uniform sampler2D user_texture_3;
uniform sampler2D user_texture_4;
uniform sampler2D user_texture_5;
uniform sampler2D user_texture_6;
uniform sampler2D user_texture_7;
//

void main()
{
    FragColor = texture(user_texture_0, uv);
} 
