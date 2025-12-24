#ifndef glTest_h
#define glTest_h

#include <common_includes.hpp>
#include <fuzzygl/world/World.hpp>





//GLFW 'events'
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handleInput(GLFWwindow* window);
void key_callback (GLFWwindow *window, int key, int scancode, int action, int mods);


// setup
bool setup(GLFWwindow** window);

// main
void adjustCamera(World& world);




#endif // !glTest_h