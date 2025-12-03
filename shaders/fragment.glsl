#version 330 core

out vec4 FragColor;
in vec4 color;
in vec2 texPos;

uniform sampler2D tex;


void main()
{
    FragColor = texture(tex, texPos)*color; 
}