#include <fuzzygl/Disk.hpp>


Disk::Vertex::Vertex(glm::vec3 vert, float angle, glm::vec2 textureVert)
{
    this->vert = vert;
    this->angle = angle;
    this->textureVert = textureVert;
}

Disk::Vertex::Vertex(float theta, float imageProgress) : Disk::Vertex::Vertex( glm::vec3(cos(theta), sin(theta), 0), theta, calcTextureVert(imageProgress))
{
	
}


glm::vec2 Disk::Vertex::calcTextureVert(float imageProgress)
{
    if(imageProgress<.5)
    {
        return glm::vec2(0,2*imageProgress);
    }

    return glm::vec2(2*(imageProgress-.5), 1); 
}



Disk::Disk(int sides, int textures)
{
    this->sides = sides;
    this->textures = textures;

    // initialize shaders
    shader = new Shader("shaders/disk/vertex.glsl", "shaders/disk/fragment.glsl");

    vertexArrayObject = setupVAO();
    // do more things... probably.

    // I guess this works for now.
    shader->setInt("tex", 0); 
    shader->setInt("tex2", 1);

    // in case nobody else does.
    setTime(0);
}

Disk::~Disk()
{
    delete shader;
}



void Disk::setTime(float time)
{
    // sets up shader uniforms to properly render these things

    shader->setFloat("time", time);


    // setup our transform matrix
    glm::mat4 trans = glm::mat4(1.0f);
    glm::vec3 axis = glm::vec3(sin(time*2*M_PI),1,0);
    axis = axis/glm::length(axis);
    // no we have to do interesting things with the matrix.
    trans = glm::rotate(trans, glm::radians(time*360), axis);
    

    // this ought to be a method of shader...
    shader->use();
    GLuint transformLoc = glGetUniformLocation(shader->getHandle(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}


void Disk::draw()
{
    shader->use();
    // you have to use a uniform after useing the shader program;
    // setting the unifrom requires it.
    
    // Do things (TM!)
    glBindVertexArray(vertexArrayObject);
    
    glDrawArrays(GL_TRIANGLES, 0, sides*3);
}

// setup functions

Disk::Vertex* Disk::makeVertices(int points, int* count)
{
    if(points<=2) return nullptr;

    *count = points*3;
    // hopefully this works like I think it does.
    // C++ approves of this, surely.
    Vertex* toReturn = (Vertex*)malloc(sizeof(Vertex)*(*count));

    int texSize = points/textures;

    for(int i = 0; i<points; i++)
    {
        toReturn[i*3] = Vertex(glm::vec3(0,0,0),-1, glm::vec2(1, 0));

        float progressPer = 1.0f/texSize;
        toReturn[i*3+1] = Vertex((2.0f*M_PI*i)/points, progressPer*(i%texSize));
        toReturn[i*3+2] = Vertex((2.0f*M_PI*(i+1))/points, progressPer*(i%texSize+1));
		
    }
    return toReturn;

}


GLuint Disk::setupVAO()
{
     // A vertex array object stores all of the vertex attribute pointers...
    // As well as vertex buffer objects.
    // Basically, it keeps track some renderable object's data and the format it should be put into the vertex shader.


    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // binding the VAO means any attribute pointers/buffer objects will be written to it.

    // shove the data in here
    GLuint VertexBufferObject;
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject); //assign VectexBufferObject as an array buffer (of which there can only be one?)

    // get data
    int numVerticies = 0;
    Vertex* data = makeVertices(sides, &numVerticies);
   
    glBufferData(GL_ARRAY_BUFFER, numVerticies*sizeof(Vertex), data, GL_STATIC_DRAW);
    free(data);


    setVertexAttributes();

    return VAO;
}

void Disk::setVertexAttributes()
{
	// explain to opengl the format of the vertex data we'll be giving it
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, vert)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, angle)));
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, textureVert)));
    glEnableVertexAttribArray(2);
}

