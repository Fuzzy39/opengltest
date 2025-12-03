#ifndef glTest_h
#define glTest_h

// std library
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


// Opengl, GlFW, etc.
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// our stuff
#include <Shader.hpp>

extern int numPoints;




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