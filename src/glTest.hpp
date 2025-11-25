#ifndef glTest_h
#define glTest_h
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>




//GLFW 'events'
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);

// setup
bool setup(GLuint* shaderProgram, GLuint* VertexArrayObject, GLFWwindow** window);
bool compileShaders(GLuint* shaderProgram);
GLuint SetupVertexArrayObj();



// functions for runtime/post setup
void renderTriangle(GLuint VertexArrayObject, GLuint shaderProgram);

#endif // !glTest_h