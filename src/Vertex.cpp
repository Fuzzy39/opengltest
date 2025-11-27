#include "glTest.hpp"

Vertex::Vertex(float x, float y, float z, float angle)
{
    this->x = x;
    this->y = y;
    this-> z = z;
    this->angle = angle;
}

Vertex Vertex::fromAngle(float theta)
{
    return Vertex(cos(theta), sin(theta), 0, theta);
}


Vertex* Vertex::makeVerticies(int points, int* count)
{
    if(points<=2) return nullptr;

    *count = points*3;
    // hopefully this works like I think it does.
    // C++ approves of this, surely.
    Vertex* toReturn = (Vertex*)malloc(sizeof(Vertex)*(*count));

    for(int i = 0; i<points; i++)
    {
        toReturn[i*3] = Vertex(0,0,0,-1);
        toReturn[i*3+1] = Vertex::fromAngle((2.0f*M_PI*i)/points);
        toReturn[i*3+2] = Vertex::fromAngle((2.0f*M_PI*(i+1))/points);
    }
    return toReturn;

}
