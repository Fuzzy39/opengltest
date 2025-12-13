#pragma once
#include <common_includes.hpp>
#include <fuzzygl/resources/Model.hpp>

class RenderObject
{
private:
    Model& model;
public:
    glm::mat4 worldPos;

public:
    RenderObject(Model& model);
    void draw();

};


class World
{
private:
    std::vector<std::unique_ptr<RenderObject>> objects;

public:
    World();
    void draw();
    std::vector<std::unique_ptr<RenderObject>>& getObjects();
};