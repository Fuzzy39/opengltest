#include <fuzzygl/world/Camera.hpp>
#include <fuzzygl/resources/ResourceManager.hpp>

// gets 3 axes of control. w and s, a and d, and control and space, control the z, x, and y axes, respectively.
// it's ugly. I know.
static glm::vec3 getControlVector()
{
    GLFWwindow* window = ResourceManager::instance().getWindow();

    glm::vec3 move = glm::vec3(0);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        move= move + glm::vec3(0,0,1);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        move= move + glm::vec3(0,0,-1);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        move= move + glm::vec3(-1,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        move= move + glm::vec3(1,0,0);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)== GLFW_PRESS)
    {
        move= move + glm::vec3(0,1,0);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        move= move + glm::vec3(0,-1,0);
    }

    return move;
}

 
OrbitBehavior::OrbitBehavior(glm::vec3 orbitOrigin, float r, float yValue, float orbitSeconds)
{
    origin = orbitOrigin;
    radius = r;
    y = yValue;
    periodSeconds = orbitSeconds;
}

void OrbitBehavior::update(Camera& cam)
{
    cam.setPosition( glm::vec3(
        radius*cos(2*M_PI*glfwGetTime()/periodSeconds),
        y,
        radius*sin(2*M_PI*glfwGetTime()/periodSeconds)
    ));
    cam.lookAt(origin);
    
    // make it adjustable, why not?
    glm::vec3 controls = getControlVector();
    float speed = .2;
    periodSeconds += speed*controls.x;
    y+= speed*controls.y;
    radius += speed*controls.z;
}


void WackyBehavior::update( Camera &cam)
{
    float cameraPeriod = 10.0f/(2*M_PI);

    cam.setPosition(glm::vec3(
        1*sin(2*glfwGetTime()/cameraPeriod), 
        .2*cos(2*glfwGetTime()/cameraPeriod),
        4 - 2 * sin(glfwGetTime()/cameraPeriod)
    ));
  
    cam.lookAt(glm::vec3(0));
    cam.pitch(.5 * cos(glfwGetTime()/cameraPeriod));
    cam.yaw(.5 * cos(2*glfwGetTime()/cameraPeriod));
}



void ControllableBehavior::update(Camera &cam)
{
    glm::vec3 move = getControlVector();
    if(glm::length(move)!=0)
    {
        move = .2f * glm::normalize(move);
        cam.translateRelativeXZ(move);
    }

   
   // cam.yaw(.001*ResourceManager::instance().deltaMousePos.x);
    //cam.pitch(.001*ResourceManager::instance().deltaMousePos.y);
   // cam.rotateAbout(.001*ResourceManager::instance().deltaMousePos.x, glm::vec3(0,1,0));
    //cam.setPitchXZ(sin(glfwGetTime()));
    //cam.getPitchXZ()+.001*ResourceManager::instance().deltaMousePos.y
    //std::cout<<"Yaw: "<<cam.getYawXZ()<<"\n";

    cam.setOrientationXZ(
        cam.getPitchXZ()-.001*ResourceManager::instance().deltaMousePos.y, 
        //M_PI*sin(glfwGetTime()/4.0f)
        cam.getYawXZ()+.001*ResourceManager::instance().deltaMousePos.x
    );
}


void ControllableBehavior::onActiveChanged(Camera &cam, bool newActive)
{
    if(newActive)
    {
        glfwSetInputMode(ResourceManager::instance().getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
        cam.setPosition(glm::vec3(0,0,0));
        cam.lookAt(glm::vec3(0,0,-1));
        return;
    }

    glfwSetInputMode(ResourceManager::instance().getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
}