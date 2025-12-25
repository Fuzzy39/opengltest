#pragma once
#include <common_includes.hpp>

class Camera;

class CameraBehavior
{
public:
    virtual void update( Camera& cam) = 0;
    virtual void onActiveChanged(Camera& cam, bool newActive) {};
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
    virtual void update( Camera& cam);
};

class WackyBehavior : public CameraBehavior
{
public:
    virtual void update(Camera& cam);
};


class ControllableBehavior :public CameraBehavior
{
public:
    virtual void update( Camera& cam);
    void onActiveChanged(Camera& cam, bool newActive) override;
};

