#include <fuzzygl/glTest.hpp>
#include <fuzzygl/Disk.hpp>
#include <fuzzygl/resources/ResourceManager.hpp>
#include <fuzzygl/world/World.hpp>

static World* world = nullptr;

int  main(void)
{
    // config
    int sides = 100;
    int textures = 5;
    float period = 10.0f;

    srand((unsigned int)time(NULL));   // Initialization, should only be called once.
    std::cout << "Hello!\n";
   
    Disk* disk = nullptr;

    GLFWwindow* window;
 
 
   
    if (!setup( &window)) // this is ugly.
    {
        return -1;
    }
   
    try
    {
        // disk!
        
        ResourceManager::instance();

        // calculate the aspect ratio
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float aspectRatio = ((float)width)/height;

        world = new World(aspectRatio);


        disk = new Disk(sides, textures);
    }
    catch(std::exception e)
    {
        return -1;
    }

    // main loop
    while(!glfwWindowShouldClose(window))
    {
        handleInput(window);

        // clear the buffer with a color.
        glClearColor(.2f, .2f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        disk->setTime( glfwGetTime()/period);
        disk->draw();
        world->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }


    glfwTerminate();
    std::cout<<"Goodbye!\n";
    return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    float aspectRatio = ((float)width)/height;
    world->updateAspectRatio(aspectRatio);

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

