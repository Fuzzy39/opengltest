#ifndef glTest_h
#define glTest_h
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <Shader.hpp>

extern int numPoints;

struct Vertex
{
public:
    float x;
    float y;
    float z;
    float angle; // radians


    Vertex(float x, float y, float z, float angle);
    static Vertex fromAngle(float theta);
    static Vertex* makeVerticies(int points, int* count); // returns an array of verticies number+1 in size
};



//GLFW 'events'
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);

// setup
bool setup(GLuint* VertexArrayObject, GLFWwindow** window);
GLuint SetupVertexArrayObj();



// functions for runtime/post setup
void renderTriangle(GLuint VertexArrayObject, Shader& shader);


// util
// t - from 0 to period
// phaseAngle - in rotations!
// returns a value from 0 to 1.
float sinusoid(float t, float period, float phaseAngle);

#endif // !glTest_h