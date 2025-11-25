#include "glTest.hpp"

int frame = 0;

int  main(int argc, char** argv)
{

    srand(time(NULL));   // Initialization, should only be called once.
    std::cout << "Hello!\n";
   
    GLuint shaderProgram, VertexArrayObject;
    GLFWwindow* window;
    if (!setup(&shaderProgram, &VertexArrayObject, &window)) // this is ugly.
    {
        return -1;
    }
   

    // main loop
    while(!glfwWindowShouldClose(window))
    {
        handleInput(window);
        frame++;

        // clear the buffer with a color.
        glClearColor(.4f, .6f, .8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderTriangle(VertexArrayObject, shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    std::cout<<"Goodbye!\n";
    return 0;
}

// is this how it works?
void renderTriangle(GLuint VertexArrayObject, GLuint shaderProgram)
{

    // Do things (TM!)
    glUseProgram(shaderProgram);
    glBindVertexArray(VertexArrayObject);
   
     
    
     glDrawArrays(GL_TRIANGLES, (frame/30)%4, 3);
   

    // glDrawArrays(GL_TRIANGLES, 3, 3);

}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void handleInput(GLFWwindow* window)
{
    // sample code
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}