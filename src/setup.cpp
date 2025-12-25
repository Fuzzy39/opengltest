#include <fuzzygl/glTest.hpp>
#include <fuzzygl/resources/ResourceManager.hpp>

bool setup(GLFWwindow** window)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac I guess


    // create a window object
    *window = glfwCreateWindow(800, 800, "OpenGL???", NULL, NULL);

    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
  
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }


    // setup viewport
    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
    glfwSetKeyCallback(*window, key_callback);

   
    //glDepthRange(-1,1);
    //glDepthFunc(GL_NOTEQUAL);
    glEnable (GL_DEPTH_TEST);

    ResourceManager::instance().setWindow(*window);

    return true;
}


