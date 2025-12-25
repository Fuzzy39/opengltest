#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inTexPos;


uniform float time; 
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 perspectiveMat;

out vec4 color;
out vec2 texPos;

vec4 sinusoid(float t)
{
    const float M_PI = 3.1415926535897932384626433832795;
    float th = t * 2 * M_PI;
    float PI3 = M_PI*2.0f/3.0f;
    return vec4((sin(t)+1)/2, (sin(t+PI3)+1)/2, (sin(t+2*PI3)+1)/2, 1.0);
}
    
void main()
{
    bool doDarkening = true;

    const float M_PI = 3.1415926535897932384626433832795;
    texPos = inTexPos;

  
    gl_Position = perspectiveMat * viewMat  * modelMat * vec4(aPos, 1.0f);
   
    float maxBright = 10;
    float minBright = 2;
    
    float bright =min(1-((gl_Position.z-maxBright)/(minBright-maxBright)),1);

    bright = bright*.5f;
    color = sinusoid(time);
    if(doDarkening)
    {
        color = (color*.5f)+vec4(bright, bright, bright, 1.0);
    }
   
   
}