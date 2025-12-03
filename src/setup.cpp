#include "glTest.hpp"
#include "Vertex.hpp"   
// stb image
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


int numPoints = 8;


bool setup( GLuint* VertexArrayObject, GLFWwindow** window)
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


    // do the complicated openGL stuff now.
    *VertexArrayObject = SetupVertexArrayObj();


    // out of a lack of knowing where to put it, texture related stuff.

    int width, height, nrChannels;
    unsigned char* data = stbi_load("resources/FROG.png", &width, &height, &nrChannels, 0);
    if (data == NULL)
    {
        std::cout << "ERROR::RESOURCE: Couldn't open the frog image. Reason: " << stbi_failure_reason();
        return false;
    }

    std::cout<<width<<", "<<height<<", nrChannels"<<nrChannels<<"\n";

    unsigned int texture;
    glGenTextures(1, &texture); 
    
    // wraping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // generate a texture from an image.            

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glActiveTexture(GL_TEXTURE0);

    return true;
}


unsigned int SetupVertexArrayObj()
{
    // A vertex array object stores all of the vertex attribute pointers...
    // As well as vertex buffer objects.
    // Basically, it keeps track some renderable object's data and the format it should be put into the vertex shader.


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // binding the VAO means any attribute pointers/buffer objects will be written to it.

    // shove the data in here
    unsigned int VertexBufferObject;
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject); //assign VectexBufferObject as an array buffer (of which there can only be one?)

    // get data
    int numVerticies = 0;
    Vertex* data = Vertex::makeVerticies(numPoints, &numVerticies);
    // std::cout<<(void*)(&(data[0].x))-(void*)(&data[0])<<"\n";
    std::cout<<(offsetof(Vertex, angle))<<"\n";
    glBufferData(GL_ARRAY_BUFFER, numVerticies*sizeof(Vertex), data, GL_STATIC_DRAW);
    free(data);


    Vertex::setVertexAttributes();

    return VAO;


}
