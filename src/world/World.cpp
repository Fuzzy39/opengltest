#include <fuzzygl/world/World.hpp>
#include <fuzzygl/resources/ResourceManager.hpp>


World::World(float ratio)
{
    // perspective matrix
    updateAspectRatio(ratio);
    cameras.push_back(std::unique_ptr<Camera>(new Camera(glm::vec3(
        0, 
        0,
        5)
    )));

    setActiveCamera(0);

    if (WORLD_TETRAHEDRONS)
    {
        setupTetrahedron();
        return;
    }
    
    setupWorld();
    //std::cout<<"World setup!\n";
}

void World::updateAspectRatio(float ratio)
{
    perspective = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
}

void World::draw()
{
    float period = 1.57f;
    float incrementBy = 1.0f/objects.size();

    // set the perspective matrix appropriately for all shaders.
    ResourceManager::instance().setShaderMatricies("perspectiveMat", perspective);
    
    // draw objects
    float i = 0;
    for(const std::unique_ptr<RenderObject>& object: objects) 
    {
        float addTo = OBJECT_DO_ROTATION ? i * incrementBy : 0;
        float baseSpeed = OBJECT_DO_ROTATION ? (i * .01f) : 1;

        if(WORLD_DO_TIME) object->setTime(glfwGetTime()*baseSpeed/period + addTo);
        //object->setTime((i*.7f)/period + i*incrementBy);
        object->draw();
        i++;
    }

    // update cameras
    activeCamera().update();
}

std::vector<std::unique_ptr<RenderObject>>& World::getObjects()
{
    return objects;
}

std::unique_ptr<Camera>& World::getCamera(int index)
{
    std::unique_ptr<Camera>& toRet = cameras[index];
    activeCamera();
    return toRet;
}

void World::addCamera()
{
    cameras.push_back(std::unique_ptr<Camera>(new Camera()));
}

int World::getCameraCount()
{
    return cameras.size();
}

Camera &World::activeCamera()
{
    Camera* toRet = nullptr;
    for( const std::unique_ptr<Camera>& cam : cameras)
    {
        
        if(cam->isActive())
        {
       
            if(toRet!=nullptr)
            {
                std::cout<<"ERROR::WORLD::CAMERA_ERROR: Multiple active cameras.\n";
                throw std::exception();   
            }
            toRet = &(*cam);
        }

    }

    if(toRet==nullptr)
    {
        std::cout<<"ERROR::WORLD::CAMERA_ERROR: No active cameras.\n";
        throw std::exception();   
    }

    return *toRet;
}


void World::setActiveCamera(int index)
{  
   
    std::cout<<"Setting cam "<<index<<" as active.\n";

    for(const std::unique_ptr<Camera>& cam : cameras)
    {
        cam->setActive(false);
    }
    cameras[index]->setActive(true);
    // mostly just check that we've not exploded anything.
    activeCamera();
}




void World::setupTetrahedron()
{
    // code assumes model starts at origin and stays in the first octant
    glm::vec3 origin = glm::vec3(0,0,0.0f);
    glm::vec3 unitSize = glm::vec3(1.0f);
    float scale = 1.0f;
    //unitSize = scale* unitSize;
    glm::vec3 gridSize = glm::vec3(10,10,10);

    int numObjects = (int)(gridSize.x*gridSize.y*gridSize.z);
    float deltaRotation = (2.0f*M_PI)/numObjects;

    glm::vec3 size = glm::vec3(
        unitSize.x*gridSize.x,
        unitSize.y*gridSize.y,
        unitSize.z*gridSize.z
    );
    glm::vec3 start = -.5f*size+origin+.5f*unitSize;//-glm::vec3(unitSize.x, unitSize.y, 0);
    Model& m = ResourceManager::instance().getModel(ResourceManager::Models::TETRAHEDRON);
    Shader& shader = ResourceManager::instance().getShader(ResourceManager::Shaders::RAINBOW);

    for(int x = 0; x<gridSize.x; x++)   
    {
        for(int y = 0; y<gridSize.y; y++)   
        {
            for(int z = 0; z<gridSize.z; z++)   
            {
                // create the object
                RenderObject* obj = new RenderObject(m, shader);
                objects.push_back(std::unique_ptr<RenderObject>(obj));
                int i = (int)(z+y*gridSize.z+x*gridSize.y*gridSize.z);
                
                // rotate it
                // glm::vec3 axis = glm::vec3(sin(i*deltaRotation),1,0);
                // axis = axis/glm::length(axis);
                //obj->worldPos=glm::translate(obj->worldPos, -.5f*unitSize);
                // glm::vec3 axis =  glm::vec3(0,0,1);
                // obj->worldPos = glm::rotate(obj->worldPos, i*deltaRotation, axis);
                //obj->worldPos=glm::translate(obj->worldPos, .5f*unitSize);

                //scale it
                obj->setScale(glm::vec3(scale)*((z+1)/gridSize.z));

            

                //translate it
                glm::vec3 pos = start + glm::vec3(x*unitSize.x,y*unitSize.y,z*unitSize.z);
                //std::cout<< "x: "<<pos.x<<" y: "<<pos.y<<" z: "<<pos.z<<"\n";
                obj->setTranslation(pos);
            } 
        } 
    } 
}

void World::setupWorld()
{
    // code assumes model starts at origin and stays in the first octant
    glm::vec3 origin = glm::vec3(0, 0, 0.0f);
    glm::vec3 unitSize = glm::vec3(1.0f);
    float scale = 1.0f;
    //unitSize = scale* unitSize;
    glm::vec3 gridSize = glm::vec3(30, 1, 30);

    int numObjects = (int)(gridSize.x * gridSize.z);
    float deltaRotation = (2.0f * M_PI) / numObjects;

    glm::vec3 size = glm::vec3(
        unitSize.x * gridSize.x,
        unitSize.y * gridSize.y,
        unitSize.z * gridSize.z
    );
    glm::vec3 start = -.5f * size + origin + .5f * unitSize;//-glm::vec3(unitSize.x, unitSize.y, 0);
    Model& m = ResourceManager::instance().getModel(ResourceManager::Models::CUBE);
    Shader& shader = ResourceManager::instance().getShader(ResourceManager::Shaders::OCEAN);


    for (int x = 0; x < gridSize.x; x++)
    {
        
        for (int z = 0; z < gridSize.z; z++)
        {
            // create the object
            RenderObject* obj = new RenderObject(m, shader);
            objects.push_back(std::unique_ptr<RenderObject>(obj));
            int i = (int)(z + x * gridSize.y * gridSize.z);

            //scale it
            obj->rotateBy(M_PI / 2.0f, glm::vec3(1, 0, 0));
            glm::vec3 scaleVec = glm::vec3(scale);
            scaleVec.y *= ((z + 1) / gridSize.z) * ((x + 1) / gridSize.x);
            //obj->setScale( scaleVec);

            //translate it
            glm::vec3 pos = start + glm::vec3(x * unitSize.x, 0, z * unitSize.z);
            //std::cout<< "x: "<<pos.x<<" y: "<<pos.y<<" z: "<<pos.z<<"\n";
            obj->setTranslation(pos);

            float randoffset = .03f * (rand() % 100);
            obj->setTimeOffset( .4*(x + z) +randoffset);
        }
        
    }
}