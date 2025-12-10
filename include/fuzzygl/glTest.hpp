#ifndef glTest_h
#define glTest_h

#include <common_includes.hpp>






//GLFW 'events'
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);

// setup
bool setup(GLFWwindow** window);






#endif // !glTest_h