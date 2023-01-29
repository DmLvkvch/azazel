#include "Render.h"

#include <iostream>

#include "ConvertUtils.h"
#include "gl_cache.h"

namespace Azazel
{
    std::unique_ptr<Render> Render::render(new Render());

    Render* Render::getRender()
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
        const GLubyte* renderer    = glGetString(GL_RENDERER);
        const GLubyte* vendor      = glGetString(GL_VENDOR);
        const GLubyte* version     = glGetString(GL_VERSION);
        const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

        std::cout<<"GL Vendor:    "<< vendor      <<std::endl;
        std::cout<<"GL Renderer:  "<< renderer    <<std::endl;
        std::cout<<"GL Version:   "<< version     <<std::endl;
        std::cout<<"GLSL Version: "<< glslVersion <<std::endl;
    }

    void Render::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Render::clear(bool color, bool depth, bool stencil)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void Render::setViewport(int x, int y, int width, int height)
    {
        glViewport(x, y, width, height);
    }

    void Render::setScissor(bool enable)
    {
        if (enable)
        {
            glEnable(GL_SCISSOR_TEST);
        }
        else
        {
            glDisable(GL_SCISSOR_TEST);
        }
    }
    
    void Render::setScissor(int x, int y, int width, int height)
    {
        glScissor(x, y, width, height);
    }

    void Render::setMultisample(bool enable)
    {
        if (true)
        {
            glEnable(GL_MULTISAMPLE);
        }
        else
        {
            glEnable(GL_MULTISAMPLE);
        }
    }

    void Render::setCullFace(bool enable)
    {
        if (enable)
        {
            glEnable(GL_CULL_FACE);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }
    }

    void Render::setCullFaceMode(CullMode cullMode)
    {
        glCullFace(convertCullMode(cullMode));
    }


    void Render::setDepthTest(bool enable)
    {
        if (enable)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void Render::setStencilTest(bool enable)
    {
        if (enable)
        {
            glEnable(GL_STENCIL);
        }
        else
        {
            glDisable(GL_STENCIL);
        }
    }

    void Render::setBlend(bool enable)
    {
        if (enable)
        {
            glEnable(GL_BLEND);
        }
        else
        {
            glDisable(GL_BLEND);
        }
    }

    void Render::drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
    {
        shader.bind();
        vertexArray.bind();
        indexBuffer.bind();
        glDrawElements(GL_TRIANGLES, indexBuffer.getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        drawCalls++;
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
    }


    void Render::beginScene()
    {
        drawCalls = 0;
    }

    void Render::endScene()
    {
    }

    void Render::reset()
    {
    }

    void Render::setBlendFunc(BlendFunction sFactor, BlendFunction dFactor)
    {
        glBlendFunc(convertBlendFunction(sFactor), convertBlendFunction(dFactor));
    }

    void Render::setBlendEquation(BlendEquation blendEquation)
    {
        glBlendEquation(convertBlendEquation(blendEquation));
    }

    void Render::saveState()
    {

    }
    
    void Render::popState()
    {

    }
}