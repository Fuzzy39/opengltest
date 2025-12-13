#pragma once
#include <common_includes.hpp>
#include <fuzzygl/resources/Shader.hpp>


// for all intents and purposes, this is a cube.
// Eventually it'll be replaced with a more abstract class.
class Model
{
private:
    struct Vertex
    {
      glm::vec3 vertex;
      glm::vec2 textureVert;  

      Vertex(glm::vec3 vert, glm::vec2 texVert);
    };

private:
    std::unique_ptr<Shader> shader;
    GLuint vertexArrayObject;
    int numVertices;

public:
    Model();
    Shader& getShader();
    GLuint getVAO();
    int getNumVertices();

private:
    void setVertexAttributes();
};



