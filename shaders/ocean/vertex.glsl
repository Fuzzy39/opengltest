#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inTexPos;

// Ocean

uniform float time; 
uniform float offset; 
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 perspectiveMat;

out vec4 color;
out vec2 texPos;

float sinusoid(float t)
{
    const float M_PI = 3.1415926535897932384626433832795;
    float th = t * 2 * M_PI;
    float PI3 = M_PI*2.0f/3.0f;
    return (sin(t)+1)/2.0f;
}
    
void main()
{
    bool doDarkening = false;

    const float M_PI = 3.1415926535897932384626433832795;
    texPos = inTexPos;

    vec3 pos = vec3(aPos.x, aPos.y, -aPos.z*(sinusoid(time+offset)*.4+1.5));
    gl_Position = perspectiveMat * viewMat  * modelMat * vec4(pos, 1.0f);
   
    float maxBright = 15;
    float minBright = 3;
   
    
    float bright =min(1-((gl_Position.z-maxBright)/(minBright-maxBright)),1);

    bright = bright*.5f;
    float to = (sin(time+offset+(M_PI/4.0f))+1)/2.0f;
    color = vec4(.25f+.1*to,.55f+.2*to,.75f+.2*to, 1.0f);
    float sudStart = .95;
    float suds = max(0, to-sudStart)*(1.0f/(1-sudStart));
    color = mix(color, vec4(.6,.9,1,1), suds);
    //color = vec4(.4,.6,.8, 1.0f);

    if(doDarkening)
    {
        color = (color*.5f)+vec4(bright, bright, bright, 1.0);
    }
   
   
}