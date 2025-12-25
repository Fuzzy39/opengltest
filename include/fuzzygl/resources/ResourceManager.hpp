#pragma once
#include <common_includes.hpp>
#include <fuzzygl/resources/Model.hpp>

/// @brief Resource Manager is a singleton class that manages application wide resources,
// such as 3d models and textures.
class ResourceManager
{
private:
    std::vector<std::unique_ptr<Model>> models;
    GLFWwindow * window;
public:
    glm::vec2 prevMousePos;
    glm::vec2 currMousePos;

    // in screen coords (0,0)->(1,1)
    glm::vec2 relMousePos;
    glm::vec2 deltaMousePos;


private:
    ResourceManager();
    GLuint makeTexture(const char* path);
public:
    static ResourceManager& instance();
    Model& getModel(int index);
    void setShaderMatricies(const std::string name, glm::mat4 value );
    void setWindow(GLFWwindow * window);
    GLFWwindow* getWindow();
};