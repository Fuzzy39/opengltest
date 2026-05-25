#include <fuzzygl/resources/Model.hpp>

Vertex::Vertex(glm::vec3 vert, glm::vec2 texVert)
{
    vertex = vert;
    textureVert = texVert;
}


Model::Model(std::vector<Vertex> verts)
{
    // setup the shader
    Shader* sh = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader = std::unique_ptr<Shader>(sh);

    // setup the VAO
    numVertices =  verts.size();

    // calculate center.
    center = glm::vec3(0);
    for(int i = 0; i<numVertices; i++)
    {
        center+= verts[i].vertex;
    }
    center *= (1.0f/numVertices);
    std::cout<<numVertices<<", "<<center.x<<", "<<center.y<<", "<<center.z<<"\n";

    
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject); // binding the VAO means any attribute pointers/buffer objects will be written to it.

    // shove the data in here
    GLuint VertexBufferObject;
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject); //assign VectexBufferObject as an array buffer (of which there can only be one?)

    // get data
    glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vertex), verts.data(), GL_STATIC_DRAW);
    setVertexAttributes();

}

Shader& Model::getShader()
{
    return *shader;
}


GLuint Model::getVAO()
{
    return vertexArrayObject;
}

int Model::getNumVertices()
{
    return numVertices;
}

glm::vec3 Model::getCenter()
{
    return center;
}

void Model::setVertexAttributes()
{
    // explain to opengl the format of the vertex data we'll be giving it
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
        sizeof(Vertex), 
        (void*)(offsetof(Vertex, vertex))
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 
        sizeof(Vertex), 
        (void*)(offsetof(Vertex, textureVert))
    );
    glEnableVertexAttribArray(1);
}

