#pragma once
#include <common_includes.hpp>
#include <fuzzygl/resources/Shader.hpp>


class Model
{
private:
    Shader shader;
    GLuint vertexArrayObject;
public:
    Model();
    Shader& getShader();
    GLuint getVAO();
};



