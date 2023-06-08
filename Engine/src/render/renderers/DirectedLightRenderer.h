#pragma once

#include <render/Render.h>
#include <render/FrameBuffer.h>

namespace Azazel
{
    class DirectedLightRenderer
    {
        DirectedLightRenderer()
        {
            shadowShader = Shader::create(FileUtils::readFile("shaders/shadow.vert.glsl"), FileUtils::readFile("shaders/shadow.frag.glsl"));
            shadowMap = Shader::create(FileUtils::readFile("shaders/depth_map.vert.glsl"), FileUtils::readFile("shaders/depth_map.frag.glsl"));
        
            depthTexture = Texture::createDepthTexture(1024, 1024);
            frameBuffer = FrameBuffer::create(nullptr, depthTexture);
        }

        ~DirectedLightRenderer()
        {
            delete shadowShader;
            delete shadowMap;
            delete depthTexture;
        }

        void begin()
        {

        }

        void draw()
        {

        }

        void end()
        {

        }

    private:
       FrameBuffer* frameBuffer;
       Shader* shadowShader;
       FrameBuffer* frameBuffer;
       Texture* depthTexture;
    };
}