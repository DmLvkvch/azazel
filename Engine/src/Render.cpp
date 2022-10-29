#include "Render.h"

namespace Azazel
{
    void Render::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    void Render::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
    {
        shader.bind();
        vertexArray.bind();
        indexBuffer.bind();
        glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
    }
}