#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>


class Vec2
{
public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);

};

class Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float x, float y, float z);
};

class Vec4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vec4();
    Vec4(float x, float y, float z, float w);
};



class Vertex
{
public:
    Vec3 vert;
    float angle; // radians
    Vec2 textureVert;

public:
    Vertex(Vec3 vert, float angle, Vec2 textureVert);
    static Vertex fromAngle(float theta, int second);
    static Vertex* makeVerticies(int points, int* count); // returns an array of verticies number+1 in size
    static void setVertexAttributes();
};
