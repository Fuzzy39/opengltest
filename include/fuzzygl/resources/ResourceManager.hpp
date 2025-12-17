#pragma once
#include <common_includes.hpp>
#include <fuzzygl/resources/Model.hpp>

/// @brief Resource Manager is a singleton class that manages application wide resources,
// such as 3d models and textures.
class ResourceManager
{
private:
    std::vector<std::unique_ptr<Model>> models;
  

private:
    ResourceManager();
    GLuint makeTexture(const char* path);
public:
    static ResourceManager& instance();
    Model& getModel(int index);
};