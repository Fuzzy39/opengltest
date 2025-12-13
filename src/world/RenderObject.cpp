#include <fuzzygl/world/World.hpp>

RenderObject::RenderObject(Model& model) : model(model)
{
    worldPos = glm::mat4(1);
}

 void RenderObject::draw()
 {
    model.getShader().setMat4("modelMat", worldPos);
    // Set the transform matrix...

    glBindVertexArray(model.getVAO());
    glDrawArrays(GL_TRIANGLES, 0, model.getNumVertices());
 }