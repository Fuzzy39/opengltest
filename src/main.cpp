#include "glTest.hpp"
#include <Shader.hpp>

int frame = 0;

int  main(int argc, char** argv)
{

    
    srand(time(NULL));   // Initialization, should only be called once.
    std::cout << "Hello!\n";
   
    GLuint VertexArrayObject;
    GLFWwindow* window;
    Shader* shader;
 
   
    if (!setup( &VertexArrayObject, &window)) // this is ugly.
    {
        return -1;
    }
   
    try
    {
        shader= new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    }
    catch(std::exception e)
    {
        return -1;
    }

    // main loop
    while(!glfwWindowShouldClose(window))
    {
        handleInput(window);
        frame++;

        // clear the buffer with a color.
        glClearColor(.2f, .2f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderTriangle(VertexArrayObject, *shader);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    delete shader;
    glfwTerminate();
    std::cout<<"Goodbye!\n";
    return 0;
}

// is this how it works?
void renderTriangle(GLuint VertexArrayObject, Shader& shader)
{

    // int uniformLocation = glGetUniformLocation(shader.getHandle(), "");
    // shader.use();
    // glUniform1f(uniformLocation, value);

    //shader.use(); // don't forget to activate the shader before setting uniforms!  
    shader.setInt("tex", 0); 
    shader.setInt("tex2", 1);
   

    float time = glfwGetTime();
    float period = 6.0f;

    shader.setFloat("time", (time*2*M_PI)/period);

    // you have to use a uniform after useing the shader program;
    // setting the unifrom requires it.
    
    // Do things (TM!)
    glBindVertexArray(VertexArrayObject);
    
    glDrawArrays(GL_TRIANGLES, 0, numPoints*3);//(int)(time*(7/period))%7+2);


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

float sinusoid(float t, float period, float phaseAngle)
{
    float progressRadians = (t*2.0f*M_PI)/period;
    float phaseAngleRadians = 2.0f*M_PI*phaseAngle;
    return (sinf(progressRadians+phaseAngleRadians)+1.0f)/2.0f;
}