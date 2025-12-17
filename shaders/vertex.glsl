#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inTexPos;



uniform mat4 modelMat;
uniform mat4 perspectiveMat;

out vec4 color;
out vec2 texPos;
    
void main()
{
    const float M_PI = 3.1415926535897932384626433832795;

    texPos = inTexPos;

    gl_Position = perspectiveMat * modelMat * vec4(aPos, 1.0f);
   
    float min = 5;
    float bright =1-(gl_Position.z/min);
    color = vec4(bright, bright, bright, 1.0);
   
   
}