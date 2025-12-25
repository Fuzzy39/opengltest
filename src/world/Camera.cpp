#include <fuzzygl/world/Camera.hpp>
#include <fuzzygl/resources/ResourceManager.hpp>

Camera::Camera() : Camera::Camera(glm::vec3(0,0,0)) { }

Camera::Camera(glm::vec3 position)
{
    active = false;
    matrix = glm::mat4(1);
    setPosition(position);
    behavior = nullptr;
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

    sendMatrix();
}

void Camera::translate(glm::vec3 translateBy)
{
  
    matrix = glm::translate(matrix, translateBy);
    sendMatrix();
}

void Camera::resetRotation()
{
    glm::vec3 pos = getPosition();
    matrix = glm::mat4(1);
    setPosition(pos);
    sendMatrix();
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
    sendMatrix();
}

void Camera::pitch(float pitchRadians)
{
    matrix = glm::rotate(matrix, pitchRadians, glm::vec3(matrix[0]));   
    sendMatrix();
}

void Camera::yaw(float yawRadians)
{
    matrix = glm::rotate(matrix, yawRadians, glm::vec3(matrix[1]));
    sendMatrix();
}

void Camera::roll(float rollRadians)
{
    matrix = glm::rotate(matrix, rollRadians, glm::vec3(matrix[2]));
    sendMatrix();
}

void Camera::rotateAbout(float rotateRadians, glm::vec3 axis)
{
    matrix = glm::rotate(matrix, rotateRadians, axis);
    sendMatrix();
}



void Camera::setActive(bool active)
{
    this->active = active;
    sendMatrix();
}

bool Camera::isActive() { return active;}



void Camera::setBehavior(CameraBehavior *cb)
{
    if(behavior!=nullptr)
    {
        delete behavior;
    }
    
    behavior = cb;
}

void Camera::sendMatrix()
{
    if(!active) return;
    ResourceManager::instance().setShaderMatricies("viewMat", matrix);
}

void Camera::update(GLFWwindow* window)
{
    if(behavior!=nullptr)
    {
        behavior->update(window, *this);
    }
}


std::string Camera::toString()
{

    std::ostringstream buffer;
    buffer << "Camera with pos " <<(getPosition().x)<<", " <<getPosition().y<<", "<<getPosition().z; 
    return buffer.str();
}

Camera::~Camera()
{
    if(behavior!=nullptr)
    {
        delete behavior;
    }
}