#include "GLESRender.h"

#include "utils/ConvertUtils.h"
#include <iostream>

namespace Azazel
{

    GLESRender::GLESRender()
    {
        std::cout << "GLESRender constructor" << std::endl;
    }

    GLESRender::~GLESRender()
    {
        std::cout << "GLESRender destructor" << std::endl;
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
        unsigned int clearBit = 0;
        if (color)
        {
            clearBit |= GL_COLOR_BUFFER_BIT;
        }
        if (depth)
        {
            clearBit |= GL_DEPTH_BUFFER_BIT;
        }
        if (stencil)
        {
            clearBit |= GL_STENCIL_BUFFER_BIT;
        }
        glClear(clearBit);
    }

    void GLESRender::setViewport(int x, int y, unsigned int width, unsigned int height)
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

    void GLESRender::setDepthMask(bool enable)
    {
        if (enable)
        {
            glDepthMask(GL_TRUE);
        }
        else
        {
            glDepthMask(GL_FALSE);
        }
    }

    void GLESRender::setDepthFunc(CompareFunction compareFunction)
    {
        glDepthFunc(convertCompareFunction(compareFunction));
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

    void GLESRender::setStencilMask(unsigned int mask)
    {
        glStencilMask(mask);
    }

    void GLESRender::setStencilFunc(CompareFunction stencilFunction, int ref, unsigned int mask)
    {
        unsigned int stencilFunc = convertCompareFunction(stencilFunction);
        glStencilFunc(stencilFunc, ref, mask);
    }

    void GLESRender::setStencilOp(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass)
    {
        unsigned int gl_sfail  = convertStencilOp(sfail);
        unsigned int gl_dpfail = convertStencilOp(dpfail);
        unsigned int gl_dppass = convertStencilOp(dppass);

        glStencilOp(gl_sfail, gl_dpfail, gl_dppass);
    }

    void GLESRender::setStencilOpSeparate(CullMode face, StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass)
    {
        unsigned int gl_face   = convertCullMode(face);
        unsigned int gl_sfail  = convertStencilOp(sfail);
        unsigned int gl_dpfail = convertStencilOp(dpfail);
        unsigned int gl_dppass = convertStencilOp(dppass);

        glStencilOpSeparate(gl_face, gl_sfail, gl_dpfail, gl_dppass);
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
        glDrawElements(GL_TRIANGLES, indexBuffer.getElementCount(), GL_UNSIGNED_INT, 0);
        drawCalls++;
    }

    void GLESRender::drawIndexedInstanced(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, int instanceCount)
    {
    }

    void GLESRender::drawIndexedInstanced(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture, int instanceCount)
    {

    }

    void GLESRender::drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture)
    {
    }

    void GLESRender::drawArrays(const VertexArray &vertexArray, const Shader &shader, int vertexCount)
    {
        shader.bind();
        vertexArray.bind();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
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