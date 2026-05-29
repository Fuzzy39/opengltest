#version 330 core

out vec4 FragColor;
in vec4 color;
in vec2 texPos;

uniform mat4 modelMat;

uniform sampler2D tex;

void main()
{
   //texture(tex, texPos)
    FragColor = texture(tex, texPos)*color;
}
