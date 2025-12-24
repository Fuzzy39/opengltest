#include <fuzzygl/world/Camera.hpp>
#include <fuzzygl/resources/ResourceManager.hpp>

Camera::Camera() : Camera::Camera(glm::vec3(0,0,0)) { }

Camera::Camera(glm::vec3 position)
{
    active = false;
    matrix = glm::mat4(1);
    setPosition(position);
}

glm::vec3 Camera::getPosition()
{
    glm::mat4 inv = glm::affineInverse(matrix);	

    return inv * glm::vec4(0,0,0,1);
}

void Camera::setPosition(glm::vec3 position)
{
    matrix[3].x = 0;
    matrix[3].y = 0;
    matrix[3].z = 0;

    glm::mat4 translate = glm::mat4(1);
    for(int i = 0; i<3; i++)
    {
        translate[3][i]= -position[i];
    }
    matrix = matrix * translate;

    update();
}

void Camera::translate(glm::vec3 translateBy)
{
  
    matrix = glm::translate(matrix, translateBy);
    update();
}

void Camera::resetRotation()
{
    glm::vec3 pos = getPosition();
    matrix = glm::mat4(1);
    setPosition(pos);
    update();
}

void Camera::lookAt(glm::vec3 target)
{
    // Okay, basic strategy
    // glm::vec3 basis[] = 
    // { 
    //     glm::normalize(target-getPosition()),
    //     glm::normalize(glm::cross(basis[0], glm::vec3(0,1,0))),
    //     glm::normalize(glm::cross(basis[0], basis[1]))
    // };

    // //glm::mat4 rotate = glm::mat4(1);
    // matrix[0] = glm::vec4(basis[2], target[0]);
    // matrix[1] = glm::vec4(basis[1], target[1]);
    // matrix[2] = glm::vec4(basis[0], target[2]);
    //matrix = rotate
    //std::cout<<getPosition().x<<", "<<getPosition().y<<", "<<getPosition().z<<"\n";
    matrix = glm::lookAt(getPosition(), target, glm::vec3(0,1,0));
    update();
}

void Camera::pitch(float pitchRadians)
{
    matrix = glm::rotate(matrix, pitchRadians, glm::vec3(matrix[0]));   
    update();
}

void Camera::yaw(float yawRadians)
{
    matrix = glm::rotate(matrix, yawRadians, glm::vec3(matrix[1]));
    update();
}

void Camera::roll(float rollRadians)
{
    matrix = glm::rotate(matrix, rollRadians, glm::vec3(matrix[2]));
    update();
}

void Camera::rotateAbout(float rotateRadians, glm::vec3 axis)
{
    matrix = glm::rotate(matrix, rotateRadians, axis);
    update();
}

void Camera::setActive(bool active)
{
    this->active = active;
    update();
}

bool Camera::isActive() { return active;}

void Camera::update()
{
    if(!active) return;
    ResourceManager::instance().setShaderMatricies("viewMat", matrix);
}

std::string Camera::toString()
{

    std::ostringstream buffer;
    buffer << "Camera with pos " <<(getPosition().x)<<", " <<getPosition().y<<", "<<getPosition().z; 
    return buffer.str();
}