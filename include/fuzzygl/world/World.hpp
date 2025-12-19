#pragma once
#include <common_includes.hpp>
#include <fuzzygl/world/RenderObject.hpp>
#include <fuzzygl/world/Camera.hpp>

class World
{
private:
    std::vector<std::unique_ptr<RenderObject>> objects;
    Camera camera;
    glm::mat4 perspective;
public:
    World(float ratio);
    void updateAspectRatio(float ratio);
    void draw();
    std::vector<std::unique_ptr<RenderObject>>& getObjects();

private:
    void setupWorld();
};