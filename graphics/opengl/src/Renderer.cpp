//
// Created by Anshul Saraf on 15/09/22.
//

#include "Renderer.h"

void Renderer::Clear() const {
    // Clean the back buffer and assign the new color to it
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

/**
 * Draw call for Element Buffer objects
 */
void Renderer::DrawElements(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) const {
    // Tell OpenGL which Shader Program we want to use
    shader.Bind();
    // Bind the VertexArray so OpenGL knows to use it
    vao.Bind();

    ebo.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr));

}
