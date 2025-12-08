#ifndef glTest_h
#define glTest_h

// std library
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


// Opengl, GlFW, etc.
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// our stuff
#include <Shader.hpp>






//GLFW 'events'
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);

// setup
bool setup(GLFWwindow** window);
GLuint MakeTexture(const char* path);





#endif // !glTest_h