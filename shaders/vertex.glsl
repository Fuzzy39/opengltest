#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float theta;

uniform float time;
out vec4 color;
    
void main()
{
    const float M_PI = 3.1415926535897932384626433832795;
    gl_Position = vec4(cos(-.261*time+theta)*length(aPos), sin(-.773*time+theta)*length(aPos), aPos.z, 1.0);
    if(theta == -1) 
    {
        color = vec4(1.0, 1.0, 1.0, 1.0);
        return;
    }

    color = vec4
    ( 
        (sin(theta+time)+1)/2.0, 
        (sin(theta+time+(2*M_PI)/3)+1)/2.0, 
        (sin(theta+time+(4*M_PI)/3)+1)/2.0,
        1.0
    );
}