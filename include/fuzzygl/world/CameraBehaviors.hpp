#pragma once
#include <common_includes.hpp>

class Camera;

class CameraBehavior
{
public:
    virtual void update(GLFWwindow* window, Camera& cam) = 0;
    virtual ~CameraBehavior(){}
};


class OrbitBehavior : public CameraBehavior
{
private:
    glm::vec3 origin;
    float radius;
    float y;
    float periodSeconds;

public:
    OrbitBehavior(glm::vec3 orbitOrigin, float r, float yValue, float orbitSeconds);
    virtual void update(GLFWwindow* window, Camera& cam);
};

class WackyBehavior : public CameraBehavior
{
public:
    virtual void update(GLFWwindow* window, Camera& cam);
};


class ControllableBehavior :public CameraBehavior
{
public:
    virtual void update(GLFWwindow* window, Camera& cam);
};

