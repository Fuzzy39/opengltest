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
    glm::vec3 pos = getPosition();
    matrix = glm::translate(matrix, pos);
    matrix = glm::rotate(matrix, pitchRadians, glm::vec3(matrix[0]));   
    matrix = glm::translate(matrix, -pos);
    sendMatrix();
}




void Camera::yaw(float yawRadians)
{
    glm::vec3 pos = getPosition();
    matrix = glm::translate(matrix, pos);
    matrix = glm::rotate(matrix, yawRadians, glm::vec3(matrix[1]));
    matrix = glm::translate(matrix, -pos);
    sendMatrix();
}

void Camera::roll(float rollRadians)
{
    glm::vec3 pos = getPosition();
    matrix = glm::translate(matrix, pos);
    matrix = glm::rotate(matrix, rollRadians, glm::vec3(matrix[2]));
    matrix = glm::translate(matrix, -pos);
    sendMatrix();
}

void Camera::rotateAbout(float rotateRadians, glm::vec3 axis)
{
    glm::vec3 pos = getPosition();
    matrix = glm::translate(matrix, pos);
    matrix = glm::rotate(matrix, rotateRadians, glm::normalize(axis));
    matrix = glm::translate(matrix, -pos);
    sendMatrix();
}




void Camera::translateRelative(glm::vec3 translateBy)
{
    glm::mat3 basis = glm::mat3(matrix);
    
    translate(
        -glm::row(basis, 0)*translateBy.x +
        -glm::row(basis, 1)*translateBy.y +
        glm::row(basis, 2)*translateBy.z
    );
}

float Camera::getPitchXZ()
{
    glm::mat3 basis = glm::mat3(matrix);
    glm::vec3 camDir = glm::row(basis, 2);
    float dot = glm::dot(camDir, glm::normalize(glm::vec3(camDir.x, camDir.y,0)));
    return acosf(dot);
}

void Camera::setPitchXZ(float radians)
{
    glm::mat3 basis = glm::mat3(matrix);
    glm::vec3 camDir = glm::row(basis, 2);
    glm::vec3 XZDir = glm::normalize(glm::vec3(camDir.x, camDir.y,0));
    glm::row(matrix, 2, glm::vec4(XZDir, matrix[3][2]));
    pitch(radians);
}




void Camera::setActive(bool active)
{
    if(this->active == active) return;

    this->active = active;
    if(behavior!=nullptr) behavior->onActiveChanged(*this, active);
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

void Camera::update()
{
    if(behavior!=nullptr)
    {
        behavior->update(*this);
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