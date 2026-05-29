#include <fuzzygl/resources/ResourceManager.hpp>

// stb image
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

static ResourceManager* _instance = nullptr;

ResourceManager& ResourceManager::instance()
{
    if(_instance != nullptr)
    {
        return *_instance;
    }
    // create the resource manager.
    // this feels like it'd cause a leak...
    _instance = new ResourceManager();
    // oh well, I guess?
    return *_instance;
}

ResourceManager::ResourceManager()
{
    // do things...
    GLuint tex0 = makeTexture("resources/FROG.png");
    GLuint tex1 = makeTexture("resources/Frog2.jpg");
    GLuint tex2 = makeTexture("resources/greg.jpg");
    GLuint tex3 = makeTexture("resources/stopper.png");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, tex3);

    // initialize our (only) model
    models.push_back(std::unique_ptr<Model>(new Model(Tetrahedron())));
    models.push_back(std::unique_ptr<Model>(new Model(Prism(1))));

   
    shaders.push_back(std::unique_ptr<Shader>(new Shader("shaders/rainbow/vertex.glsl", "shaders/rainbow/fragment.glsl")));
    shaders.push_back(std::unique_ptr<Shader>(new Shader("shaders/ocean/vertex.glsl", "shaders/ocean/fragment.glsl")));

    
    prevMousePos = glm::vec2(-1);
    currMousePos = glm::vec2(-1);
    relMousePos = glm::vec2(0);
    deltaMousePos = glm::vec2(0);
}

Model& ResourceManager::getModel(int index)
{
    return *models[index];
}
Shader& ResourceManager::getShader(int index)
{
    return *shaders[index];
}

void ResourceManager::setShaderMatricies(const std::string name, glm::mat4 value)
{
    for (const std::unique_ptr<Shader>& i : shaders)
    {
        i->setMat4(name, value);
    }
}

void ResourceManager::setWindow(GLFWwindow *window)
{
    this->window = window;
}

GLFWwindow* ResourceManager::getWindow()
{
    return window;
}

GLuint ResourceManager::makeTexture(const char *path)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 4);
    if (data == NULL)
    {
        std::cout << "ERROR::RESOURCE: Couldn't load the texture at '"<<path<<"' Reason: " << stbi_failure_reason();
        throw std::exception();
    }


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

   
    return texture;
}
