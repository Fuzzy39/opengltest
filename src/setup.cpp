#include "glTest.hpp"


float vertices[] = {
    -0.50f, -1.0f, 0.0f,
    -1.0f, -0.0f, 0.0f,
    -0.50f,  1.0f, 0.0f,

    0.50f,  1.0f, 0.0f,
    1.0f, -0.0f, 0.0f,
    0.50f, -1.0f, 0.0f,
    -0.50f, -1.0f, 0.0f,
    -1.0f, -0.0f, 0.0f,
};

bool setup( GLuint* shaderProgram, GLuint* VertexArrayObject, GLFWwindow** window)
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
    if (!compileShaders(shaderProgram)) return false;
    *VertexArrayObject = SetupVertexArrayObj();

    return true;
}


// this seems terrible
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 color;"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   color = vec4((aPos.x+1.0)/2.0, (aPos.y+1.0)/2.0, (aPos.y+1.0)/2.0, 1.0);"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 color;"
    "void main()"
    "{"
    "FragColor = color;"
    "}";



bool compileShaders( GLuint* shaderProgram)
{
    // SETUP shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // put our source in the shader and compile it.
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //check if comilation succeeded.
    int  success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }


    // fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // put our source in the shader and compile it.
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check if it worked.
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        return false;
    }

    // make a program
 
    *shaderProgram = glCreateProgram();

    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);

    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        char infoLog[512];
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }


    // wrap up.
    glUseProgram(*shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    // explain to opengl the format of the vertex data we'll be giving it
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;


}
