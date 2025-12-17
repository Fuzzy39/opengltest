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
    rotation = glm::mat4(1);
}

glm::mat4 RenderObject::rotateBy(float radians, glm::vec3 axis)
{

    rotation = glm::rotate(rotation, radians, axis/glm::length(axis));
    return rotation;
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

    model.getShader().setFloat("time", time);

    resetRotation();
    rotateBy(time*2*M_PI, glm::vec3(1, 0,0));
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
    //glm::vec3 axis = glm::cross(glm::vec3(1,0,0), rotation);

    toReturn = toReturn*rotation;

    toReturn = glm::translate(toReturn, -model.getCenter());





    return toReturn;
 }
