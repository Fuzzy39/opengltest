#include <fuzzygl/resources/Model.hpp>

Model::Vertex::Vertex(glm::vec3 vert, glm::vec2 texVert)
{
    vertex = vert;
    textureVert = texVert;
}


Model::Model()
{
    // setup the shader
    Shader* sh = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader = std::unique_ptr<Shader>(sh);

    // setup the VAO
    
    Vertex verts[] = {
        // bottom
        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(1,0,0), glm::vec2(1,0)),
        Vertex(glm::vec3(.5,sqrt(3),0), glm::vec2(1,1)),

        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(1,0,0), glm::vec2(1,0)),
        Vertex(glm::vec3(.5,sqrt(3)/2.0f,1.5f), glm::vec2(1,1)),

        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(.5,sqrt(3),0), glm::vec2(1,0)),
        Vertex(glm::vec3(.5,sqrt(3)/2.0f,1.5f), glm::vec2(1,1)),

        Vertex(glm::vec3(1,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(.5,sqrt(3),0), glm::vec2(1,0)),
        Vertex(glm::vec3(.5,sqrt(3)/2.0f,1.5f), glm::vec2(1,1)),
    };

    
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject); // binding the VAO means any attribute pointers/buffer objects will be written to it.

    // shove the data in here
    GLuint VertexBufferObject;
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject); //assign VectexBufferObject as an array buffer (of which there can only be one?)

    // get data
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
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