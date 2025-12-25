#pragma once
#include <common_includes.hpp>
#include <fuzzygl/world/CameraBehaviors.hpp>

class Camera
{
private:
    bool active;
    glm::mat4 matrix;
    CameraBehavior* behavior;
    //float fovRadians;
public:
    Camera();
    Camera(glm::vec3 position);

    // position
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    void translate(glm::vec3 translateBy);

    // rotation
   void resetRotation();
   // Assumes the vertical component is, you know, vertical, y axis.
   void lookAt(glm::vec3 target);
   void pitch( float pitchRadians);
   void yaw(float yawRadians);
   void roll(float rollRadians);
   void rotateAbout(float rotateRadians, glm::vec3 axis);

   // active
   void setActive(bool active);
   bool isActive();

   // behavior
   void setBehavior(CameraBehavior* cb);
   void update(GLFWwindow* window);

   // util
   std::string toString();
   ~Camera();

private:
    void sendMatrix();

};