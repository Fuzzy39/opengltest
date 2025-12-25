#pragma once
#include <common_includes.hpp>
#include <fuzzygl/world/RenderObject.hpp>
#include <fuzzygl/world/Camera.hpp>

class World
{
private:
    std::vector<std::unique_ptr<RenderObject>> objects;
    std::vector<std::unique_ptr<Camera>> cameras;
    glm::mat4 perspective;
public:
    World(float ratio);
    void updateAspectRatio(float ratio);
    void draw(GLFWwindow* window);
    std::vector<std::unique_ptr<RenderObject>>& getObjects();

    std::unique_ptr<Camera>& getCamera(int index);
    void addCamera();
    int getCameraCount();

    Camera& activeCamera();
    void setActiveCamera(int index);
  



private:
    void setupWorld();
};