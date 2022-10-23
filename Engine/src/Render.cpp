#include "Render.h"

void Render::clear()
{
     glClear(GL_COLOR_BUFFER_BIT);
}

void Render::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
{
    shader.bind();
    vertexArray.bind();
    indexBuffer.bind();
    glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}