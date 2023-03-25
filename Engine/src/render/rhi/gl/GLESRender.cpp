#include "GLESRender.h"

#include "utils/ConvertUtils.h"
#include <iostream>

namespace Azazel
{

    GLESRender::GLESRender()
    {

    }

    GLESRender::~GLESRender()
    {

    }

    void GLESRender::init()
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

    void GLESRender::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void GLESRender::clear(bool color, bool depth, bool stencil)
    {
        GLbitfield clear = 0;
        if (color)
        {
            clear |= GL_COLOR_BUFFER_BIT;
        }
        if (depth)
        {
            clear |= GL_DEPTH_BUFFER_BIT;
        }
        if (stencil)
        {
            clear |= GL_STENCIL_BUFFER_BIT;
        }
        glClear(clear);
    }

    void GLESRender::setViewport(int x, int y, int width, int height)
    {
        glViewport(x, y, width, height);
    }

    void GLESRender::setScissor(bool enable)
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
    
    void GLESRender::setScissor(int x, int y, int width, int height)
    {
        glScissor(x, y, width, height);
    }

    void GLESRender::setMultisample(bool enable)
    {
        if (enable)
        {
            glEnable(GL_MULTISAMPLE);
        }
        else
        {
            glEnable(GL_MULTISAMPLE);
        }
    }

    void GLESRender::setCullFace(bool enable)
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

    void GLESRender::setCullFaceMode(CullMode cullMode)
    {
        glCullFace(convertCullMode(cullMode));
    }

    void GLESRender::setFrontFace(CullFront cullFront)
    {
        glFrontFace(convertCullFront(cullFront));
    }

    void GLESRender::setDepthTest(bool enable)
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

    void GLESRender::setDepthFunc()
    {
        
    }


    void GLESRender::setStencilTest(bool enable)
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

    void GLESRender::setBlend(bool enable)
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

    void GLESRender::drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
    {
        shader.bind();
        vertexArray.bind();
        indexBuffer.bind();
        glDrawElements(GL_TRIANGLES, indexBuffer.getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        drawCalls++;
    }

    void GLESRender::drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture)
    {
        texture.bind();
        shader.bind();
        vertexArray.bind();
        indexBuffer.bind();
        glDrawElements(GL_TRIANGLES, indexBuffer.getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        drawCalls++;
    }

    void GLESRender::drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture)
    {
    }


    void GLESRender::beginScene()
    {
        drawCalls = 0;
    }

    void GLESRender::endScene()
    {
    }

    void GLESRender::reset()
    {
    }

    void GLESRender::setBlendFunc(BlendFunction sFactor, BlendFunction dFactor)
    {
        glBlendFunc(convertBlendFunction(sFactor), convertBlendFunction(dFactor));
    }

    void GLESRender::setBlendEquation(BlendEquation blendEquation)
    {
        glBlendEquation(convertBlendEquation(blendEquation));
    }

    void GLESRender::setFramebufferSRGB(bool enable)
    {
        glEnable(GL_FRAMEBUFFER_SRGB);
    }

    void GLESRender::saveState()
    {

    }
    
    void GLESRender::popState()
    {

    }
}