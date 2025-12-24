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
        world->addCamera();
        world->getCamera(1)->setPosition(glm::vec3(8,8,8));
        world->getCamera(1)->lookAt(glm::vec3(0,0,0));
        world->addCamera();
        world->getCamera(2)->setPosition(glm::vec3(8,8,8));
        world->getCamera(2)->lookAt(glm::vec3(0,0,0));

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
       // disk->draw();

        // fiddle with the camera.

        adjustCamera(*world);
        world->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }


    glfwTerminate();
    std::cout<<"Goodbye!\n";
    return 0;
}


void adjustCamera(World& world)
{
    static int camActive = 0;

    Camera* cam = &(*world.getCamera(0));
  
    float switchPeriod = 8.0f;
    float cameraPeriod = 10.0f/(2*M_PI);

    cam->setPosition(glm::vec3(
        1*sin(2*glfwGetTime()/cameraPeriod), 
        .2*cos(2*glfwGetTime()/cameraPeriod),
        4 - 2 * sin(glfwGetTime()/cameraPeriod)
    ));
  
    cam->lookAt(glm::vec3(0));
    cam->pitch(.5 * cos(glfwGetTime()/cameraPeriod));
    cam->yaw(.5 * cos(2*glfwGetTime()/cameraPeriod));
    cam->roll(.5 * cos(4*glfwGetTime()/cameraPeriod));

 
    cam = &(*world.getCamera(1));
    cam->setPosition(glm::vec3(
        10*cos(glfwGetTime()/cameraPeriod), 
        8,
        10 * sin(glfwGetTime()/cameraPeriod)
    ));
    cam->lookAt(glm::vec3(0));
    

    // int newCam = (int)(glfwGetTime()/switchPeriod)%2;
    // if(newCam!=camActive)
    // {
    //     world.setActiveCamera(newCam);
    //     camActive = newCam;
    // }
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
 
    glm::vec3 move = glm::vec3(0);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        move= move + glm::vec3(0,0,1);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        move= move + glm::vec3(0,0,-1);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        move= move + glm::vec3(-1,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        move= move + glm::vec3(1,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        move= move + glm::vec3(0,1,0);
    }
     if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        move= move + glm::vec3(0,-1,0);
    }
    if(glm::length(move)!=0)
    {
        move = .2f * glm::normalize(move);
        Camera* cam = &(*world->getCamera(2));
        cam->translate(move);
        cam->lookAt(glm::vec3(0));
    }
}

void key_callback (GLFWwindow *window, int key, int scancode, int action, int mods)
{
    static int camActive = 0;

    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
        camActive = (camActive+1) %3;
        world->setActiveCamera(camActive);

    }
}

