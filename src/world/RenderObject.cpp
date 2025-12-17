#include <fuzzygl/world/World.hpp>

RenderObject::RenderObject(Model& model) : model(model)
{
    translation = -model.getCenter();
    resetRotation();
    scale = glm::vec3(1);
}

// Translation
glm::vec3 RenderObject::getTranslation()
{
    return translation;
}

void RenderObject::setTranslation(glm::vec3 toSet)
{
    translation = toSet-model.getCenter();
}

glm::vec3 RenderObject::translateBy(glm::vec3 delta)
{
    return glm::vec3();
}

// Rotation
void RenderObject::resetRotation()
{
    rotation = glm::vec3(1,0,0);
}

glm::mat4 RenderObject::rotateBy(float radians, glm::vec3 axis)
{

    glm::mat4 toReturn = glm::rotate(glm::mat4(1), radians, axis/glm::length(axis));
    glm::vec4 rot = toReturn*glm::vec4(rotation, 1);
    rotation = glm::vec3(rot.x, rot.y, rot.z);

    return toReturn;
}

// Scale
glm::vec3 RenderObject::getScale()
{
    return scale;
}

void RenderObject::setScale(glm::vec3 toSet)
{
    scale = toSet;
}

void RenderObject::draw()
{
    // maybe a bit of a hack. sue me.
    model.getShader().setInt("tex", 2); 
    model.getShader().setMat4("modelMat", getModelMat());
    // Set the transform matrix...

    glBindVertexArray(model.getVAO());
    glDrawArrays(GL_TRIANGLES, 0, model.getNumVertices());
 }


 void RenderObject::setTime(float time)
 {
    resetRotation();
    rotateBy(time*2*M_PI, glm::vec3(0,1,0));
 }

 glm::mat4 RenderObject::getModelMat()
 {
    glm::mat4 toReturn = glm::mat4(1);

    // scale and translate

   
    toReturn = glm::translate(toReturn, translation);
 


    // now, rotate...
    toReturn = glm::translate(toReturn, model.getCenter());
    toReturn = glm::scale(toReturn, scale);

    // recover the rotation parameters
    // the vector rotation is on the unit sphere and represents what rotating (1,0,0) should look like.
    // cross product is perpendicular to both vectors, should be the axis to rotate around.
    glm::vec3 axis = glm::cross(glm::vec3(1,0,0), rotation);

    // magnitude of cross product should be product of magnitudes (1*1)
    // times sin(theta). Get theta:
    //float theta = asin(glm::length(axis));
    float theta = glm::orientedAngle(rotation, glm::vec3(1,0,0), glm::vec3(1,0,0));

    // rotation axis needs to be a unit vector.
    axis = axis*(1.0f/glm::length(axis));
    // std::cout<< "ROT x: "<<rotation.x<<" y: "<<rotation.y<<" z: "<<rotation.z<<"\n";
    // std::cout<< "x: "<<axis.x<<" y: "<<axis.y<<" z: "<<axis.z<<" theta: "<<theta<<"\n\n";
    // do rotation if we can...
    if(axis != glm::vec3(0)) toReturn = glm::rotate(toReturn, theta, axis);

    toReturn = glm::translate(toReturn, -model.getCenter());





    return toReturn;
 }
