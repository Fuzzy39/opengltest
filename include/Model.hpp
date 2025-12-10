#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glTest.hpp>


class Model
{
private:
    Shader shader;

public:

};



class RenderObject
{
private:
    Model* model;
public:
    glm::mat4 worldPosition;
    
};