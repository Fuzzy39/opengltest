#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float theta;
layout (location = 2) in vec2 inTexPos;


uniform float time;
uniform mat4 transform;

out vec4 color;
out vec2 texPos;
    
void main()
{
    const float M_PI = 3.1415926535897932384626433832795;


    float texSpeed = 5;
    float texMax = 2;
    float colorMag = .5;
    float speed = 30;

    texPos = inTexPos*(((texMax-1)*((cos(texSpeed*time+M_PI)+1)/2))+1);

   
    gl_Position =  transform*vec4(aPos, 1.0f);
    //gl_Position = vec4(cos(-.261*time+theta)*length(aPos), sin(-.773*time+theta)*length(aPos), aPos.z, 1.0);
    
    
    if(theta == -1) 
    {
        color = vec4(1.0, 1.0, 1.0, 1.0);
        return;
    }

   
    color = vec4
    ( 
        (sin(theta+speed*time)+1)/4.0+colorMag, 
        (sin(theta+speed*time+(2*M_PI)/3)+1)/4.0+colorMag, 
        (sin(theta+speed*time+(4*M_PI)/3)+1)/4.0+colorMag,
        1.0
    );
}