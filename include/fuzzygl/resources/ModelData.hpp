#pragma once
#include <common_includes.hpp>

struct Vertex
{
    glm::vec3 vertex;
    glm::vec2 textureVert;  

    Vertex(glm::vec3 vert, glm::vec2 texVert);
};

std::vector<Vertex> Tetrahedron();    
std::vector<Vertex> Prism(float height);

