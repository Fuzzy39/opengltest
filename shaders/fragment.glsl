#version 330 core

out vec4 FragColor;
in vec4 color;
in vec2 texPos;

uniform float time;
uniform mat4 transform;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
    float side = sign(transform*vec4(0,0,1,1)).z;

    FragColor = mix(texture(tex2, texPos), texture(tex, texPos), ((side*cos(0))+1)/2 )*color; 
}