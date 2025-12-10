#pragma once
#include <common_includes.hpp>
#include <fuzzygl/resources/Shader.hpp>




// This class represents a disk with textures strewn across it.
// by defualt it's a unit disk with radius 1 in the xy plane.
class Disk
{
private:
    class Vertex
    {
    public:
        glm::vec3 vert;
        float angle; // radians
        glm::vec2 textureVert;

    public:
        Vertex(glm::vec3 vert, float angle, glm::vec2 textureVert);
        Vertex(float theta, float imageProgress);
    
    private:
        glm::vec2 calcTextureVert(float imageProgress);
      
    };


private:
    int sides;
    int textures;
    Shader* shader;
    GLuint vertexArrayObject;
  

    // textures?

public:
    // sides - the number of sides of the disk. minumum is 3.
    // textures - the number of repeated textures per side of the disk. minimum is 1, max is sides.
    Disk(int sides, int textures);

    ~Disk();

    // time - a value between 0 and 1 for a cycle of the disk's insane motion
    void setTime(float time);

    // draw the thing!
    void draw();

private:
    // this is all setup
    Vertex* makeVertices(int points, int textures, int* count); // returns an array of verticies number+1 in size
    void setVertexAttributes();
    GLuint setupVAO();
    




};
