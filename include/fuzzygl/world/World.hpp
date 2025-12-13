#pragma once
#include <common_includes.hpp>
#include <fuzzygl/resources/Model.hpp>

class RenderObject
{
private:
    Model& model;
private:
    glm::vec3 translation;
    // where (1,0,0) is not rotated. represents the point where (1,0,0) would end up after being rotated.
    glm::vec3 rotation;
    glm::vec3 scale;

public:
    RenderObject(Model& model);

    glm::vec3 getTranslation();
    void setTranslation(glm::vec3 toSet);
    glm::vec3 translateBy(glm::vec3 delta);


    // axis should be a unit vector, but this function will correct it.
    void resetRotation();
    glm::mat4 rotateBy(float radians, glm::vec3 axis);

    glm::vec3 getScale();
    void setScale(glm::vec3 toSet);


    void draw();
    // period between 0 and 1.
    void setTime(float time);

private:
    glm::mat4 getModelMat();


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