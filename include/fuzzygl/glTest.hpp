#ifndef glTest_h
#define glTest_h

#include <common_includes.hpp>
#include <fuzzygl/world/World.hpp>





//GLFW 'events'
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);
void key_callback (GLFWwindow *window, int key, int scancode, int action, int mods);
void mouseUpdate(GLFWwindow* window);



// setup
bool setup(GLFWwindow** window);





#endif // !glTest_h