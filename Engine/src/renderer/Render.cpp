#include "Render.h"

#include <iostream>

namespace Azazel
{
    std::unique_ptr<Render> Render::render(new Render());

    Render* Render::getRenderer()
    {
        return render.get();
    }

    Render::Render()
    {

    }

    Render::~Render()
    {

    }

    void Render::init()
    {
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* version = glGetString(GL_VERSION);
        const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

        std::cout<<"GL Vendor: "<<vendor<<std::endl;
        std::cout<<"GL Renderer: "<<renderer<<std::endl;
        std::cout<<"GL Version: "<<version<<std::endl;
        std::cout<<"GLSL Version: "<<glslVersion<<std::endl;
    }

    void Render::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Render::clear(bool color, bool depth, bool stencil)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Render::drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture)
    {
        texture.bind();
        shader.bind();
        vertexArray.bind();
        indexBuffer.bind();
        glDrawElements(GL_TRIANGLES, indexBuffer.getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        drawCalls++;
    }

    void Render::drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture)
    {
        texture.bind();
        shader.bind();
        vertexArray.bind();
    }


    void Render::beginScene()
    {
        drawCalls = 0;
    }

    void Render::endScene()
    {
        std::cout << "DrawCalls: " << drawCalls << std::endl;
    }

    void Render::reset()
    {
        glEnable(GL_BLEND);
    }

    void Render::setBlendFunc()
    {

    }

    void Render::setBlendEquation()
    {
    }

}