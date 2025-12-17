#include <fuzzygl/world/World.hpp>
#include <fuzzygl/resources/ResourceManager.hpp>

World::World(float ratio)
{
    // perspective matrix
    updateAspectRatio(ratio);
    
    // make objects and have a grand time or whatever
    setupWorld();

}

void World::updateAspectRatio(float ratio)
{
    perspective = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
}

void World::draw()
{
    float period = 10.0f;
    float incrementBy = 1.0f/objects.size();
    float i = 0;

    // set the perspective matrix appropriately for all models.
    ResourceManager::instance().setShaderMatricies("perspectiveMat", perspective);
    
    // draw objects
    for(const std::unique_ptr<RenderObject>& object: objects) 
    {
        object->setTime(glfwGetTime()*(i*.7f)/period + i*incrementBy);
        
        object->draw();
        i++;
    }
}

std::vector<std::unique_ptr<RenderObject>>& World::getObjects()
{
    return objects;
}



void World::setupWorld()
{
    // code assumes model starts at origin and stays in the first octant
    glm::vec3 origin = glm::vec3(0,0,-3.0f);
    glm::vec3 unitSize = glm::vec3(.7f);
    float scale = .5f;
    //unitSize = scale* unitSize;
    glm::vec3 gridSize = glm::vec3(3,3,3);

    int numObjects = gridSize.x*gridSize.y*gridSize.z;
    float deltaRotation = (2.0f*M_PI)/numObjects;

    glm::vec3 size = glm::vec3(
        unitSize.x*gridSize.x,
        unitSize.y*gridSize.y,
        unitSize.z*gridSize.z
    );
    glm::vec3 start = -.5f*size+origin+.5f*unitSize;//-glm::vec3(unitSize.x, unitSize.y, 0);
    Model& m = ResourceManager::instance().getModel(0);
    
    for(int x = 0; x<gridSize.x; x++)   
    {
        for(int y = 0; y<gridSize.y; y++)   
        {
            for(int z = gridSize.z-1; z>=0; z--)   
            {
                // create the object
                RenderObject* obj = new RenderObject(m);
                objects.push_back(std::unique_ptr<RenderObject>(obj));
                int i = z+y*gridSize.z+x*gridSize.y*gridSize.z;
                
                // rotate it
                // glm::vec3 axis = glm::vec3(sin(i*deltaRotation),1,0);
                // axis = axis/glm::length(axis);
                //obj->worldPos=glm::translate(obj->worldPos, -.5f*unitSize);
                // glm::vec3 axis =  glm::vec3(0,0,1);
                // obj->worldPos = glm::rotate(obj->worldPos, i*deltaRotation, axis);
                //obj->worldPos=glm::translate(obj->worldPos, .5f*unitSize);

                //scale it
                obj->setScale(glm::vec3(scale));

            

                //translate it
                glm::vec3 pos = start + glm::vec3(x*unitSize.x,y*unitSize.y,z*unitSize.z);
                std::cout<< "x: "<<pos.x<<" y: "<<pos.y<<" z: "<<pos.z<<"\n";
                obj->setTranslation(pos);
            } 
        } 
    } 
}