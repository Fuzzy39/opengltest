#version 330 core

out vec4 FragColor;
in vec4 color;
in vec2 texPos;

uniform float time;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
    FragColor = mix(texture(tex2, texPos), texture(tex, texPos),(sin(time)+1)/2)*color; 
}