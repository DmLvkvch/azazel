#include "VKRender.h"

#include "render/ConvertUtils.h"
#include <iostream>

namespace Azazel
{

    VKRender::VKRender()
    {

    }

    VKRender::~VKRender()
    {

    }

    void VKRender::init()
    {
        
    }

    void VKRender::setClearColor(const glm::vec4& color)
    {
    }

    void VKRender::clear(bool color, bool depth, bool stencil)
    {
    }

    void VKRender::setViewport(int x, int y, int width, int height)
    {
    }

    void VKRender::setScissor(bool enable)
    {
        if (enable)
        {
        }
        else
        {
        }
    }
    
    void VKRender::setScissor(int x, int y, int width, int height)
    {
    }

    void VKRender::setMultisample(bool enable)
    {
        if (enable)
        {
        }
        else
        {
        }
    }

    void VKRender::setCullFace(bool enable)
    {
        if (enable)
        {
        }
        else
        {
        }
    }

    void VKRender::setCullFaceMode(CullMode cullMode)
    {
    }

    void VKRender::setFrontFace(CullFront cullFront)
    {
    }

    void VKRender::setDepthTest(bool enable)
    {
        if (enable)
        {
        }
        else
        {
        }
    }

    void VKRender::setStencilTest(bool enable)
    {
        if (enable)
        {
        }
        else
        {
        }
    }

    void VKRender::setBlend(bool enable)
    {
        if (enable)
        {
        }
        else
        {
        }
    }

    void VKRender::drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
    {
        shader.bind();
        vertexArray.bind();
        indexBuffer.bind();
        //glDrawElements(GL_TRIANVK, indexBuffer.getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        drawCalls++;
    }

    void VKRender::drawIndexed(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture)
    {
        texture.bind();
        shader.bind();
        vertexArray.bind();
        indexBuffer.bind();
        //glDrawElements(GL_TRIANVK, indexBuffer.getElementCount() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        drawCalls++;
    }

    void VKRender::drawArrays(const VertexArray& vertexArray, const Shader& shader, const Texture& texture)
    {
    }


    void VKRender::beginScene()
    {
        drawCalls = 0;
    }

    void VKRender::endScene()
    {
    }

    void VKRender::reset()
    {
    }

    void VKRender::setBlendFunc(BlendFunction sFactor, BlendFunction dFactor)
    {
    }

    void VKRender::setBlendEquation(BlendEquation blendEquation)
    {
    }

    void VKRender::saveState()
    {

    }
    
    void VKRender::popState()
    {

    }
}