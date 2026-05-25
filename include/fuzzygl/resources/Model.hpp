#pragma once
#include <common_includes.hpp>
#include <fuzzygl/resources/Shader.hpp>
#include <fuzzygl/resources/ModelData.hpp>

// for all intents and purposes, this is a cube.
// Eventually it'll be replaced with a more abstract class.
class Model
{
private:
    std::unique_ptr<Shader> shader;
    GLuint vertexArrayObject;
    int numVertices;
    glm::vec3 center;

public:
    Model(std::vector<Vertex> vertices);
    Shader& getShader();
    GLuint getVAO();
    int getNumVertices();

    /// @brief Get the center of the model.
    /// @return The average of all vertices.
    glm::vec3 getCenter();

private:
    void setVertexAttributes();
};


