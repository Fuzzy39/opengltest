#include <fuzzygl/resources/ModelData.hpp>

// should this data be stored in code as opposed to a file?
// No... but I'm lazy. If we get real models this will have to change, of course.
std::vector<Vertex> Tetrahedron()
{
    Vertex verts[] = {
        // bottom
        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(1,0,0), glm::vec2(1,0)),
        Vertex(glm::vec3(.5,sqrt(3)/2,0), glm::vec2(.5,1)),

        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(1,0,0), glm::vec2(1,0)),
        Vertex(glm::vec3(.5,.5/sqrt(3),-.75f), glm::vec2(.5,1)),

        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(.5,sqrt(3)/2,0), glm::vec2(1,0)),
        Vertex(glm::vec3(.5,.5/sqrt(3),-.75f), glm::vec2(.5,1)),

        Vertex(glm::vec3(1,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(.5,sqrt(3)/2,0), glm::vec2(1,0)),
        Vertex(glm::vec3(.5,.5/sqrt(3),-.75f), glm::vec2(.5,1)),
    };
    size_t numVertices = sizeof(verts)/sizeof(Vertex);

    return std::vector<Vertex> (verts, verts+numVertices);

}


std::vector<Vertex> Prism(float h)
{
    // worrying about it later
   
    Vertex verts[] = {
        // bottom
        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(1,0,0), glm::vec2(1,0)),
        Vertex(glm::vec3(1,1,0), glm::vec2(1,1)),

        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(0,1,0), glm::vec2(0,1)),
        Vertex(glm::vec3(1,1,0), glm::vec2(1,1)),

        // top
        Vertex(glm::vec3(0,0,h), glm::vec2(0,0)),
        Vertex(glm::vec3(1,0,h), glm::vec2(1,0)),
        Vertex(glm::vec3(1,1,h), glm::vec2(1,1)),

        Vertex(glm::vec3(0,0,h), glm::vec2(0,0)),
        Vertex(glm::vec3(0,1,h), glm::vec2(0,1)),
        Vertex(glm::vec3(1,1,h), glm::vec2(1,1)),

        // front (x = 0)
        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(0,1,0), glm::vec2(1,0)),
        Vertex(glm::vec3(0,1,h), glm::vec2(1,1)),

        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(0,0,h), glm::vec2(0,1)),
        Vertex(glm::vec3(0,1,h), glm::vec2(1,1)),

        // back ( x = 1)
        Vertex(glm::vec3(1,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(1,1,0), glm::vec2(1,0)),
        Vertex(glm::vec3(1,1,h), glm::vec2(1,1)),

        Vertex(glm::vec3(1,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(1,0,h), glm::vec2(0,1)),
        Vertex(glm::vec3(1,1,h), glm::vec2(1,1)),

        // left (y = 0)
        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(1,0,0), glm::vec2(1,0)),
        Vertex(glm::vec3(1,0,h), glm::vec2(1,1)),

        Vertex(glm::vec3(0,0,0), glm::vec2(0,0)),
        Vertex(glm::vec3(0,0,h), glm::vec2(0,1)),
        Vertex(glm::vec3(1,0,h), glm::vec2(1,1)),

        // right (y = 1)
        Vertex(glm::vec3(0,1,0), glm::vec2(0,0)),
        Vertex(glm::vec3(1,1,0), glm::vec2(1,0)),
        Vertex(glm::vec3(1,1,h), glm::vec2(1,1)),

        Vertex(glm::vec3(0,1,0), glm::vec2(0,0)),
        Vertex(glm::vec3(0,1,h), glm::vec2(0,1)),
        Vertex(glm::vec3(1,1,h), glm::vec2(1,1)),        

    };
    size_t numVertices = sizeof(verts)/sizeof(Vertex);

    return std::vector<Vertex> (verts, verts+numVertices);
}
