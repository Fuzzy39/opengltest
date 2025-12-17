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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, tex2);

    // initialize our (only) model
    models.push_back(std::unique_ptr<Model>(new Model()));
}

Model& ResourceManager::getModel(int index)
{
    return *models[index];
}

void ResourceManager::setShaderMatricies(const std::string name, glm::mat4 value)
{
    for(const std::unique_ptr<Model>& model : models)
    {
        model->getShader().setMat4(name, value);
    }
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
