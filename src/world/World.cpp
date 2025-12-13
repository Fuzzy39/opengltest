#include <fuzzygl/world/World.hpp>
#include <fuzzygl/Resources/ResourceManager.hpp>

World::World()
{
    // code assumes model starts at origin and stays in the first octant
    glm::vec3 origin = glm::vec3(0,0,1);
    glm::vec3 unitSize = glm::vec3(1,1,1);
    glm::vec3 gridSize = glm::vec3(2,2,1);

    int numObjects = gridSize.x*gridSize.y*gridSize.z;
    float deltaRotation = (2.0f*M_PI)/numObjects;

    glm::vec3 size = glm::vec3(
        unitSize.x*gridSize.x,
        unitSize.y*gridSize.y,
        unitSize.z*gridSize.z
    );
    glm::vec3 start = .5f*size+unitSize+glm::vec3(-unitSize.x, 0, 0);
    Model& m = ResourceManager::instance().getModel(0);
    
    for(int x = 0; x<gridSize.x; x++)   
    {
        for(int y = 0; y<gridSize.y; y++)   
        {
            for(int z = 0; z<gridSize.z; z++)   
            {
                // create the object
                RenderObject* obj = new RenderObject(m);
                objects.push_back(std::unique_ptr<RenderObject>(obj));
                
                // rotate it
                glm::vec3 axis = glm::vec3(sin(deltaRotation),1,0);
                axis = axis/glm::length(axis);
                obj->worldPos = glm::rotate(obj->worldPos, deltaRotation, axis);

                //translate it
                glm::translate(obj->worldPos, start + glm::vec3(x*unitSize.x,y*unitSize.y,z*unitSize.z));
            } 
        } 
    } 

}

void World::draw()
{
    for(const std::unique_ptr<RenderObject>& object: objects) 
    {
        object->draw();
    }
}

std::vector<std::unique_ptr<RenderObject>>& World::getObjects()
{
    return objects;
}