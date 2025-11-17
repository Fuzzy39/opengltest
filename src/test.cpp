#include <glad/gl.h>
#include "gl.c"
#include <GLFW/glfw3.h>
#include <iostream>

// I guess it's triangle time?
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

// this seems terrible
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  


void handleInput(GLFWwindow* window)
{
    // sample code
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);  
    }
}

// is this how it works?
void renderTriangle()
{
    unsigned int VertexBufferObject;
    glGenBuffers(1, &VertexBufferObject);
    
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject); //assign VectexBufferObject as an array buffer (of which there can only be one?)

    // copy data to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

    // SETUP shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);


glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);

    // main loop
    while(!glfwWindowShouldClose(window))
    {
        handleInput(window);

        // clear the buffer with a color.
        glClearColor(.1f, .2f, .2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    std::cout<<"Goodbye!\n";
    return 0;
}