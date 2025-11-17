#include <glad/gl.h>
#include "gl.c"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  


double randomDouble()
{
    int r = rand(); 
    return ((double)r)/RAND_MAX;
}

void handleInput(GLFWwindow* window)
{
    static bool enterPressed = false;
    // sample code
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);  
    }

    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        enterPressed = true;
    }
    else
    {
        if(enterPressed)
        {
            glClearColor(randomDouble(), randomDouble(), randomDouble(), 1.0f);
        }
        enterPressed = false;
    }

}

int  main(int argc, char** argv)
{

    srand(time(NULL));   // Initialization, should only be called once.

    std::cout<<"Hello!\n";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac I guess


    // create a window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL???", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    
    // setup viewport
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // main loop
    while(!glfwWindowShouldClose(window))
    {
        handleInput(window);

        // clear the buffer with a color.
       
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    std::cout<<"Goodbye!\n";
    return 0;
}