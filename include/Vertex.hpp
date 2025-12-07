#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>


class Vertex
{
public:
    glm::vec3 vert;
    float angle; // radians
    glm::vec2 textureVert;

public:
    Vertex(glm::vec3 vert, float angle, glm::vec2 textureVert);
    static Vertex fromAngle(float theta, int second);
    static Vertex* makeVerticies(int points, int* count); // returns an array of verticies number+1 in size
    static void setVertexAttributes();
};
