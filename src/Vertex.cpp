#include "glTest.hpp"
#include "Vertex.hpp"


Vertex::Vertex(glm::vec3 vert, float angle, glm::vec2 textureVert)
{
    this->vert = vert;
    this->angle = angle;
    this->textureVert = textureVert;
}

Vertex Vertex::fromAngle(float theta, int second)
{
	glm::vec2 texture;
	switch(second)
	{
	case 0:
		texture = glm::vec2(0, 0);
		break;
	case 1:
		texture = glm::vec2(0, 1);
		break;
	case 2:
		texture = glm::vec2(1, 1);
		break;
		
	}
	

    return Vertex(
        glm::vec3(cos(theta), sin(theta), 0), 
        theta,
        texture
    );
}


Vertex* Vertex::makeVerticies(int points, int* count)
{
    if(points<=2) return nullptr;

    *count = points*3;
    // hopefully this works like I think it does.
    // C++ approves of this, surely.
    Vertex* toReturn = (Vertex*)malloc(sizeof(Vertex)*(*count));

	bool even = 1;
    for(int i = 0; i<points; i++)
    {
        toReturn[i*3] = Vertex(glm::vec3(0,0,0),-1, glm::vec2(1, 0));
        toReturn[i*3+1] = Vertex::fromAngle((2.0f*M_PI*i)/points, even);
        toReturn[i*3+2] = Vertex::fromAngle((2.0f*M_PI*(i+1))/points, even+1);
		even = !even;
    }
    return toReturn;

}

void Vertex::setVertexAttributes()
{
	// explain to opengl the format of the vertex data we'll be giving it
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, vert)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, angle)));
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, textureVert)));
    glEnableVertexAttribArray(2);
}
